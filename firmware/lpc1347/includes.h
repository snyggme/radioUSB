/***************************************************************************
 **
 **
 **    Master include file
 **
 **    Used with ARM IAR C/C++ Compiler
 **
 **    (c) Copyright IAR Systems 2007
 **
 **    $Revision: 28 $
 **
 ***************************************************************************/

#ifndef __INCLUDES_H
#define __INCLUDES_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <intrinsics.h>
#include <assert.h>
#include <nxp/iolpc1347.h>

#include "arm_comm.h"
#include "board.h"

#include "drv_clk.h"
#include "drv_nvic.h"

#include "drv_OLED.h"

#include "usb_cnfg.h"
#include "usb_desc.h"
#include "usb_hw.h"
#include "usb_t9.h"
#include "usb_hooks.h"
#include "usb_dev_desc.h"
#include "usb_hooks.h"
#include "usb_buffer.h"

#include "cd_class.h"
#include "cdc_desc.h"
#include "cdc_cmd.h"

#endif  // __INCLUDES_H
