#ifndef __BOARD_H
#define __BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/drivers/GPIO.h>
#include <ti/drivers/SPI.h>
#include <ti/drivers/crypto/CryptoCC26XX.h>

#include "CC1310_LAUNCHXL.h"

#define Board_initGeneral()     CC1310_LAUNCHXL_initGeneral()

#define Board_CRYPTO           CC1310_LAUNCHXL_CRYPTO0

#define GPIO_LED0         CC1310_LAUNCHXL_GPIO_LED0
#define GPIO_LED1         CC1310_LAUNCHXL_GPIO_LED1
#define GPIO_LED2         CC1310_LAUNCHXL_GPIO_LED2

#define PIN_LED0          CC1310_LAUNCHXL_PIN_LED0
#define PIN_LED1          CC1310_LAUNCHXL_PIN_LED1
#define PIN_LED2          CC1310_LAUNCHXL_PIN_LED2

/*
 * These macros are provided for backwards compatibility.
 * Please use the <Driver>_init functions directly rather
 * than Board_init<Driver>.
 */

#define Board_initGPIO()        GPIO_init()
#define Board_SPI0              CC1310_LAUNCHXL_SPI0
#define Board_SPI1              CC1310_LAUNCHXL_SPI1
#define Board_SPI_FLASH_CS      CC1310_LAUNCHXL_SPI_FLASH_CS
#define Board_FLASH_CS_ON       0
#define Board_FLASH_CS_OFF      1
/*
 * These macros are provided for backwards compatibility.
 * Please use the 'Board_PIN_xxx' macros to differentiate
 * them from the 'Board_GPIO_xxx' macros.
 */

#define LED0              PIN_LED0
#define LED1              PIN_LED1
#define LED2              PIN_LED2

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H */
