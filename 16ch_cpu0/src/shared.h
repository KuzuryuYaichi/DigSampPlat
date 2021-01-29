/*
 * shared.h
 *
 *  Created on: 2020Äê7ÔÂ2ÈÕ
 *      Author: 27318
 */

#ifndef SRC_SHARED_H_
#define SRC_SHARED_H_

#include "xil_types.h"

#define SHARED_BASE_PTR (0x3FFFFF00)
#define UPDATE_NET_FLAG (0x3FFFFF40)
#define UPDATE_LCD_FLAG (0x3FFFFF50)
#define CPU1_START_FLAG (0x3FFFFF60)
#define UPDATE_LCD_FLASH_FLAG (0x3FFFFF70)
#define SHARED_CONNECTED_FLAG (0x3FFFFF80)

#define CPU1_Sync_StartFlag (*(volatile u8 *)CPU1_START_FLAG)
#define CPU1_2_CPU0_UpdateNetFlag (*(volatile u8 *)UPDATE_NET_FLAG)
#define CPU0_2_CPU1_UpdateLCDFlag (*(volatile u8 *)UPDATE_LCD_FLAG)
#define CPU1_2_CPU0_UpdateLCDFlashFlag (*(volatile u8 *)UPDATE_LCD_FLASH_FLAG)
#define ConnectedFlag (*(volatile u8 *)SHARED_CONNECTED_FLAG)

struct CONFIG_POS_STRUCT
{
	unsigned char *imgAddr;
	volatile u8 s_data[4];
};

#endif /* SRC_SHARED_H_ */
