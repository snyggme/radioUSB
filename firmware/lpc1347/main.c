
#include "includes.h"
#include <yfuns.h>
#include <stdio.h>

#define DLY_100US               550

volatile uint32_t Ticks;

volatile uint32_t Ticks01s;
volatile uint32_t Ticks1s;
volatile uint32_t Ticks10s;

volatile uint32_t AnimPhase;
volatile uint32_t AnimAct;


/** external data **/

/** internal functions **/

/** public functions **/
/*************************************************************************
 * Function Name: InitClock
 * Parameters:
 * Return: void
 *
 * Description: Initialize PLL to 72MHz
 *              Sys clock is Sys PLL output and  AHB divider is 1
 *              System runs at 72MHz
 *
 *************************************************************************/
void InitClock(void)
{
  /* Enable Internal RC oscillator */
  CLK_SetIRCOsc(CLK_ENABLE);
  /* Select internal RC oscillator for
     Sys clock source*/
  CLK_SetMainClk(MAINSEL_IRCOSC, 1);
  /* Sys Oscilator Enable, bypass disabled, set range */
  CLK_MainOscSet(CLK_ENABLE, CLK_DISABLE, (MOSC >(20MHZ))?(MOSCRNG_15_25MHZ):(MOSCRNG_1_20MHZ));
  /* Select Sys Oscillator for
     SYS PLL source*/
  CLK_SetPLLInClk(PLLINSEL_MOSC);
  /* Enable set PLL 72Hz (M = 6; P = 2) */
  CLK_SetPll(CLK_ENABLE, (72MHZ/MOSC)-1, 1);
  /* Select Sys PLL Output for
     Main clock source. SYSAHB clock divider 1:1. CPU runs at 72MHz */
  CLK_SetMainClk(MAINSEL_CLKPLL,1);
}

/*************************************************************************
 * Function Name: DelayResolution100us
 * Parameters: Int32U Dly
 * Return: void
 *
 * Description: Delay Dly * [100us]
 *
 *************************************************************************/
void DelayResolution100us(Int32U Dly)
{
  for(; Dly; Dly--)
  {
    for(volatile Int32U j = DLY_100US; j; j--)
    {
    }
  }
}

/*************************************************************************
 * Function Name: GpioInit
 * Parameters: void
 * Return: void
 *
 * Description: Reset all GPIO pins to default: primary function
 *
 *************************************************************************/
void GpioInit(void)
{
 /* Set to inputs */
  GPIO_DIR0 = 0;
  GPIO_DIR1 = 0;

  /* Reset all GPIO pins to default primary function */
  IOCON_RESET_PIO0_0 = 0x90;
  IOCON_PIO0_1 = 0x90;
  IOCON_PIO0_2 = 0x90;
  IOCON_PIO0_3 = 0x90;
  IOCON_PIO0_4 = 0x00;
  IOCON_PIO0_5 = 0x00;
  IOCON_PIO0_6 = 0x90;
  IOCON_PIO0_7 = 0x90;
  IOCON_PIO0_8 = 0x90;
  IOCON_PIO0_9 = 0x90;
  IOCON_SWCLK_PIO0_10 = 0x90;
  IOCON_TDI_PIO0_11 = 0x90;
  IOCON_TMS_PIO0_12 = 0x90;
  IOCON_TDO_PIO0_13 = 0x90;
  IOCON_TRST_PIO0_14 = 0x90;
  IOCON_SWDIO_PIO0_15 = 0x90;
  IOCON_PIO0_16 = 0x90;
  IOCON_PIO0_17 = 0x90;
  IOCON_PIO0_20 = 0x90;
  IOCON_PIO0_21 = 0x90;
  IOCON_PIO0_22 = 0x90;
  IOCON_PIO0_23 = 0x90;
  IOCON_PIO1_0 = 0x90;
  IOCON_PIO1_1 = 0x90;
  IOCON_PIO1_2 = 0x90;
  IOCON_PIO1_3 = 0x90;
  IOCON_PIO1_4 = 0x90;
  IOCON_PIO1_5 = 0x90;
  IOCON_PIO1_7 = 0x90;
  IOCON_PIO1_8 = 0x90;
  IOCON_PIO1_10 = 0x90;
  IOCON_PIO1_11 = 0x90;
  IOCON_PIO1_13 = 0x90;
  IOCON_PIO1_14 = 0x90;
  IOCON_PIO1_15 = 0x90;
  IOCON_PIO1_16 = 0x90;
  IOCON_PIO1_17 = 0x90;
  IOCON_PIO1_18 = 0x90;
  IOCON_PIO1_19 = 0x90;
  IOCON_PIO1_20 = 0x90;
  IOCON_PIO1_21 = 0x90;
  IOCON_PIO1_22 = 0x90;
  IOCON_PIO1_23 = 0x90;
  IOCON_PIO1_24 = 0x90;
  IOCON_PIO1_25 = 0x90;
  IOCON_PIO1_26 = 0x90;
  IOCON_PIO1_27 = 0x90;
  IOCON_PIO1_28 = 0x90;
  IOCON_PIO1_29 = 0x90;
  IOCON_PIO1_31 = 0x90;
  
  GPIO_DIR0 = 0xC77834;
  GPIO_DIR1 = 0x00; // as Master was GPIO_DIR1 = 0x088000
}
/*************************************************************************
 * Function Name: SPI_Receive
 * Parameters: pBuf, length
 * *pBuf - input array;
 * length - size of input array 
 * Return: none
 *
 * Description: SPI receiver of bytes 
 *************************************************************************/
void SPI_Receive(uint8_t *pBuf, uint32_t length) 
{
  uint32_t i;
  
  for (i =0; i < length; i++) 
  {
    while(!SSP1SR_bit.RNE);
 
    *pBuf = SSP1DR;
    pBuf++;
  }
}
/*************************************************************************
 * Function Name: SPI_Send
 * Parameters: pBuf, length
 * *pBuf - array of bytes to be send;
 * length - size of input array 
 * Return: none
 *
 * Description: SPI receiver of bytes 
 *************************************************************************/
void SPI_Send(uint8_t *pBuf, uint32_t length) 
{
  uint32_t i;
  
  for (i =0; i < length; i++) 
  {
    while(!SSP1SR_bit.TNF);
 
    SSP1DR = *pBuf;
    pBuf++;
  }
}
/*************************************************************************
 * Function Name: CT32B0_IRQHandler
 * Parameters: none
 *
 * Return: none
 *
 * Description: Timer 0 interrupt handler
 *
 *************************************************************************/
void CT32B0_IRQHandler (void)
{
  ++Ticks;
  
  if( Ticks > 9 )
  {
    Ticks = 0;
    Ticks01s++;
    AnimAct = 1;
  }

  if( Ticks01s > 9 )
  {
    Ticks01s = 0;
    Ticks1s++;
  }

  if( Ticks1s > 9 )
  {
    Ticks1s = 0;
    Ticks10s++;
  }
  
  /* Clear interrupt */
  TMR32B0IR_bit.MR0INT = 1;
  NVIC_ClrPend(NVIC_CT32B0);
}

/*************************************************************************
 * Function Name: CT32B0_Init
 * Parameters: none
 *
 * Return: none
 *
 * Description: Timer 0 initialization
 *
 *************************************************************************/
void CT32B0_Init(uint32_t tps)
{
  Ticks = 0;
  /* Enable TIM0 clocks */
  SYSAHBCLKCTRL_bit.CT32B0 = 1;

  /* Init Timer 0 */
  TMR32B0TCR_bit.CE = 0;     /* counting  disable */
  TMR32B0TCR_bit.CR = 1;     /* set reset */
  TMR32B0TCR_bit.CR = 0;     /* release reset */
  TMR32B0CTCR_bit.CTM = 0;   /* Timer Mode: every rising PCLK edge */
  TMR32B0MCR_bit.MR0I = 1;   /* Enable Interrupt on MR0 */
  TMR32B0MCR_bit.MR0R = 1;   /* Enable reset on MR0 */
  TMR32B0MCR_bit.MR0S = 0;   /* Disable stop on MR0 */
  /* set timer 0 period */
  TMR32B0PR = 0;
  TMR32B0MR0 = (CLK_GetClock(CLK_SYS))/(tps);
  /* init timer 0 interrupt */
  TMR32B0IR_bit.MR0INT = 1;  /* clear pending interrupt */
  TMR32B0TCR_bit.CE = 1;     /* counting Enable */
  /* Enable NVIC TMR0 Interrupt */
  NVIC_IntEnable(NVIC_CT32B0);
  NVIC_IntPri(NVIC_CT32B0,16);
}

/*************************************************************************
 * Function Name: CT32B0_Stop
 * Parameters: none
 *
 * Return: none
 *
 * Description: Disable Timer 0
 *
 *************************************************************************/
void CT32B0_Stop(void)
{
  TMR32B0TCR_bit.CE = 0;        /* counting  disable */

  NVIC_IntDisable(NVIC_CT32B0);

  SYSAHBCLKCTRL_bit.CT32B0 = 0; /* disable clock */
}

#pragma section=".intvec"
/*************************************************************************
 * Function Name: main
 * Parameters: none
 *
 * Return: none
 *
 * Description: main
 *
 *************************************************************************/
int main(void)
{
Int8U i, Buffer[3], txBuff[2], carriageReturn[1];
pInt8U pBuffer;
Int32U Size,TranSize;
Int8U str[60];

Boolean CdcConfigureStateHold;

int cpuclk;
  /* Flash accelerator save value */
  FLASHCFG_bit.FLASHTIM = 3;
  /* Clock Init */
  InitClock();
  /* Flash accelerator init */
  cpuclk = CLK_GetClock(CLK_SYS);

  if( cpuclk < 20000000 ){
    FLASHCFG_bit.FLASHTIM = 1;
  } else if( cpuclk < 40000000 ){
    FLASHCFG_bit.FLASHTIM = 2;
  } else {
    FLASHCFG_bit.FLASHTIM = 3;
  }
  /* Set vector table location */
  VTOR  = (unsigned int)__segment_begin(".intvec");
  /* Enable GPIO Clock */
  SYSAHBCLKCTRL_bit.GPIO = 1;
  /* Enable IOCON Clock */
  SYSAHBCLKCTRL_bit.IOCON = 1;
  /* Set all pins as input ports */
  GpioInit();
  /* Init LED Ports */
  LED1_DIR |= LED1_MASK;
  LED2_DIR |= LED2_MASK;
  /* Turn off LED1 */
  LED_OFF(LED1);
  /* Turn off LED2 */
  LED_OFF(LED2);
  /* Init Timer 0 */
  /*CT32B0_Init(100);

  AnimPhase = 0;
  Ticks = 0;
  Ticks01s = 0;
  Ticks1s = 0;
  Ticks10s = 0;*/


  /* Init USB */
  UsbCdcInit();

  __enable_interrupt();

  /* Soft connection enable */
  USB_ConnectRes(TRUE);

  CdcConfigureStateHold = !IsUsbCdcConfigure();
  
  OLED_SPI_Init();

  //txBuff[0] = 0xAA;
  //txBuff[1] = 0xBB;
  carriageReturn[0] = 13;
  
  while(1)
  {
    if (IsUsbCdcConfigure())
    {
      //Size = UsbCdcRead(txBuff, sizeof(txBuff));
      
      SPI_Receive(Buffer, sizeof(Buffer));
      //SPI_Send(txBuff, sizeof(txBuff));
      
      sprintf(str, "Packet received! packet[0] = %d, packet[1] = %d; RSSI = %d", Buffer[0], Buffer[1], Buffer[2]);
      UsbCdcWrite(str,sizeof(str));
      UsbCdcWrite(&carriageReturn[0],sizeof(carriageReturn[0]));
      
        
    }
  }
}

