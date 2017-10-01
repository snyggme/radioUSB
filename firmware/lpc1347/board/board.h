/***************************************************************************
 **
 **    This file defines the board specific definition
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler.
 **
 **    (c) Copyright IAR Systems 2012
 **
 **    $Revision: 28 $
 **
 ***************************************************************************/
#include <intrinsics.h>
#include "arm_comm.h"

#ifndef __BOARD_H
#define __BOARD_H


#if defined(IAR_LPC1347_SK)
#define MOSC   (12MHZ)

/*LEDs*/
#define USB_CONNECT_LED_MASK   (1UL<<6)
#define USB_CONNECT_LED_DIR    GPIO_DIR0
#define USB_CONNECT_LED        GPIO_B6

#define LED1_MASK   (1UL<<11)
#define LED1_DIR    GPIO_DIR0
#define LED1        GPIO_B11

#define LED2_MASK   (1UL<<12)
#define LED2_DIR    GPIO_DIR0
#define LED2        GPIO_B12

#define LED3_MASK   (1UL<<13)
#define LED3_DIR    GPIO_DIR0
#define LED3        GPIO_B13

#define LED4_MASK   (1UL<<14)
#define LED4_DIR    GPIO_DIR0
#define LED4        GPIO_B14

#define LED5_MASK   (1UL<<15)
#define LED5_DIR    GPIO_DIR0
#define LED5        GPIO_B15

#define LED6_MASK   (1UL<<16)
#define LED6_DIR    GPIO_DIR0
#define LED6        GPIO_B16

#define LED_ON(led) led = 1;
#define LED_OFF(led) led = 0;

#define LED1_CONNECT_IOCON       IOCON_TDI_PIO0_11
#define LED2_CONNECT_IOCON       IOCON_TMS_PIO0_12
#define LED3_CONNECT_IOCON       IOCON_TDO_PIO0_13
#define LED4_CONNECT_IOCON       IOCON_TRST_PIO0_14
#define LED5_CONNECT_IOCON       IOCON_SWDIO_PIO0_15
#define LED6_CONNECT_IOCON       IOCON_PIO0_16

#define LED1_CONNECT_IOCON_INIT  0x81 
#define LED2_CONNECT_IOCON_INIT  0x81 
#define LED3_CONNECT_IOCON_INIT  0x81 
#define LED4_CONNECT_IOCON_INIT  0x81 
#define LED5_CONNECT_IOCON_INIT  0x81 
#define LED6_CONNECT_IOCON_INIT  0x80 


/* Buttons*/
#define BUT2_MASK      (1UL<<9)
#define BUT2_DIR       GPIO_DIR0
#define BUT2           GPIO_B9

#define BUT3_MASK      (1UL<<10)
#define BUT3_DIR       GPIO_DIR0
#define BUT3           GPIO_B10

#define BUT4_MASK      (1UL<<7)
#define BUT4_DIR       GPIO_DIR0
#define BUT4           GPIO_B7

#define BUT5_MASK      (1UL<<8)
#define BUT5_DIR       GPIO_DIR0
#define BUT5           GPIO_B8

#define BUT6_MASK      (1UL<<1)
#define BUT6_DIR       GPIO_DIR0
#define BUT6           GPIO_B1

#define BUT3_CONNECT_IOCON       IOCON_SWCLK_PIO0_10
#define BUT3_CONNECT_IOCON_INIT  0x81 

/*OLED*/
#define OLED_CS_MASK      (1UL<<19)
#define OLED_CS_DIR       GPIO_DIR1
#define OLED_CS           GPIO_B51

#define OLED_CLK_MASK      (1UL<<15)
#define OLED_CLK_DIR       GPIO_DIR1
#define OLED_CLK           GPIO_B47

#define OLED_DIN_MASK      (1UL<<21)
#define OLED_DIN_DIR       GPIO_DIR0
#define OLED_DIN           GPIO_B21

#define OLED_DC_MASK      (1UL<<23)
#define OLED_DC_DIR       GPIO_DIR0
#define OLED_DC           GPIO_B23

#define OLED_RES_MASK      (1UL<<17)
#define OLED_RES_DIR       GPIO_DIR0
#define OLED_RES           GPIO_B17

/* I2C */
#define I2C_SDA_MASK      (1UL<<5)
#define I2C_SDA_DIR       GPIO_DIR0
#define I2C_SDA           GPIO_B5
#define I2C_SDA_IN()      (I2C_SDA_DIR &= ~I2C_SDA_MASK)
#define I2C_SDA_OUT()     (I2C_SDA_DIR |= I2C_SDA_MASK)

#define I2C_SCL_MASK      (1UL<<4)
#define I2C_SCL_DIR       GPIO_DIR0
#define I2C_SCL           GPIO_B4
#define I2C_SCL_IN()      (I2C_SCL_DIR &= ~I2C_SCL_MASK)
#define I2C_SCL_OUT()     (I2C_SCL_DIR |= I2C_SCL_MASK)


/*TEMP*/
#define TEMP_CHANNEL          7
#define TEMP_PIN_IOCON        IOCON_PIO0_23

/*USB*/
#define USB_CONNECT_MASK        (1UL<<6)
#define USB_CONNECT_IOCON       IOCON_PIO0_6
#define USB_CONNECT_IOCON_INIT  0x81 

#define USB_VBUS_MASK           (1UL<<3)
#define USB_VBUS_IOCON          IOCON_PIO0_3
#define USB_VBUS_IOCON_INIT     0x81 

#else
#endif

#endif /* __BOARD_H */
