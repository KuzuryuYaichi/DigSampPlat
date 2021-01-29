/*
 * display_ctrl.h
 *
 *  Created on: 2020Äê4ÔÂ23ÈÕ
 *      Author: 27318
 */

#ifndef SRC_DISPLAY_CTRL_H_
#define SRC_DISPLAY_CTRL_H_

#include <stdio.h>
#include "../platform.h"
#include "xgpio.h"
#include "../shared.h"

#define	AXI_GPIO_DEVICE_ID	XPAR_GPIO_0_DEVICE_ID
#define	XGPIO_BANK1			1
#define	XGPIO_BANK2			2

XGpio_Config *XGpioCfg;
XGpio XGpioInst;

int GPIO_Init();
void LCD_Display();
void Key_Scan();
void memread_NW_param();

#define KEY_OUT_BASE KEY_OUT1
#define KEY_IN_BASE KEY_IN1

#define BIT_POS(pos) (1 << (pos))

#define Gpio_SetBits(InstancePtr, Channel, mask) \
	XGpio_DiscreteWrite(InstancePtr, Channel, XGpio_DiscreteRead(InstancePtr, Channel) | (mask))

#define Gpio_ResetBits(InstancePtr, Channel, mask) \
	XGpio_DiscreteWrite(InstancePtr, Channel, XGpio_DiscreteRead(InstancePtr, Channel) & ~(mask))

enum GPIO_DEF
{
	//KEY INPUT
	KEY_IN1	= 0,
	KEY_IN2,
	KEY_OUT1,
	KEY_OUT2,
	KEY_OUT3,
	//LED STATE
	LED_NET,
	LED_DAT,
	LED_ERR,
	//SPI LCD
	LCD_CS,
	LCD_RES,
	LCD_DC,
	LCD_SCLK,
	LCD_SDIN
};

enum KEY_PRESS
{
	KEY_UP = 0,
	KEY_DOWN,
	KEY_LEFT,
	KEY_OK,
	KEY_CANCEL,
	KEY_RIGHT,
	KEY_NONE
};

enum LCD_STATE
{
	LCD_CHECKED_IP = 0,
	LCD_CHECKED_MASK,
	LCD_CHECKED_GATE,
	LCD_CHANNEL,
	LCD_NET_CONFIG,
	LCD_SAMPLE_MODE,
	LCD_SAMPLE_MODE_SEL,
	LCD_CHANGED,
	LCD_LOGO
};

enum DEMICAL_SYSTEM
{
	UNITS_DEMICAL = 0,
	TENS_DEMICAL,
	HUNDREDS_DEMICAL
};

#endif /* SRC_DISPLAY_CTRL_H_ */
