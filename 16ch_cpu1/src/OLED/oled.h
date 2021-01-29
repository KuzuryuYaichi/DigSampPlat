//////////////////////////////////////////////////////////////////////////////////	 
 //使用SysTick的普通计数模式对延迟进行管理
   //********************************************************************************
#ifndef __OLED_H
#define __OLED_H

#include "xil_types.h"
#include "display_ctrl.h"

#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column		0x3F			// 256/4-1
#define Max_Row		0x3F			// 64-1
#define	Brightness	0xFF 
#define	Shift		0x1C

#define OLED_CS_Clr()  Gpio_ResetBits(&XGpioInst, XGPIO_BANK1, BIT_POS(LCD_CS))
#define OLED_CS_Set()  Gpio_SetBits(&XGpioInst, XGPIO_BANK1, BIT_POS(LCD_CS))

#define OLED_RST_Clr() Gpio_ResetBits(&XGpioInst, XGPIO_BANK1, BIT_POS(LCD_RES))
#define OLED_RST_Set() Gpio_SetBits(&XGpioInst, XGPIO_BANK1, BIT_POS(LCD_RES))

#define OLED_DC_Clr() Gpio_ResetBits(&XGpioInst, XGPIO_BANK1, BIT_POS(LCD_DC))
#define OLED_DC_Set() Gpio_SetBits(&XGpioInst, XGPIO_BANK1, BIT_POS(LCD_DC))

#define OLED_SCLK_Clr() Gpio_ResetBits(&XGpioInst, XGPIO_BANK1, BIT_POS(LCD_SCLK))
#define OLED_SCLK_Set() Gpio_SetBits(&XGpioInst, XGPIO_BANK1, BIT_POS(LCD_SCLK))

#define OLED_SDIN_Clr() Gpio_ResetBits(&XGpioInst, XGPIO_BANK1, BIT_POS(LCD_SDIN))
#define OLED_SDIN_Set() Gpio_SetBits(&XGpioInst, XGPIO_BANK1, BIT_POS(LCD_SDIN))

void delay_ms(int dly);
 		     
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
//OLED控制用函数
void OLED_WR_Byte(u8 dat,u8 cmd);
void OLED_Init(void);
void Set_Column_Address(unsigned char a, unsigned char b);
void Set_Row_Address(unsigned char a, unsigned char b);
void Set_Write_RAM(void);
void Set_Read_RAM(void);
void Fill_RAM(unsigned char Data);
void Draw_Rectangle(unsigned char Data, unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char e);
void Fill_Block(unsigned char Data, unsigned char a, unsigned char b, unsigned char c, unsigned char d);
void Grayscale(void);
void Set_Remap_Format(unsigned char d);
void Show_Pattern(unsigned char *Data_Pointer, unsigned char a, unsigned char b, unsigned char c, unsigned char d);
void Con_4_byte(unsigned char DATA);
void Set_Partial_Display(unsigned char a, unsigned char b, unsigned char c);
void Set_Display_Offset(unsigned char d);
void Set_Start_Line(unsigned char d);
void Set_Master_Current(unsigned char d);
void Vertical_Scroll(unsigned char a, unsigned char b, unsigned char c);
void Set_Gray_Scale_Table(void);
void Set_Linear_Gray_Scale_Table(void); 
 //以下ASCII程序
void Asc5_8(unsigned char x,unsigned char y,unsigned char ch[], int isChecked);
void Asc6_12(unsigned char x,unsigned char y,unsigned char ch[],int isChecked);
void Asc8_16(unsigned char x,unsigned char y,unsigned char ch[]);
void Asc12_24(unsigned char x,unsigned char y,unsigned char ch[]);
void Asc20_40(unsigned char x,unsigned char y,unsigned char ch[]);
 //以下汉字程序
void HZ16_16( unsigned char x, unsigned char y, unsigned char num);
void HZ12_12( unsigned char x, unsigned char y, unsigned char num);
void HZ24_24( unsigned char x, unsigned char y, unsigned char num);
void Show_HZ16_16(unsigned char  x,unsigned char  y, unsigned char  d,unsigned char num1,unsigned char num2);
void Show_HZ12_12(unsigned char  x,unsigned char  y, unsigned char  d,unsigned char num1,unsigned char num2);
void Show_HZ24_24(unsigned char  x,unsigned char  y, unsigned char  d,unsigned char num1,unsigned char num2);

void HZ16_16_TOEC( unsigned char x, unsigned char y, unsigned char num, unsigned char *data);
void Show_HZ16_16_TOEC(unsigned char x,unsigned char y, unsigned char d, unsigned char num1, unsigned char num2, unsigned char *data);

void Display_LCD_CHANNEL(enum LCD_STATE nstate, int forward);
void Display_LCD_SAMPLE_STATE(enum LCD_STATE, int forward);
void Display_LCD_NET_CONFIG(int, enum LCD_STATE, int forward);
void Display_LCD_CONFIG_CHECKED(enum LCD_STATE, int pos);
void Display_LCD_CONFIG_SAMPLE_MODE(enum LCD_STATE, int forward);
void Display_LCD_CONFIG_SAMPLE_MODE_SEL(enum LCD_STATE, int forward, int pos);

#endif  
	 



