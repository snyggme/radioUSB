/***** Includes *****/
#include <stdlib.h>
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>

/* Drivers */
#include <ti/drivers/rf/RF.h>
#include <ti/drivers/PIN.h>

#ifdef DEVICE_FAMILY
    #undef DEVICE_FAMILY_PATH
    #define DEVICE_FAMILY_PATH(x) <ti/devices/DEVICE_FAMILY/x>
    #include DEVICE_FAMILY_PATH(driverlib/rf_prop_mailbox.h)
#else
    #error "You must define DEVICE_FAMILY at the project level as one of cc26x0, cc26x0r2, cc13x0, etc."
#endif

/* Board Header files */
#include "Board.h"

#include "RFQueue.h"
#include "smartrf_settings/smartrf_settings.h"

#include <stdlib.h>

/* Pin driver handle */
static PIN_Handle ledPinHandle;
static PIN_State ledPinState;

/*
 * Application LED pin configuration table:
 *   - All LEDs board LEDs are off.
 */
PIN_Config pinTable[] =
{
    PIN_ID(16) | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    PIN_ID(17) | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX, // DIO17: LED2 (initially off)
    PIN_ID(18) | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX, // DIO18: LED3 (initially off)
    PIN_ID(4) | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL ,

    PIN_TERMINATE
};


/***** Defines *****/
#define RX_TASK_STACK_SIZE 1024
#define RX_TASK_PRIORITY   2
#define PARS_TASK_PRIORITY   3

/* Packet RX Configuration */
#define DATA_ENTRY_HEADER_SIZE 8  /* Constant header size of a Generic Data Entry */
#define MAX_LENGTH             30 /* Max length byte the radio will accept */
#define NUM_DATA_ENTRIES       2  /* NOTE: Only two data entries supported at the moment */
#define NUM_APPENDED_BYTES     3  /* The Data Entries data field will contain:
                                   * 1 Header byte (RF_cmdPropRx.rxConf.bIncludeHdr = 0x1)
                                   * Max 30 payload bytes
                                   * 1 status byte (RF_cmdPropRx.rxConf.bAppendStatus = 0x1) */

#define AES_ECB_LENGTH 16



/***** Prototypes *****/
static void rxTaskFunction(UArg arg0, UArg arg1);
static void parsTaskFunction(UArg arg0, UArg arg1);
static void callback(RF_Handle h, RF_CmdHandle ch, RF_EventMask e);

/***** Variable declarations *****/
static Task_Params rxTaskParams, parsTaskParams;
Task_Struct rxTask, parsTask;    /* not static so you can see in ROV */
static uint8_t rxTaskStack[RX_TASK_STACK_SIZE], parsTaskStack[RX_TASK_STACK_SIZE];

static RF_Object rfObject;
static RF_Handle rfHandle;

Semaphore_Struct semStruct;
Semaphore_Handle semHandle;

/* Buffer which contains all Data Entries for receiving data.
 * Pragmas are needed to make sure this buffer is 4 byte aligned (requirement from the RF Core) */
#if defined(__TI_COMPILER_VERSION__)
    #pragma DATA_ALIGN (rxDataEntryBuffer, 4);
        static uint8_t rxDataEntryBuffer[RF_QUEUE_DATA_ENTRY_BUFFER_SIZE(NUM_DATA_ENTRIES,
                                                                 MAX_LENGTH,
                                                                 NUM_APPENDED_BYTES)];
#elif defined(__IAR_SYSTEMS_ICC__)
    #pragma data_alignment = 4
        static uint8_t rxDataEntryBuffer[RF_QUEUE_DATA_ENTRY_BUFFER_SIZE(NUM_DATA_ENTRIES,
                                                                 MAX_LENGTH,
                                                                 NUM_APPENDED_BYTES)];
#elif defined(__GNUC__)
        static uint8_t rxDataEntryBuffer [RF_QUEUE_DATA_ENTRY_BUFFER_SIZE(NUM_DATA_ENTRIES,
            MAX_LENGTH, NUM_APPENDED_BYTES)] __attribute__ ((aligned (4)));
#else
    #error This compiler is not supported.
#endif

/* Receive dataQueue for RF Core to fill in data */
static dataQueue_t dataQueue;
static rfc_dataEntryGeneral_t* currentDataEntry;
static uint8_t packetLength;
static uint8_t* packetDataPointer;
static int8_t rssi;

static PIN_Handle pinHandle;

static uint8_t packet[MAX_LENGTH + NUM_APPENDED_BYTES - 1]; /* The length byte is stored in a separate variable */

/*typedef struct
{
  uint8_t key[16];                      // Stores the Aes Key
  CryptoCC26XX_KeyLocation keyLocation; // Location in Key RAM
  uint8_t clearText[AES_ECB_LENGTH];    // Input message - cleartext
  uint8_t msgOut[AES_ECB_LENGTH];       // Output message
} AESECBExample;

AESECBExample ecbExample =
{
  { 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6,
  0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C },
  CRYPTOCC26XX_KEY_0,
  { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
  { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }
};

CryptoCC26XX_Handle             handle;
int32_t                         keyIndex;
int32_t                         status;
CryptoCC26XX_AESECB_Transaction trans;
*/


/***** Function definitions *****/
void RxTask_init(PIN_Handle ledPinHandle) {
    pinHandle = ledPinHandle;

    Task_Params_init(&rxTaskParams);
    rxTaskParams.stackSize = RX_TASK_STACK_SIZE;
    rxTaskParams.priority = RX_TASK_PRIORITY;
    rxTaskParams.stack = &rxTaskStack;
    rxTaskParams.arg0 = (UInt)1000000;

    Task_construct(&rxTask, rxTaskFunction, &rxTaskParams, NULL);
}

void ParsTask_init() {

    Task_Params_init(&parsTaskParams);
    parsTaskParams.stackSize = RX_TASK_STACK_SIZE;
    parsTaskParams.priority = PARS_TASK_PRIORITY;
    parsTaskParams.stack = &parsTaskStack;
    parsTaskParams.arg0 = (UInt)1000000;

    Task_construct(&parsTask, parsTaskFunction, &parsTaskParams, NULL);
}

static void rxTaskFunction(UArg arg0, UArg arg1)
{
    RF_Params rfParams;
    RF_Params_init(&rfParams);

    if( RFQueue_defineQueue(&dataQueue,
                            rxDataEntryBuffer,
                            sizeof(rxDataEntryBuffer),
                            NUM_DATA_ENTRIES,
                            MAX_LENGTH + NUM_APPENDED_BYTES))
    {
        /* Failed to allocate space for all data entries */
        while(1);
    }

    /* Modify CMD_PROP_RX command for application needs */
    RF_cmdPropRx.pQueue = &dataQueue;           /* Set the Data Entity queue for received data */
    RF_cmdPropRx.rxConf.bAutoFlushIgnored = 1;  /* Discard ignored packets from Rx queue */
    RF_cmdPropRx.rxConf.bAutoFlushCrcErr = 1;   /* Discard packets with CRC error from Rx queue */
    RF_cmdPropRx.maxPktLen = MAX_LENGTH;        /* Implement packet length filtering to avoid PROP_ERROR_RXBUF */
    RF_cmdPropRx.pktConf.bRepeatOk = 1;
    RF_cmdPropRx.pktConf.bRepeatNok = 1;

    /* Request access to the radio */
    rfHandle = RF_open(&rfObject, &RF_prop, (RF_RadioSetup*)&RF_cmdPropRadioDivSetup, &rfParams);

    /* Set the frequency */
    RF_postCmd(rfHandle, (RF_Op*)&RF_cmdFs, RF_PriorityNormal, NULL, 0);

    /* Enter RX mode and stay forever in RX */
    RF_runCmd(rfHandle, (RF_Op*)&RF_cmdPropRx, RF_PriorityNormal, &callback, IRQ_RX_ENTRY_DONE);

    while(1);
}

void callback(RF_Handle h, RF_CmdHandle ch, RF_EventMask e)
{
    if (e & RF_EventRxEntryDone)
    {
        /* Toggle pin to indicate RX */
        PIN_setOutputValue(pinHandle, PIN_ID(16),!PIN_getOutputValue(PIN_ID(16)));

        /* Get current unhandled data entry */
        currentDataEntry = RFQueue_getDataEntry();

        /* Handle the packet data, located at &currentDataEntry->data:
         * - Length is the first byte with the current configuration
         * - Data starts from the second byte */
        packetLength      = *(uint8_t*)(&currentDataEntry->data);
        packetDataPointer = (uint8_t*)(&currentDataEntry->data + 1);

        /* Copy the payload + the status byte to the packet variable */
        memcpy(packet, packetDataPointer, (packetLength + 2));

        RFQueue_nextEntry();

        Semaphore_post(semHandle);
    }
}

static void parsTaskFunction(UArg arg0, UArg arg1)
{
    SPI_Handle      spi;
    SPI_Params      spiParams;
    SPI_Transaction spiTransaction;
    uint8_t         transmitBuffer[3];
    uint8_t         receiveBuffer[2];
    bool            transferOK;


    SPI_Params_init(&spiParams);  // Initialize SPI parameters
    spiParams.bitRate     = 1000000;
    spiParams.frameFormat = SPI_POL1_PHA1;
    spiParams.mode        = SPI_MASTER;

    spiTransaction.count = sizeof(transmitBuffer);
    spiTransaction.txBuf = transmitBuffer;
    spiTransaction.rxBuf = receiveBuffer;

    spi = SPI_open(Board_SPI0, &spiParams);
    if (spi == NULL) {
        while (1);  // SPI_open() failed
    }

    PIN_setOutputValue(ledPinHandle, CC1310_LAUNCHXL_SPI0_CSN, 1);

    while(1){

        Semaphore_pend(semHandle, BIOS_WAIT_FOREVER);

       /* ecbExample.msgOut[0] = packet[0];
        ecbExample.msgOut[1] = packet[1];
        ecbExample.msgOut[2] = packet[2];
        ecbExample.msgOut[3] = packet[3];
        ecbExample.msgOut[4] = packet[4];
        ecbExample.msgOut[5] = packet[5];
        ecbExample.msgOut[6] = packet[6];
        ecbExample.msgOut[7] = packet[7];
        ecbExample.msgOut[8] = packet[8];
        ecbExample.msgOut[9] = packet[9];
        ecbExample.msgOut[10] = packet[10];
        ecbExample.msgOut[11] = packet[11];
        ecbExample.msgOut[12] = packet[12];
        ecbExample.msgOut[13] = packet[13];
        ecbExample.msgOut[14] = packet[14];
        ecbExample.msgOut[15] = packet[15];

        // Attempt to open CryptoCC26XX.
        handle = CryptoCC26XX_open(Board_CRYPTO, false, NULL);
        if (!handle) {
          System_abort("Crypto module could not be opened.");
        }
        keyIndex = CryptoCC26XX_allocateKey(handle, ecbExample.keyLocation,
                                                                           (const uint32_t *) ecbExample.key);
        if (keyIndex == CRYPTOCC26XX_STATUS_ERROR) {
                System_abort("Key Location was not allocated.");
        }

        // Initialize transaction
        CryptoCC26XX_Transac_init((CryptoCC26XX_Transaction *) &trans, CRYPTOCC26XX_OP_AES_ECB_DECRYPT);
        // Setup transaction
        trans.keyIndex         = keyIndex;
        trans.msgIn            = (uint32_t *) ecbExample.msgOut;
        trans.msgOut           = (uint32_t *) ecbExample.clearText;
        // Zero original clear text before decrypting the cypher text into the ecbExample.clearText array
        memset(ecbExample.clearText, 0x0, AES_ECB_LENGTH);
        // Decrypt the plaintext with AES ECB
        status = CryptoCC26XX_transact(handle, (CryptoCC26XX_Transaction *) &trans);
        if(status != CRYPTOCC26XX_STATUS_SUCCESS){
                System_abort("Encryption failed.");
        }
        CryptoCC26XX_releaseKey(handle, &keyIndex);

        printf("ClearText - %d, %d, %d, %d\n", ecbExample.clearText[0], ecbExample.clearText[1], ecbExample.clearText[2], ecbExample.clearText[3]);
        printf("EncryptedText - %d, %d, %d, %d\n", ecbExample.msgOut[0], ecbExample.msgOut[1], ecbExample.msgOut[2], ecbExample.msgOut[3]); */

        transmitBuffer[0] = packet[0];
        transmitBuffer[1] = packet[1];
        //transmitBuffer[0] = ecbExample.clearText[0];
        //transmitBuffer[1] = ecbExample.clearText[1];
        transmitBuffer[2] = packet[30];

        PIN_setOutputValue(ledPinHandle, PIN_ID(4), 0);

        transferOK = SPI_transfer(spi, &spiTransaction);

        PIN_setOutputValue(ledPinHandle, PIN_ID(4), 1);

        //printf("receiveBuffer[0] = %d, receiveBuffer[1] = %d \n", receiveBuffer[0], receiveBuffer[1]);
        //printf("packet[30] = %d\n", (packet[30] >> 1));
    }
}

/*
 *  ======== main ========
 */
int main(void)
{
    Semaphore_Params semParams;

    /* Call driver init functions. */
    Board_initGeneral();
    SPI_init();  // Initialize the SPI driver
    //CryptoCC26XX_init();

    /* Open LED pins */
    ledPinHandle = PIN_open(&ledPinState, pinTable);
    if(!ledPinHandle)
    {
        System_abort("Error initializing board LED pins\n");
    }

    /* Initialize task */
    RxTask_init(ledPinHandle);
    ParsTask_init();

    /* Construct a Semaphore object to be use as a resource lock, inital count 1 */
    Semaphore_Params_init(&semParams);
    Semaphore_construct(&semStruct, 1, &semParams);

    /* Obtain instance handle */
    semHandle = Semaphore_handle(&semStruct);

    /* Start BIOS */
    BIOS_start();

    return (0);
}
