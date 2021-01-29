/*
 * gpio.c
 *
 *  Created on: 2020年4月23日
 *      Author: 27318
 */
#include <stdio.h>
#include "../platform.h"
#include "xgpio.h"
#include "display_ctrl.h"
#include "../shared.h"

int GPIO_Init()
{
	int Status;
	/*
	 * Initialize the AXI GPIO driver.
	 */
	XGpioCfg = XGpio_LookupConfig(AXI_GPIO_DEVICE_ID);
	Status = XGpio_CfgInitialize(&XGpioInst, XGpioCfg, XGpioCfg->BaseAddress);
	if (Status != XST_SUCCESS) {
		print("axi gpio cfg init err\n");
		return XST_FAILURE;
	}

	XGpio_SetDataDirection(&XGpioInst, XGPIO_BANK1, ~(BIT_POS(LED_NET)
													| BIT_POS(LED_DAT)
													| BIT_POS(LED_ERR)
													| BIT_POS(KEY_IN1)
													| BIT_POS(KEY_IN2)
													| BIT_POS(LCD_CS)
													| BIT_POS(LCD_RES)
													| BIT_POS(LCD_DC)
													| BIT_POS(LCD_SCLK)
													| BIT_POS(LCD_SDIN)));

	Gpio_ResetBits(&XGpioInst, XGPIO_BANK1, BIT_POS(LED_NET) | BIT_POS(LED_DAT) | BIT_POS(LED_ERR));
	return XST_SUCCESS;
}

static enum KEY_PRESS keyPress = 0;
static int selectedIndex = LCD_CHECKED_IP, selectedIndexMainMenu = LCD_CHANNEL;
u32 channelStateN = 0, channelStateL = 0;

extern int Udp_Send_num;

void LedSetError()
{
	Gpio_SetBits(&XGpioInst, XGPIO_BANK1, BIT_POS(LED_ERR));
}

void LedResetError()
{
	Gpio_ResetBits(&XGpioInst, XGPIO_BANK1, BIT_POS(LED_ERR));
}

void Key_Scan()
{
	static int timer = 0;
	static enum KEY_PRESS lastPress = KEY_NONE;
	enum KEY_PRESS nowPress = KEY_NONE;
	int i;

	for(i=0;i<2;i++)//扫描检测按键
	{
		Gpio_SetBits(&XGpioInst, XGPIO_BANK1, BIT_POS(KEY_IN_BASE + i));
		u32 down = XGpio_DiscreteRead(&XGpioInst, XGPIO_BANK1);
		if(down & BIT_POS(KEY_OUT1))
		{
			nowPress = 3 * i + (KEY_OUT1 - KEY_OUT_BASE);
		}
		else if(down & BIT_POS(KEY_OUT2))
		{
			nowPress = 3 * i + (KEY_OUT2 - KEY_OUT_BASE);
		}
		else if(down & BIT_POS(KEY_OUT3))
		{
			nowPress = 3 * i + (KEY_OUT3 - KEY_OUT_BASE);
		}
		Gpio_ResetBits(&XGpioInst, XGPIO_BANK1, BIT_POS(KEY_IN_BASE + i));
	}

	if(nowPress == KEY_NONE)//判断按键为未按下 清空计数器
	{
		timer = 0;
	}
	else if(lastPress == KEY_NONE && nowPress != KEY_NONE)//判断按键为刚按下 启动计数器
	{
		++timer;
	}
	else if(timer == 5)//超过50ms认为有效
	{
		keyPress = (nowPress >= KEY_UP && nowPress <= KEY_RIGHT) ? nowPress : KEY_NONE;
		++timer;
	}
	else if(lastPress == nowPress && timer > 0 && timer < 5)//未超过50ms 并且按键一致时 累加计数器
	{
		++timer;
	}
	else if(timer < 100)
	{
		++timer;
	}
	else if(timer == 100 && nowPress == KEY_CANCEL)
	{
		Gpio_ResetBits(&XGpioInst, XGPIO_BANK1, BIT_POS(LED_ERR));
		++timer;
	}

	lastPress = nowPress;
}

static int char_pos = 0;
extern struct CONFIG_POS_STRUCT *ConfigPosStruct;
const u32 demical_num[3] = {100, 10, 1};
static enum LCD_STATE cstate = LCD_LOGO, nstate = LCD_CHANNEL;

u16 SampleState, SampleStateL;
int forward = 0, SampleModeSel = 0;

void LCD_Display()
{
	static u8 last_modified[4];

	SampleState = Get_Sample_Mode();

	channelStateN = ~XGpio_DiscreteRead(&XGpioInst, XGPIO_BANK2);

	if(channelStateN)
		Gpio_SetBits(&XGpioInst, XGPIO_BANK1, BIT_POS(LED_DAT));
	else
		Gpio_ResetBits(&XGpioInst, XGPIO_BANK1, BIT_POS(LED_DAT));

	if(ConnectedFlag)
		Gpio_SetBits(&XGpioInst, XGPIO_BANK1, BIT_POS(LED_NET));
	else
		Gpio_ResetBits(&XGpioInst, XGPIO_BANK1, BIT_POS(LED_NET));

	if(keyPress != KEY_NONE)
	{
		switch(cstate)
		{
		case LCD_CHANNEL://当处于通道数据界面时
		case LCD_SAMPLE_MODE:
		case LCD_NET_CONFIG:
		{
			switch(keyPress)
			{
			case KEY_LEFT://按左方向键菜单向上滑动
				forward = 1;
				selectedIndex = 0;
				if(--selectedIndexMainMenu < LCD_CHANNEL)selectedIndexMainMenu = LCD_SAMPLE_MODE;
				nstate = selectedIndexMainMenu;
				break;
			case KEY_RIGHT://按右方向键菜单向下滑动
				forward = 0;
				selectedIndex = 0;
				if(++selectedIndexMainMenu > LCD_SAMPLE_MODE)selectedIndexMainMenu = LCD_CHANNEL;
				nstate = selectedIndexMainMenu;
				break;
			}
			if(cstate == LCD_SAMPLE_MODE)
			{
				if(keyPress == KEY_OK)
				{
					SampleStateL = SampleState;
					nstate = LCD_SAMPLE_MODE_SEL;
				}
			}
			else if(cstate == LCD_NET_CONFIG)//当处于网络配置界面时
			{
				switch(keyPress)
				{
				case KEY_UP:
					if(--selectedIndex == -1)
						selectedIndex = 2;
					nstate = LCD_CHANGED;
					break;
				case KEY_DOWN:
					if(++selectedIndex == 3)
						selectedIndex = 0;
					nstate = LCD_CHANGED;
					break;
				case KEY_OK://按OK进入网络配置界面
					if(selectedIndex >= LCD_CHECKED_IP && selectedIndex <= LCD_CHECKED_GATE)
					{
						nstate = selectedIndex;
						memcpy(last_modified, ConfigPosStruct[selectedIndex].s_data, 4);
					}
					else
					{
						selectedIndex = 0;
						nstate = LCD_CHANGED;
					}
					break;
				}
			}
			break;
		}
		case LCD_SAMPLE_MODE_SEL:
		{
			switch(keyPress)
			{
			case KEY_UP:
			case KEY_DOWN:
			{
				u32 BitMask = 1 << SampleModeSel;
				if(SampleState & BitMask)
					SampleState &= ~BitMask;
				else
					SampleState |= BitMask;
				Set_Sample_Mode(SampleState);
				SampleState = Get_Sample_Mode();
				nstate = LCD_CHANGED;
				break;
			}
			case KEY_OK://确认后保存到flash
				CPU1_2_CPU0_UpdateLCDFlashFlag = 1;
				nstate = LCD_SAMPLE_MODE;
				break;
			case KEY_CANCEL://取消则不保存 回滚上次配置
				Set_Sample_Mode(SampleStateL);
				SampleState = Get_Sample_Mode();
				nstate = LCD_SAMPLE_MODE;
				break;
			case KEY_LEFT:
				if(--SampleModeSel < 0)SampleModeSel=7;
				nstate = LCD_CHANGED;
				break;
			case KEY_RIGHT:
				if(++SampleModeSel > 7)SampleModeSel=0;
				nstate = LCD_CHANGED;
				break;
			}
			break;
		}
		case LCD_CHECKED_IP:
		case LCD_CHECKED_GATE:
		case LCD_CHECKED_MASK:
		{
			switch(keyPress)
			{
			case KEY_CANCEL:
				memcpy(ConfigPosStruct[selectedIndex].s_data, last_modified, 4);
				nstate = LCD_NET_CONFIG;
				break;
			case KEY_OK:
//				modify_flash_net_config();
				CPU1_2_CPU0_UpdateNetFlag = 1;
				nstate = LCD_NET_CONFIG;
				break;
			case KEY_UP:
			case KEY_DOWN:
			{
				int tmp, index = -1;
				if(char_pos >= 0 && char_pos <= 2)
				{
					index = 0;
				}
				else if(char_pos >= 5 && char_pos <= 7)
				{
					index = 1;
				}
				else if(char_pos >= 10 && char_pos <= 12)
				{
					index = 2;
				}
				else if(char_pos >= 15 && char_pos <= 17)
				{
					index = 3;
				}
				else goto KeyChanged;
				if(keyPress == KEY_UP)
				{
					tmp = ConfigPosStruct[cstate].s_data[index] + demical_num[char_pos - index * 5];
					ConfigPosStruct[cstate].s_data[index] = tmp > 255 ? 0 : (tmp & 0xFF);
				}
				else if(keyPress == KEY_DOWN)
				{
					tmp = ConfigPosStruct[cstate].s_data[index] - demical_num[char_pos - index * 5];
					ConfigPosStruct[cstate].s_data[index] = tmp < 0 ? 255 : (tmp & 0xFF);
				}
			KeyChanged:
				nstate = LCD_CHANGED;
				break;
			}
			case KEY_LEFT:
				if(char_pos == 0)char_pos = 17;
				else if(char_pos == 5 || char_pos == 10 || char_pos == 15)char_pos-=3;
				else char_pos--;
				nstate = LCD_CHANGED;
				break;
			case KEY_RIGHT:
				if(char_pos == 17)char_pos = 0;
				else if(char_pos == 2 || char_pos == 7 || char_pos == 12)char_pos+=3;
				else char_pos++;
				nstate = LCD_CHANGED;
				break;
			}
			break;
		}
		}
		keyPress = KEY_NONE;
	}
	else if(channelStateN != channelStateL)
	{
		channelStateL = channelStateN;
		nstate = LCD_CHANGED;
	}
	else if(CPU0_2_CPU1_UpdateLCDFlag)
	{
		CPU0_2_CPU1_UpdateLCDFlag = 0;
		nstate = LCD_CHANGED;
	}

	if(cstate != nstate)
	{
		switch(cstate)
		{
		case LCD_CHANNEL:
		{
			if(nstate != LCD_CHANGED)
			{
				if(nstate == LCD_NET_CONFIG)
					Display_LCD_NET_CONFIG(selectedIndex, LCD_CHANNEL, forward);
				else if(nstate == LCD_SAMPLE_MODE)
					Display_LCD_SAMPLE_MODE(nstate, cstate, forward);
				cstate = nstate;
			}
			else
			{
				Display_LCD_CHANNEL(LCD_CHANGED, forward);
				nstate = cstate;
			}
			break;
		}
		case LCD_SAMPLE_MODE:
		{
			if(nstate != LCD_CHANGED)
			{
				if(nstate == LCD_NET_CONFIG)
					Display_LCD_NET_CONFIG(selectedIndex, LCD_SAMPLE_MODE, forward);
				else if(nstate == LCD_CHANNEL)
					Display_LCD_CHANNEL(nstate, forward);
				else if(nstate == LCD_SAMPLE_MODE_SEL)
					Display_LCD_SAMPLE_MODE_SEL(nstate, forward, SampleModeSel);
				cstate = nstate;
			}
			else
			{
				Display_LCD_SAMPLE_MODE(LCD_CHANGED, cstate, forward);
				nstate = cstate;
			}
			break;
		}
		case LCD_SAMPLE_MODE_SEL:
		{
			if(nstate != LCD_CHANGED)
			{
				if(nstate == LCD_SAMPLE_MODE)
					Display_LCD_SAMPLE_MODE(nstate, cstate, forward);
				cstate = nstate;
			}
			else
			{
				Display_LCD_SAMPLE_MODE_SEL(nstate, forward, SampleModeSel);
				nstate = cstate;
			}
			break;
		}
		case LCD_NET_CONFIG:
		{
			if(nstate != LCD_CHANGED)
			{
				switch(nstate)
				{
				case LCD_CHANNEL:
					Display_LCD_CHANNEL(LCD_CHANNEL, forward);
					break;
				case LCD_SAMPLE_MODE:
					Display_LCD_SAMPLE_MODE(LCD_SAMPLE_MODE, cstate, forward);
					break;
				case LCD_CHECKED_IP:
				case LCD_CHECKED_GATE:
				case LCD_CHECKED_MASK:
					Display_LCD_CONFIG_CHECKED((enum LCD_STATE)selectedIndex, char_pos);
					break;
				}
				cstate = nstate;
			}
			else
			{
				Display_LCD_NET_CONFIG(selectedIndex, nstate, forward);
				nstate = cstate;
			}
			break;
		}
		case LCD_CHECKED_IP:
		{
			if(nstate != LCD_CHANGED)
			{
				if(nstate == LCD_NET_CONFIG)
					Display_LCD_NET_CONFIG(selectedIndex, LCD_CHECKED_IP);
				cstate = nstate;
			}
			else
			{
				Display_LCD_CONFIG_CHECKED(LCD_CHECKED_IP, char_pos);
				nstate = cstate;
			}
			break;
		}
		case LCD_CHECKED_GATE:
		{
			if(nstate != LCD_CHANGED)
			{
				if(nstate == LCD_NET_CONFIG)
					Display_LCD_NET_CONFIG(selectedIndex, LCD_CHECKED_IP);
				cstate = nstate;
			}
			else
			{
				Display_LCD_CONFIG_CHECKED(LCD_CHECKED_GATE, char_pos);
				nstate = cstate;
			}
			break;
		}
		case LCD_CHECKED_MASK:
		{
			if(nstate != LCD_CHANGED)
			{
				if(nstate == LCD_NET_CONFIG)
					Display_LCD_NET_CONFIG(selectedIndex, LCD_CHECKED_IP);
				cstate = nstate;
			}
			else
			{
				Display_LCD_CONFIG_CHECKED(LCD_CHECKED_MASK, char_pos);
				nstate = cstate;
			}
			break;
		}
		case LCD_LOGO:
		{
			if(nstate != LCD_CHANGED)
			{
				Display_LCD_CHANNEL_NORMAL(LCD_CHANNEL);
				cstate = nstate;
			}
			break;
		}
		default:break;
		}
	}
}
