#ifndef __CC1310_LAUNCHXL_BOARD_H__
#define __CC1310_LAUNCHXL_BOARD_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include <ti/drivers/PIN.h>
#include <ti/devices/cc13x0/driverlib/ioc.h>

/* Externs */
extern const PIN_Config BoardGpioInitTable[];

/* Defines */
#define CC1310_LAUNCHXL

/* Mapping of pins to board signals using general board aliases
 *      <board signal alias>                  <pin mapping>   <comments>
 */

/* LEDs */
#define CC1310_LAUNCHXL_PIN_LED0              IOID_10
#define CC1310_LAUNCHXL_PIN_LED1              IOID_12
#define CC1310_LAUNCHXL_PIN_LED2              IOID_14

/* SPI */
#define CC1310_LAUNCHXL_SPI_FLASH_CS          PIN_UNASSIGNED
#define CC1310_LAUNCHXL_FLASH_CS_ON           0
#define CC1310_LAUNCHXL_FLASH_CS_OFF          1

/* SPI Board */
#define CC1310_LAUNCHXL_SPI0_MISO             IOID_2
#define CC1310_LAUNCHXL_SPI0_MOSI             IOID_1
#define CC1310_LAUNCHXL_SPI0_CLK              IOID_3
#define CC1310_LAUNCHXL_SPI0_CSN              PIN_UNASSIGNED
#define CC1310_LAUNCHXL_SPI1_MISO             PIN_UNASSIGNED
#define CC1310_LAUNCHXL_SPI1_MOSI             PIN_UNASSIGNED
#define CC1310_LAUNCHXL_SPI1_CLK              PIN_UNASSIGNED
#define CC1310_LAUNCHXL_SPI1_CSN              PIN_UNASSIGNED

/*!
 *  @brief  Initialize the general board specific settings
 *
 *  This function initializes the general board specific settings.
 */
void CC1310_LAUNCHXL_initGeneral(void);

/*!
 *  @def    CC1310_LAUNCHXL_CryptoName
 *  @brief  Enum of Crypto names
 */
typedef enum CC1310_LAUNCHXL_CryptoName {
    CC1310_LAUNCHXL_CRYPTO0 = 0,

    CC1310_LAUNCHXL_CRYPTOCOUNT
} CC1310_LAUNCHXL_CryptoName;

/*!
 *  @def    CC1310_LAUNCHXL_GPIOName
 *  @brief  Enum of GPIO names
 */
typedef enum CC1310_LAUNCHXL_GPIOName {
    CC1310_LAUNCHXL_GPIO_LED0 = 0,
    CC1310_LAUNCHXL_GPIO_LED1,
    CC1310_LAUNCHXL_GPIO_LED2,

    CC1310_LAUNCHXL_GPIOCOUNT
} CC1310_LAUNCHXL_GPIOName;

typedef enum CC1310_LAUNCHXL_SPIName {
    CC1310_LAUNCHXL_SPI0 = 0,
    CC1310_LAUNCHXL_SPI1,

    CC1310_LAUNCHXL_SPICOUNT
} CC1310_LAUNCHXL_SPIName;

typedef enum CC1310_LAUNCHXL_UDMAName {
    CC1310_LAUNCHXL_UDMA0 = 0,

    CC1310_LAUNCHXL_UDMACOUNT
} CC1310_LAUNCHXL_UDMAName;

#ifdef __cplusplus
}
#endif

#endif /* __CC1310_LAUNCHXL_BOARD_H__ */
