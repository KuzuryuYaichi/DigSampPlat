//////////////////////////////////////////////////////////////////////////////////	 
// M31S1322_01_V1 FOR STM32 201505 WWW.LCDSOC.COM

//********************************************************************************
//�ӿڶ������oled.h�ļ�
#include "oled.h"
//����ASCII��
#include "Asc5x8.h" 	   //ascii 5*8�ֿ�
#include "Asc6x12.h" 	   //ascii 8*16�ֿ�
#include "Asc8x16.h" 	   //ascii 8*16�ֿ�
#include "Asc12x24.h" 	   //ascii 12*24�ֿ�
#include "Asc20x40.h" 	   //ascii 20*40�ֿ�
//�Զ��庺�ֿ�
#include "HZ12X12_S.h" 	   //12*12�����Զ��庺�ֿ�
#include "HZ16X16_S.h" 	   //16*16�����Զ��庺�ֿ�
#include "HZ24X24_S.h" 	   //24*24�����Զ��庺�ֿ�
// #include "HZ24X24_H.h" 	   //24*24�����Զ��庺�ֿ�
// #include "HZ24X24_K.h" 	   //24*24�����Զ��庺�ֿ�
#include "HZ16X16_TOEC.h"
#include "../shared.h"

extern struct CONFIG_POS_STRUCT *configPosStruct;

//��SSD1325д��һ���ֽڡ�
//dat:Ҫд�������/����
//cmd:����/�����־ 0,��ʾ����;1,��ʾ����;
void OLED_WR_Byte(u8 dat,u8 cmd)
{	
	u8 i;			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  
	OLED_CS_Clr();
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat<<=1;   
	}				 		  
	OLED_CS_Set();
	OLED_DC_Set();   	  
} 

void delay_us(int dly)
{
	int i, j;
	for (i = 0; i < dly; i++) {
		for (j = 0; j < 65; j++) {
			;
		}
	}
}

void delay_ms(int dly)
{
	int i, j;
	for (i = 0; i < dly; i++) {
		for (j = 0; j < 0xffff; j++) {
			;
		}
	}
}

//-----------------OLED�˿ڶ��� 4��SPI----------------  					   
/* ����IO��ģ��SPIͨѶ��ʽ����oledģ��
CS   ~ PE6
RES ~ PE5
DC   ~ PE4
CLK  ~ PE3
DIN ~ PE2
*/  
//��ʼ��SSD1322				    
void OLED_Init(void)
{
    OLED_RST_Set();
	delay_ms(100);
	OLED_RST_Clr();
	delay_ms(100);
	OLED_RST_Set(); 
		
	OLED_WR_Byte(0xAE,OLED_CMD); //	Display Off
	
	OLED_WR_Byte(0xFD,OLED_CMD); // Set Command Lock
	OLED_WR_Byte(0x12,OLED_DATA); //
	
	OLED_WR_Byte(0xB3,OLED_CMD); // Set Clock as 80 Frames/Sec
	OLED_WR_Byte(0x91,OLED_DATA); //  

   	OLED_WR_Byte(0xCA,OLED_CMD); // Set Multiplex Ratio
	OLED_WR_Byte(0x3F,OLED_DATA); // 1/64 Duty (0x0F~0x5F)
   
	OLED_WR_Byte(0xA2,OLED_CMD); // Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_DATA); //	
	
	OLED_WR_Byte(0xA1,OLED_CMD); // Set Mapping RAM Display Start Line (0x00~0x7F)
	OLED_WR_Byte(0x00,OLED_DATA); //	

	
	OLED_WR_Byte(0xA0,OLED_CMD); //Set Column Address 0 Mapped to SEG0 
	OLED_WR_Byte(0x14,OLED_DATA);      	//   Default => 0x40
						                //     Horizontal Address Increment
						//     Column Address 0 Mapped to SEG0
						//     Disable Nibble Remap
						//     Scan from COM0 to COM[N-1]
						//     Disable COM Split Odd Even
	OLED_WR_Byte(0x11,OLED_DATA);      	//    Default => 0x01 (Disable Dual COM Mode)

	
	OLED_WR_Byte(0xB5,OLED_CMD); //  Disable GPIO Pins Input
	OLED_WR_Byte(0x00,OLED_DATA); //	
	
    OLED_WR_Byte(0xAB,OLED_CMD); //   Enable Internal VDD Regulator
	OLED_WR_Byte(0x01,OLED_DATA); //

	OLED_WR_Byte(0xB4,OLED_CMD); //  Display Enhancement  
	OLED_WR_Byte(0xA0,OLED_DATA); // Enable External VSL
	OLED_WR_Byte(0xF8,OLED_DATA); // Enhance Low Gray Scale Display Quality

    OLED_WR_Byte(0xC1,OLED_CMD); //  Set Contrast Current 
	OLED_WR_Byte(0xEF,OLED_DATA); //  Default => 0x7F

    OLED_WR_Byte(0xC7,OLED_CMD); //  Master Contrast Current Control 
	OLED_WR_Byte(Brightness,OLED_DATA); //  Default => 0x0f (Maximum)

    OLED_WR_Byte(0xB8,OLED_CMD); //  	// Set Gray Scale Table 
	OLED_WR_Byte(0x0C,OLED_DATA); //
	OLED_WR_Byte(0x18,OLED_DATA); //
	OLED_WR_Byte(0x24,OLED_DATA); //
	OLED_WR_Byte(0x30,OLED_DATA); //
	OLED_WR_Byte(0x3C,OLED_DATA); //
	OLED_WR_Byte(0x48,OLED_DATA); //
	OLED_WR_Byte(0x54,OLED_DATA); //
	OLED_WR_Byte(0x60,OLED_DATA); //
	OLED_WR_Byte(0x6C,OLED_DATA); //
	OLED_WR_Byte(0x78,OLED_DATA); //
	OLED_WR_Byte(0x84,OLED_DATA); //
	OLED_WR_Byte(0x90,OLED_DATA); //
	OLED_WR_Byte(0x9C,OLED_DATA); //
	OLED_WR_Byte(0xA8,OLED_DATA); //
	OLED_WR_Byte(0xB4,OLED_DATA); //
 	OLED_WR_Byte(0x00,OLED_CMD); 	// Enable Gray Scale Table

	OLED_WR_Byte(0xB1,OLED_CMD); //   Set Phase 1 as 5 Clocks & Phase 2 as 14 Clocks
	OLED_WR_Byte(0xE2,OLED_DATA); //  Default => 0x74 (7 Display Clocks [Phase 2] / 9 Display Clocks [Phase 1])

    OLED_WR_Byte(0xD1,OLED_CMD); //    Enhance Driving Scheme Capability (0x00/0x20)
	OLED_WR_Byte(0xA2,OLED_DATA); //   Normal
	OLED_WR_Byte(0x20,OLED_DATA); //

    OLED_WR_Byte(0xBB,OLED_CMD); //     Set Pre-Charge Voltage Level as 0.60*VCC
	OLED_WR_Byte(0x1F,OLED_DATA); //

    OLED_WR_Byte(0xB6,OLED_CMD); //  // Set Second Pre-Charge Period as 8 Clocks 
	OLED_WR_Byte(0x08,OLED_DATA); //

    OLED_WR_Byte(0xBE,OLED_CMD); //  Set Common Pins Deselect Voltage Level as 0.86*VCC 
	OLED_WR_Byte(0x07,OLED_DATA); //  Default => 0x04 (0.80*VCC)

    OLED_WR_Byte(0xA6,OLED_CMD); //     Normal Display Mode (0x00/0x01/0x02/0x03)
	 							//   Default => 0xA4
						//     0xA4  => Entire Display Off, All Pixels Turn Off
						//     0xA5  => Entire Display On, All Pixels Turn On at GS Level 15
						//     0xA6  => Normal Display
						//     0xA7  => Inverse Display
	 
	OLED_WR_Byte(0xA9,OLED_CMD); // Disable Partial Display
     	 	
	Fill_RAM(0x00);
	OLED_WR_Byte(0xAF,OLED_CMD); //	Display On
}  

void Set_Column_Address(unsigned char a, unsigned char b)
{
	OLED_WR_Byte(0x15,OLED_CMD);		// Set Column Address
	OLED_WR_Byte(a,OLED_DATA);			// Default => 0x00
	OLED_WR_Byte(b,OLED_DATA);			// Default => 0x77
}

void Set_Row_Address(unsigned char a, unsigned char b)
{
	OLED_WR_Byte(0x75,OLED_CMD);		// Set Row Address
	OLED_WR_Byte(a,OLED_DATA);			// Default => 0x00
	OLED_WR_Byte(b,OLED_DATA);			// Default => 0x7F
}

void Set_Write_RAM()
{
	OLED_WR_Byte(0x5C,OLED_CMD);			// Enable MCU to Write into RAM
}

void Set_Read_RAM()
{
	OLED_WR_Byte(0x5D,OLED_CMD);			// Enable MCU to Read from RAM
}

void Set_Remap_Format(unsigned char d)
{
	 OLED_WR_Byte(0xA0,OLED_CMD);  			// Set Re-Map / Dual COM Line Mode
	 OLED_WR_Byte(d,OLED_DATA);  			// Default => 0x40
											// Horizontal Address Increment
											// Column Address 0 Mapped to SEG0
											// Disable Nibble Remap
											// Scan from COM0 to COM[N-1]
											// Disable COM Split Odd Even
	 OLED_WR_Byte(0x11,OLED_DATA); 	 		// Default => 0x01 (Disable Dual COM Mode)
} 

void Set_Partial_Display(unsigned char a, unsigned char b, unsigned char c)
{
  	OLED_WR_Byte((0xA8|a),OLED_CMD);		// Default => 0x8F
					
	if(a == 0x00)
	{
	    OLED_WR_Byte(b,OLED_DATA);
		OLED_WR_Byte(c,OLED_DATA);
	}
}

void Set_Display_Offset(unsigned char d)
{
	OLED_WR_Byte(0xA2,OLED_CMD);
 	OLED_WR_Byte(d,OLED_DATA);
}

void Set_Start_Line(unsigned char d)
{
	OLED_WR_Byte(0xA1,OLED_CMD);	// Set Vertical Scroll by RAM
 	OLED_WR_Byte(d,OLED_DATA);
}

void Set_Master_Current(unsigned char d)
{
	OLED_WR_Byte(0xC7,OLED_CMD);	//  Master Contrast Current Control
 	OLED_WR_Byte(d,OLED_DATA);
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Gray Scale Table Setting (Full Screen)
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Set_Gray_Scale_Table()
{
    OLED_WR_Byte(0xB8,OLED_CMD); //  	// Set Gray Scale Table 
	OLED_WR_Byte(0x0C,OLED_DATA); //
	OLED_WR_Byte(0x18,OLED_DATA); //
	OLED_WR_Byte(0x24,OLED_DATA); //
	OLED_WR_Byte(0x30,OLED_DATA); //
	OLED_WR_Byte(0x3C,OLED_DATA); //
	OLED_WR_Byte(0x48,OLED_DATA); //
	OLED_WR_Byte(0x54,OLED_DATA); //
	OLED_WR_Byte(0x60,OLED_DATA); //
	OLED_WR_Byte(0x6C,OLED_DATA); //
	OLED_WR_Byte(0x78,OLED_DATA); //
	OLED_WR_Byte(0x84,OLED_DATA); //
	OLED_WR_Byte(0x90,OLED_DATA); //
	OLED_WR_Byte(0x9C,OLED_DATA); //
	OLED_WR_Byte(0xA8,OLED_DATA); //
	OLED_WR_Byte(0xB4,OLED_DATA); //
 	OLED_WR_Byte(0x00,OLED_CMD); 	// Enable Gray Scale Table
}

void Set_Linear_Gray_Scale_Table()
{
   	OLED_WR_Byte(0xB9,OLED_CMD); //	Set Default Linear Gray Scale Table
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Vertical Scrolling (Full Screen)
//
//    a: Scrolling Direction
//       "0x00" (Upward)		���Ϲ���
//       "0x01" (Downward)		���¹���
//    b: Set Numbers of Row Scroll per Step	  ÿ֡����
//    c: Set Time Interval between Each Scroll Step	ÿ֡����ʱ
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Vertical_Scroll(unsigned char a, unsigned char b, unsigned char c)
{
	unsigned char i,j;

	Set_Partial_Display(0x00,0x00,Max_Row);

	switch(a)
	{
		case 0:
			for(i=0;i<(Max_Row+1);i+=b)
			{
				Set_Display_Offset(i+1);
				for(j=0;j<c;j++)
				{
					delay_us(200);
				}
			}
			break;
		case 1:
			for(i=0;i<(Max_Row+1);i+=b)
			{
				Set_Display_Offset(Max_Row-i);
				for(j=0;j<c;j++)
				{
					delay_us(200);
				}
			}
			break;
	}
	Set_Partial_Display(0x01,0x00,0x00);
}
  
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Show Regular Pattern (Full Screen)
// ��������,������,������Ļ�Ǻڵ�
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Fill_RAM(unsigned char Data)
{
	unsigned char i, j;

	Set_Column_Address(0x00,0x77);
	Set_Row_Address(0x00,0x7F);
	Set_Write_RAM();

	for(i=0;i<128;i++)
	{
		for(j=0;j<120;j++)
		{
			OLED_WR_Byte(Data,OLED_DATA);
		    OLED_WR_Byte(Data,OLED_DATA); 
		}
	}
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  www.lcdsoc.com 201505
//	Data:ȡֵΪ 0x11��0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff, ff����
//  a: Line Width		�߿�
//  b: Column Address of Start ��ʼ��
//  c: Column Address of End	 ������
//  d: Row Address of Start	 ��ʼ��
//  e: Row Address of End		 ������
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Draw_Rectangle(unsigned char Data, unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char e)
{
	unsigned char i,j,k,l,b1,c1;
	b1=b/4;
	c1=c/4;
	k=a%4;
	l=(a/4)+(k?0:-1);

	Set_Column_Address(Shift+b1,Shift+c1);
	Set_Row_Address(d,(d+a-1));
	Set_Write_RAM();
	for(i=0;i<(c1-b1+1);i++)
	{
		for(j=0;j<a;j++)
		{
			OLED_WR_Byte(Data, OLED_DATA);
			OLED_WR_Byte(Data, OLED_DATA);
		}
	}

	Set_Column_Address(Shift+(c1-l),Shift+c1);
	Set_Row_Address(d+a,e-a);
	Set_Write_RAM();
	for(i=0;i<(e-d+1);i++)
	{
		for(j=0;j<(l+1);j++)
		{
			if(j == 0)
			{
				switch(k)
				{
					case 0:
						OLED_WR_Byte(Data, OLED_DATA);
						OLED_WR_Byte(Data, OLED_DATA);
						break;
					case 1:
						OLED_WR_Byte(0x00, OLED_DATA);
						OLED_WR_Byte(Data & 0x0F, OLED_DATA);
						break;
					case 2:
					    OLED_WR_Byte(0x00, OLED_DATA);
						OLED_WR_Byte(Data, OLED_DATA);
						break;
					case 3:
						OLED_WR_Byte(Data & 0x0F, OLED_DATA);
						OLED_WR_Byte(Data, OLED_DATA);
						break;
				}
			}
			else
			{
				OLED_WR_Byte(Data,OLED_DATA);
				OLED_WR_Byte(Data,OLED_DATA);
			}
		}
	}
   
	Set_Column_Address(Shift+b1,Shift+c1);
	Set_Row_Address((e-a+1),e);
	Set_Write_RAM();
	for(i=0;i<(c1-b1+1);i++)
	{
		for(j=0;j<a;j++)
		{
			OLED_WR_Byte(Data,OLED_DATA);
			OLED_WR_Byte(Data,OLED_DATA); 
		}
	}

	Set_Column_Address(Shift+b1,Shift+(b1+l));
	Set_Row_Address(d+a,e-a);
	Set_Write_RAM();
	for(i=0;i<(e-d+1);i++)
	{
		for(j=0;j<(l+1);j++)
		{
			if(j == l)
			{
				switch(k)
				{
				case 0:
					OLED_WR_Byte(Data,OLED_DATA);
					OLED_WR_Byte(Data,OLED_DATA);
					break;
				case 1:
					OLED_WR_Byte((Data&0xF0),OLED_DATA);
					OLED_WR_Byte(0x00,OLED_DATA);
					break;
				case 2:
					OLED_WR_Byte(Data,OLED_DATA);
					OLED_WR_Byte(0x00,OLED_DATA);
					break;
				case 3:
					OLED_WR_Byte(Data,OLED_DATA);
					OLED_WR_Byte((Data&0xF0),OLED_DATA);
					break;
				}
			}
			else
			{
				OLED_WR_Byte(Data,OLED_DATA);
				OLED_WR_Byte(Data,OLED_DATA);
			}
		}
	}
}

void Draw_Rectangle_LOCAL(unsigned char Data, unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char e, void *dataPtr)
{
	unsigned char (*DataPtr)[128] = dataPtr;
	unsigned char i,j,m,n,b1,c1;
	b1=b/2;
	c1=c/2;
	m=b%2;
	n=c%2;

	for(j=d;j<=e;j++)
	{
		for(i=b1;i<=c1;i++)
		{
			if(j==d || j==e)
				DataPtr[j][i] = 0xFF;
			else if(i==b1)
				DataPtr[j][i] = DataPtr[j][i]|(m?0x0F:0xF0);
			else if(i==c1)
				DataPtr[j][i] = DataPtr[j][i]|(n?0x0F:0xF0);
			else
				DataPtr[j][i] = 0;
		}
	}
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Show Regular Pattern (Partial or Full Screen)
//
//    a: Column Address of Start
//    b: Column Address of End (Total Columns Devided by 4)
//    c: Row Address of Start
//    d: Row Address of End
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Fill_Block(unsigned char Data, unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
	unsigned char i,j;
	
	Set_Column_Address(Shift+a,Shift+b);
	Set_Row_Address(c,d);
	Set_Write_RAM();

	for(i=0;i<(d-c+1);i++)
	{
		for(j=0;j<(b-a+1);j++)
		{
			OLED_WR_Byte(Data,OLED_DATA);
		    OLED_WR_Byte(Data,OLED_DATA); 
		}
	}
}

void LOCAL_Fill_Line_One_Ch(unsigned char data, unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
	unsigned char i, j;

	Set_Column_Address(Shift+a,Shift+b);
	Set_Row_Address(c,d);
	Set_Write_RAM();

	for(i=0;i<(d-c+1);i++)
	{
		for(j=0;j<(b-a+1);j++)
		{
			OLED_WR_Byte(data,OLED_DATA);
		}
	}
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Show Pattern (Partial or Full Screen)
//
//    a: Column Address of Start
//    b: Column Address of End (Total Columns Devided by 4)
//    c: Row Address of Start
//    d: Row Address of End
// �Ҷ�ģʽ����ʾһ��ͼƬ
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Show_Pattern(unsigned char *Data_Pointer, unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
	unsigned char *Src_Pointer;
	unsigned char i,j;
 
  //ȡģʱ����������	�����ܷ�����2.7��ͬ��
    Src_Pointer=Data_Pointer;
	Set_Column_Address(Shift+a,Shift+b);
	Set_Row_Address(c,d);
	Set_Write_RAM();
  	for(i=0;i<(d-c+1);i++)
	{
		for(j=0;j<(b-a+1);j++)
		{
			OLED_WR_Byte(*Src_Pointer,OLED_DATA);
			Src_Pointer++;
			OLED_WR_Byte(*Src_Pointer,OLED_DATA);
			Src_Pointer++;
		}
	}
 }

/**************************************
  ����ת�����򣺽�2λ�ֳ�1���ֽڴ����Դ棬����1��seg��ʾ4��������Ҫͬʱд2���ֽڼ�4������
  uchar DATA��ȡģ������ģ����
****************************************/
void Con_4_byte(unsigned char DATA)
{
	unsigned char d1_4byte[4],d2_4byte[4];
	unsigned char i;
	unsigned char d,k1,k2;
	d=DATA;

	for(i=0;i<2;i++)   // һ��λ�ķ�ʽд��  2*4=8λ
	{
		k1=d&0xc0;     //��i=0ʱ ΪD7,D6λ ��i=1ʱ ΪD5,D4λ

		/****��4�ֿ��ܣ�16���Ҷ�,һ���ֽ����ݱ�ʾ�������أ�һ�����ض�Ӧһ���ֽڵ�4λ***/
		switch(k1)
		{
		case 0x00:
			d1_4byte[i]=0x00;
			break;
		case 0x40:  // 0100,0000
			d1_4byte[i]=0x0f;
			break;
		case 0x80:  //1000,0000
			d1_4byte[i]=0xf0;
			break;
		case 0xc0:   //1100,0000
			d1_4byte[i]=0xff;
			break;
		default:
			break;
		}

		d=d<<2;
		k2=d&0xc0;     //��i=0ʱ ΪD7,D6λ ��i=1ʱ ΪD5,D4λ

		/****��4�ֿ��ܣ�16���Ҷ�,һ���ֽ����ݱ�ʾ�������أ�һ�����ض�Ӧһ���ֽڵ�4λ***/
		switch(k2)
		{
		case 0x00:
			d2_4byte[i]=0x00;
			break;
		case 0x40:  // 0100,0000
			d2_4byte[i]=0x0f;
			break;
		case 0x80:  //1000,0000
			d2_4byte[i]=0xf0;
			break;
		case 0xc0:   //1100,0000
			d2_4byte[i]=0xff;
			break;
		default:
			break;
		}

		d=d<<2;                                //������λ

		OLED_WR_Byte(d1_4byte[i],OLED_DATA);//дǰ2��
		OLED_WR_Byte(d2_4byte[i],OLED_DATA);//д��2��	  ����4��
	}
}

void LOCAL_Con_4_byte(unsigned char DATA, void *dataPtr, int x, int y)
{
	unsigned char (*DataPtr)[128] = dataPtr;
	unsigned char d1_4byte[4],d2_4byte[4];
	unsigned char i;
	unsigned char d,k1,k2;
	d=DATA;

	for(i=0;i<2;i++)   // һ��λ�ķ�ʽд��  2*4=8λ
	{
		k1=d&0xc0;     //��i=0ʱ ΪD7,D6λ ��i=1ʱ ΪD5,D4λ
		/****��4�ֿ��ܣ�16���Ҷ�,һ���ֽ����ݱ�ʾ�������أ�һ�����ض�Ӧһ���ֽڵ�4λ***/
		switch(k1)
		{
		case 0x00:
			d1_4byte[i]=0x00;
			break;
		case 0x40:  // 0100,0000
			d1_4byte[i]=0x0f;
			break;
		case 0x80:  //1000,0000
			d1_4byte[i]=0xf0;
			break;
		case 0xc0:   //1100,0000
			d1_4byte[i]=0xff;
			break;
		default:
			break;
		}
		d=d<<2;

		k2=d&0xc0;     //��i=0ʱ ΪD7,D6λ ��i=1ʱ ΪD5,D4λ
		/****��4�ֿ��ܣ�16���Ҷ�,һ���ֽ����ݱ�ʾ�������أ�һ�����ض�Ӧһ���ֽڵ�4λ***/
		switch(k2)
		{
		case 0x00:
			d2_4byte[i]=0x00;
			break;
		case 0x40:  // 0100,0000
			d2_4byte[i]=0x0f;
			break;
		case 0x80:  //1000,0000
			d2_4byte[i]=0xf0;
			break;
		case 0xc0:   //1100,0000
			d2_4byte[i]=0xff;
			break;
		default:
			break;
		}
		d=d<<2;                                //������λ

		DataPtr[y][x + 2 * i] = d1_4byte[i];
		DataPtr[y][x + 2 * i + 1] = d2_4byte[i];
	}
}
 
/***************************************************************
//  ��ʾ12*12������ 2015-05���²���ͨ��
//  ȡģ��ʽΪ������ȡģ���λ,��������:�����Ҵ��ϵ���    16�� 12�� 
//   num���������ֿ��е�λ��
//   x: Start Column  ��ʼ�� ��Χ 0~��256-16��
//   y: Start Row   ��ʼ�� 0~63 
***************************************************************/
void HZ12_12( unsigned char x, unsigned char y, unsigned char num)
{
	unsigned char x1,j ;
	x1=x/4; 
	Set_Column_Address(Shift+x1,Shift+x1+3); // ���������꣬shiftΪ��ƫ������1322������3Ϊ16/4-1
	Set_Row_Address(y,y+11); 
	Set_Write_RAM();	 //	д�Դ�

	for(j=0;j<24;j++)
	{
		 Con_4_byte(HZ12X12_S[num*24+j]);
	}
}

//****************************************************
//   д��һ��12*12���� www.lcdsoc.com	x������ּ��dҪΪ4�ı���
//    num1,num2���������ֿ��е�λ��	 ��num1��ʾ��num2
//    x: Start Column  ��ʼ�� ��Χ 0~��255-16��
//    y: Start Row    ��ʼ�� 0~63
//    d:�ּ���� 0Ϊ�޼�� 
//*****************************************************
void Show_HZ12_12(unsigned char x, unsigned char y, unsigned char d, unsigned char num1, unsigned char num2)
{
	unsigned char i,d1;
	d1=d+16;
	for(i=num1;i<num2+1;i++)
	{
		HZ12_12(x,y,i);
		x=x+d1;
	}
}

/***************************************************************
//  ��ʾ16*16������ 2015-05���²���ͨ��
//  ȡģ��ʽΪ������ȡģ���λ,��������:�����Ҵ��ϵ���    16�� 16�� 
//   num���������ֿ��е�λ��
//   x: Start Column  ��ʼ�� ��Χ 0~��256-16��
//   y: Start Row   ��ʼ�� 0~63 
***************************************************************/
void HZ16_16( unsigned char x, unsigned char y, unsigned char num)
{
	unsigned char x1,j ;
	x1=x/4; 
	Set_Column_Address(Shift+x1,Shift+x1+3); // ���������꣬shiftΪ��ƫ������1322������3Ϊ16/4-1
	Set_Row_Address(y,y+15); 
	Set_Write_RAM();	 //	д�Դ�
	for(j=0;j<32;j++)
	{
		 Con_4_byte(HZ16X16_S[num*32+j]);
	}
}

//****************************************************
//   д��һ��16*16���� www.lcdsoc.com
//    num1,num2���������ֿ��е�λ��	 ��num1��ʾ��num2
//    x: Start Column  ��ʼ�� ��Χ 0~��255-16��
//    y: Start Row    ��ʼ�� 0~63
//    d:�ּ���� 0Ϊ�޼�� 
//x������ּ��dҪΪ4�ı���
//*****************************************************
void Show_HZ16_16(unsigned char x, unsigned char y, unsigned char d, unsigned char num1, unsigned char num2)
{
	unsigned char i,d1;
	d1=d+16;
	for(i=num1;i<num2+1;i++)
	{
		HZ16_16(x,y,i);
		x=x+d1;
	}
}

/***************************************************************
//  ��ʾ24*24������ 2015-05���²���ͨ��
//  ȡģ��ʽΪ������ȡģ���λ,��������:�����Ҵ��ϵ���    24�� 24�� 
//   num���������ֿ��е�λ��
//   x: Start Column  ��ʼ�� ��Χ 0~��255-16��
//   y: Start Row   ��ʼ�� 0~63 
***************************************************************/
void HZ24_24(unsigned char x, unsigned char y, unsigned char num)
{
	unsigned char x1,j ;
	x1=x/4; 
	Set_Column_Address(Shift+x1, Shift+x1+5); // ���������꣬shiftΪ��ƫ������1322������3Ϊ16/4-1
	Set_Row_Address(y, y+23);
	Set_Write_RAM();	 //	д�Դ�
	for(j=0;j<72;j++)
	{
		 Con_4_byte(HZ24X24_S[num*72+j]);	//����24*24 ������������Ҫ����24*24��HZ24X24_K.h�� ,����24*24��HZ24X24_H.h��������Ӧ��ͷ�ļ����޸Ĵ˴�������
	}
}

//****************************************************
//   д��һ��24*24���� www.lcdsoc.com
//    num1,num2���������ֿ��е�λ��	 ��num1��ʾ��num2
//    x: Start Column  ��ʼ�� ��Χ 0~��255-16��
//    y: Start Row    ��ʼ�� 0~63
//    d:�ּ���� 0Ϊ�޼�� 
//    x������ּ��dҪΪ4�ı���
//*****************************************************
void Show_HZ24_24(unsigned char x,unsigned char y, unsigned char d,unsigned char num1, unsigned char num2)
{
	unsigned char i, d1;
	d1=d+24;
	for(i=num1;i<num2+1;i++)
	{
		HZ24_24(x,y,i);
		x=x+d1;
	}
}

//==============================================================
//����������д��һ���׼ASCII�ַ���	 5x8
//��������ʾ��λ�ã�x,y����ch[]Ҫ��ʾ���ַ���
//���أ���
//==============================================================  
void Asc5_8(unsigned char x,unsigned char y,unsigned char ch[], int isChecked)
{
	unsigned char x1, c=0, i=0, j=0;
	while (ch[i] != '\0')
	{
		x1=x/4;
		c =ch[i]-32;
		if(x1>61)
		{
			x=0;
			x1=x/4;
			y=y+8;
		}  //����
		Set_Column_Address(Shift+x1,Shift+x1+1); // ���������꣬shiftΪ��ƫ������1322����
		Set_Row_Address(y,y+7);
		Set_Write_RAM();	 //	д�Դ�

		for(j=0;j<8;j++)
		{
			Con_4_byte(isChecked?~ASC5X8[c*8+j]:ASC5X8[c*8+j]);	//����ת��
		}
		i++;
		x=x+8;	 //�ּ�࣬8Ϊ��С
	}
}

//==============================================================
//����������д��һ���׼ASCII�ַ���	 5x8
//��������ʾ��λ�ã�x,y����ch[]Ҫ��ʾ���ַ���
//���أ���
//==============================================================
void LOCAL_Asc5_8(unsigned char x,unsigned char y,unsigned char ch[], unsigned char *dataPtr)
{
	unsigned char x1, c=0, i=0, j=0;
	while (ch[i] != '\0')
	{
		x1=x/2;
		c =ch[i]-32;

		for(j=0;j<8;j++)
		{
			LOCAL_Con_4_byte(ASC5X8[c*8+j], dataPtr, x1, y+j);	//����ת��
		}
		i++;
		x=x+8;	 //�ּ�࣬8Ϊ��С
	}
}

//==============================================================
//����������д��һ���׼ASCII�ַ���	 6x12
//��������ʾ��λ�ã�x,y����ch[]Ҫ��ʾ���ַ���
//���أ���
//==============================================================  
void Asc6_12(unsigned char x,unsigned char y,unsigned char ch[], int isChecked)
{
	unsigned char x1, c=0, i=0, j=0;
	while (ch[i] != '\0')
	{
		x1=x/4;
		c=ch[i]-32;
		if(x1>61)
		{
			x=0;
			x1=x/4;
			y=y+12;
		}  //����
		Set_Column_Address(Shift+x1,Shift+x1+1); // ���������꣬shiftΪ��ƫ������1322����
		Set_Row_Address(y,y+11);
		Set_Write_RAM();	 //	д�Դ�

		for(j=0;j<12;j++)
		{
			Con_4_byte(isChecked?~ASC6X12[c*12+j]:ASC6X12[c*12+j]);	//����ת��
		}
		i++;
		x=x+8;	 //�ּ�࣬8Ϊ��С
	}
}

void LOCAL_Asc6_12(unsigned char x,unsigned char y,unsigned char ch[], unsigned char *dataPtr, int isChecked)
{
	unsigned char x1, c=0, i=0, j=0;
	while (ch[i]!='\0')
	{
		x1=x/2;
		c =ch[i]-32;

		for(j=0;j<12;j++)
		{
			LOCAL_Con_4_byte(isChecked?~ASC6X12[c*12+j]:ASC6X12[c*12+j], dataPtr, x1, y+j);	//����ת��
		}
		i++;
		x+=8;	 //�ּ�࣬8Ϊ��С
	}
}

//==============================================================
//����������д��һ���׼ASCII�ַ���	 6x12
//��������ʾ��λ�ã�x,y����ch[]Ҫ��ʾ���ַ���
//���أ���
//==============================================================
void Asc6_12_Char_Checked(unsigned char x,unsigned char y,unsigned char ch[], int pos)
{
	unsigned char x1,c=0, i=0,j=0;
	while (ch[i]!='\0')
	{
		x1=x/4;
		c =ch[i]-32;
		if(x1>61)
		{
			x=0;
			x1=x/4;
			y=y+12;
		}  //����
		Set_Column_Address(Shift+x1,Shift+x1+1); // ���������꣬shiftΪ��ƫ������1322����
		Set_Row_Address(y,y+11);
		Set_Write_RAM();	 //	д�Դ�

		if(i == pos)
			for(j=0;j<12;j++)
			{
				Con_4_byte(~ASC6X12[c*12+j]);	//����ת��
			}
		else
			for(j=0;j<12;j++)
			{
				Con_4_byte(ASC6X12[c*12+j]);	//����ת��
			}
		i++;
		x+=8;	 //�ּ�࣬8Ϊ��С
	}
}

//==============================================================
//����������д��һ���׼ASCII�ַ���	 8x16
//��������ʾ��λ�ã�x,y����ch[]Ҫ��ʾ���ַ���
//���أ���
//==============================================================  
void Asc8_16(unsigned char x,unsigned char y,unsigned char ch[])
{
	unsigned char x1,c=0, i=0,j=0;
	while (ch[i]!='\0')
	{
		x1=x/4;
		c =ch[i]-32;
		if(x1>61)
		{
			x=0;
			x1=x/4;
			y=y+16;
		}  //����
		Set_Column_Address(Shift+x1,Shift+x1+1); // ���������꣬shiftΪ��ƫ������1322����
		Set_Row_Address(y,y+15);
		Set_Write_RAM();//	д�Դ�

		for(j=0;j<16;j++)
		{
			Con_4_byte(ASC8X16[c*16+j]);	//����ת��
		}
		i++;
		x=x+8;	 //�ּ�࣬8Ϊ��С
	}
}
 
//==============================================================
//����������д��һ���׼ASCII�ַ���	 12x24
//��������ʾ��λ�ã�x,y����ch[]Ҫ��ʾ���ַ���
//���أ���
//==============================================================  
void Asc12_24(unsigned char x,unsigned char y,unsigned char ch[])
{
	unsigned char x1,c=0, i=0,j=0;
	while (ch[i]!='\0')
	{
		x1=x/4;
		c =ch[i]-32;
		if(x1>59)
		{
			x=0;
			x1=x/4;
			y=y+24;
		}  //����
		Set_Column_Address(Shift+x1,Shift+x1+3); // ���������꣬shiftΪ��ƫ������1322����
		Set_Row_Address(y,y+23);
		Set_Write_RAM();	 //	д�Դ�

		for(j=0;j<48;j++)
		{
			Con_4_byte(ASC12X24[c*48+j]);	//����ת��
		}
		i++;
		x=x+12;//�ּ�࣬12Ϊ��С
	}
}

//==============================================================
//����������д��һ���׼ASCII�ַ���	 20x40	 256*64 ֻ����ʾһ��
//��������ʾ��λ�ã�x,y����ch[]Ҫ��ʾ���ַ���
//���أ���
//==============================================================  
void Asc20_40(unsigned char x,unsigned char y,unsigned char ch[])
{
	unsigned char x1,c=0, i=0,j=0;
	while (ch[i]!='\0')
	{
		x1=x/4;
		c =ch[i]-32;
		Set_Column_Address(Shift+x1,Shift+x1+5); // ���������꣬shiftΪ��ƫ������1322����
		Set_Row_Address(y,y+39);
		Set_Write_RAM();	 //	д�Դ�

		for(j=0;j<120;j++)
		{
			Con_4_byte(ASC20X40[c*120+j]);	//����ת��
		}
		i++;
		x=x+20;//�ּ�࣬20Ϊ��С
	}
}

void Show_HZ16_16_TOEC(unsigned char x,unsigned char y, unsigned char d, unsigned char num1, unsigned char num2, unsigned char *data)
{
	unsigned char i, d1;
	d1=d+16;
	for(i=num1;i<num2+1;i++)
	{
		HZ16_16_TOEC(x,y,i,data);
		x=x+d1;
	}
}

void LOCAL_Show_HZ16_16_TOEC(unsigned char x,unsigned char y, unsigned char d, unsigned char num1, unsigned char num2, unsigned char *data, void *dataPtr)
{
	unsigned char i, d1;
	d1=d+16;
	for(i=num1;i<num2+1;i++)
	{
		LOCAL_HZ16_16_TOEC(x,y,i,data, dataPtr);
		x=x+d1;
	}
}

void HZ16_16_TOEC(unsigned char x, unsigned char y, unsigned char num, unsigned char *data)
{
	unsigned char x1,j ;
	x1=x/4;
	Set_Column_Address(Shift+x1,Shift+x1+3); // ���������꣬shiftΪ��ƫ������1322������3Ϊ16/4-1
	Set_Row_Address(y,y+15);
	Set_Write_RAM();	 //	д�Դ�

	for(j=0;j<32;j++)
	{
		Con_4_byte(data[num*32+j]);
	}
}

void LOCAL_HZ16_16_TOEC(unsigned char x, unsigned char y, unsigned char num, unsigned char *data, void *dataPtr)
{
	unsigned char x1, j;
	x1=x/2;

	for(j=0;j<32;j++)
	{
		LOCAL_Con_4_byte(data[num*32+j], dataPtr, x1+4*(j%2), y+j/2);
	}
}

/***************************************************************
//  ��ʾ24*24������ 2015-05���²���ͨ��
//  ȡģ��ʽΪ������ȡģ���λ,��������:�����Ҵ��ϵ���    24�� 24��
//   num���������ֿ��е�λ��
//   x: Start Column  ��ʼ�� ��Χ 0~��255-16��
//   y: Start Row   ��ʼ�� 0~63
***************************************************************/
void HZ24_24_TOEC(unsigned char x, unsigned char y, unsigned char num, unsigned char *data)
{
	unsigned char x1,j ;
	x1=x/4;
	Set_Column_Address(Shift+x1,Shift+x1+5); // ���������꣬shiftΪ��ƫ������1322������3Ϊ16/4-1
	Set_Row_Address(y,y+23);
	Set_Write_RAM();	 //	д�Դ�

	for(j=0;j<72;j++)
	{
		Con_4_byte(data[num*72+j]);	//����24*24 ������������Ҫ����24*24��HZ24X24_K.h�� ,����24*24��HZ24X24_H.h��������Ӧ��ͷ�ļ����޸Ĵ˴�������
	}
}

//****************************************************
//   д��һ��24*24���� www.lcdsoc.com
//    num1,num2���������ֿ��е�λ��	 ��num1��ʾ��num2
//    x: Start Column  ��ʼ�� ��Χ 0~��255-16��
//    y: Start Row    ��ʼ�� 0~63
//    d:�ּ���� 0Ϊ�޼��
//    x������ּ��dҪΪ4�ı���
//*****************************************************
void Show_HZ24_24_TOEC(unsigned char x,unsigned char y, unsigned char d, unsigned char num1, unsigned char num2, unsigned char *data)
{
	unsigned char i, d1;
	d1=d+24;
	for(i=num1;i<num2+1;i++)
	{
		HZ24_24_TOEC(x,y,i,data);
		x=x+d1;
	}
}

extern struct CONFIG_POS_STRUCT *ConfigPosStruct;

void SharedMemInit()
{
	ConfigPosStruct[0].imgAddr = image_Addr;
	ConfigPosStruct[1].imgAddr = image_Mask;
	ConfigPosStruct[2].imgAddr = image_Gate;
}

void LOCAL_Fill_Line(void *dataPtr, unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
	unsigned char j;
	unsigned char *DataPtr = dataPtr;

	Set_Column_Address(Shift+a,Shift+b);
	Set_Row_Address(c,d);
	Set_Write_RAM();

	for(j=0;j<(b-a+1);j++)
	{
		OLED_WR_Byte(*DataPtr++,OLED_DATA);
	}
}

const char char_checked[] = {127, '\0'},
			char_space[] = {' ', '\0'},
			char_RisingEdge[] = {128, 129, 130, '\0'},
			char_FallingEdge[] = {131, 132, 133, '\0'};

const char *TITLE_SAMPLE_STATE[] = {"NO.", char_RisingEdge, char_FallingEdge};

extern u16 SampleState;

static unsigned char LCD_SAMPLE_STATE[64][128] = {0};

void Refresh_LCD_SAMPLE_MODE()
{
	int j;
	for(j=0;j<8;j++)
	{
		if(SampleState & (1 << j))
		{
			LOCAL_Asc5_8(31 + 10 + 28 * j, 8 + 2 * 21, char_checked, LCD_SAMPLE_STATE);
			LOCAL_Asc5_8(31 + 10 + 28 * j, 8 + 1 * 21, char_space, LCD_SAMPLE_STATE);
		}
		else
		{
			LOCAL_Asc5_8(31 + 10 + 28 * j, 8 + 1 * 21, char_checked, LCD_SAMPLE_STATE);
			LOCAL_Asc5_8(31 + 10 + 28 * j, 8 + 2 * 21, char_space, LCD_SAMPLE_STATE);
		}
	}
}

void LOCAL_LCD_SAMPLE_STATE()
{
	int s_width, e_width, s_height, e_height;
	int i, j;
	Fill_RAM(0x00);		//����
	char ch_no[5];
	//�ٷ�������ˢ��Rect������BUG 4��һˢ���º����걻ˢ�¹ʴ˴���������ѭ�� ��ˢ���ַ� ����ʱ����и������Ż�
	for(i=0;i<3;i++)
	{
		for(j=0;j<9;j++)
		{
			if(i == 0)
			{
				s_height = 0;
				e_height = 22;
			}
			else
			{
				s_height = 23 + 20 * (i - 1);
				e_height = 23 + 20 * i;
			}
			if(j == 0)
			{
				s_width = 0;
				e_width = 30;
			}
			else
			{
				s_width = 31 + 28 * (j - 1);
				e_width = 31 + 28 * j;
			}
			Draw_Rectangle_LOCAL(0xff, 1, s_width, e_width, s_height, e_height, LCD_SAMPLE_STATE);
		}
	}

	for(j=0;j<8;j++)
	{
		sprintf(ch_no, "%2d", j + 1);
		LOCAL_Asc5_8(31 + 4 + 28 * j, 8, ch_no, LCD_SAMPLE_STATE);
	}

	for(i=0;i<3;i++)
	{
		if(i==0)
			LOCAL_Asc5_8(5,8+i*20, TITLE_SAMPLE_STATE[i], LCD_SAMPLE_STATE);
		else
			LOCAL_Asc6_12(5,7+i*20, TITLE_SAMPLE_STATE[i], LCD_SAMPLE_STATE, 0);
	}
}

void Display_LCD_SAMPLE_MODE(enum LCD_STATE nstate, enum LCD_STATE cstate, int forward)
{
	int j;

	SampleState = Get_Sample_Mode();
	if(nstate != LCD_CHANGED && cstate != LCD_SAMPLE_MODE_SEL)
	{
		Refresh_LCD_SAMPLE_MODE();
		Vertical_Scroll_Local(forward, 0x01, 0, LCD_SAMPLE_STATE);
	}
	else
	{
		for(j=0;j<8;j++)
		{
			if(SampleState & (1 << j))
			{
				Asc5_8(31 + 10 + 28 * j, 8 + 2 * 21, char_checked, 0);
				Asc5_8(31 + 10 + 28 * j, 8 + 1 * 21, char_space, 0);
			}
			else
			{
				Asc5_8(31 + 10 + 28 * j, 8 + 1 * 21, char_checked, 0);
				Asc5_8(31 + 10 + 28 * j, 8 + 2 * 21, char_space, 0);
			}
		}
	}
}

void Display_LCD_SAMPLE_MODE_SEL(enum LCD_STATE nstate, int forward, int pos)
{
	SampleState = Get_Sample_Mode();
	int j;
	for(j=0;j<8;j++)
	{
		if(SampleState & (1 << j))
		{
			Asc5_8(31 + 10 + 28 * j, 8 + 2 * 21, char_checked, pos == j);
			Asc5_8(31 + 10 + 28 * j, 8 + 1 * 21, char_space, 0);
		}
		else
		{

			Asc5_8(31 + 10 + 28 * j, 8 + 1 * 21, char_checked, pos == j);
			Asc5_8(31 + 10 + 28 * j, 8 + 2 * 21, char_space, 0);
		}
	}
}

extern u32 channelStateL;

const char* DISPLAY_TITLE[] = {"NO.","TTL","HDB"};

static unsigned char LCD_CHANNEL_MAP[64][128] = {0};
void Display_LCD_CHANNEL_NORMAL(enum LCD_STATE nstate)
{
	int i, j;
	unsigned char (*DataPtr)[128] = LCD_CHANNEL_MAP;

	Fill_RAM(0x00);		//����
	for(i=0;i<=Max_Row;i++)
	{
		LOCAL_Fill_Line(DataPtr[i],0,0x7F,i,i);
	}

	for(j=0;j<8;j++)
	{
		if(channelStateL & (1 << j))
			Asc5_8(31 + 10 + 28 * j, 8 + 1 * 21, char_checked, 0);
		else
			Asc5_8(31 + 10 + 28 * j, 8 + 1 * 21, char_space, 0);
		if(channelStateL & (1 << (16 + j)))
			Asc5_8(31 + 10 + 28 * j, 8 + 2 * 21, char_checked, 0);
		else
			Asc5_8(31 + 10 + 28 * j, 8 + 2 * 21, char_space, 0);
	}
}

void Refresh_LCD_CHANNEL_Data()
{
	int j;
	for(j=0;j<8;j++)
	{
		if(channelStateL & (1 << j))
			LOCAL_Asc5_8(31 + 10 + 28 * j, 8 + 1 * 21, char_checked, LCD_CHANNEL_MAP);
		else
			LOCAL_Asc5_8(31 + 10 + 28 * j, 8 + 1 * 21, char_space, LCD_CHANNEL_MAP);
		if(channelStateL & (1 << (16 + j)))
			LOCAL_Asc5_8(31 + 10 + 28 * j, 8 + 2 * 21, char_checked, LCD_CHANNEL_MAP);
		else
			LOCAL_Asc5_8(31 + 10 + 28 * j, 8 + 2 * 21, char_space, LCD_CHANNEL_MAP);
	}
}

void Display_LCD_CHANNEL(enum LCD_STATE nstate, int forward)
{
	int j;

	if(nstate != LCD_CHANGED)
	{
		Refresh_LCD_CHANNEL_Data();
		Vertical_Scroll_Local(forward, 0x01, 0, LCD_CHANNEL_MAP);
	}
	else
	{
		for(j=0;j<8;j++)
		{
			if(channelStateL & (1 << j))
				Asc5_8(31 + 10 + 28 * j, 8 + 1 * 21, char_checked, 0);
			else
				Asc5_8(31 + 10 + 28 * j, 8 + 1 * 21, char_space, 0);
			if(channelStateL & (1 << (16 + j)))
				Asc5_8(31 + 10 + 28 * j, 8 + 2 * 21, char_checked, 0);
			else
				Asc5_8(31 + 10 + 28 * j, 8 + 2 * 21, char_space, 0);
		}
	}
}

void LOCAL_LCD_CHANNEL()
{
	int s_width, e_width, s_height, e_height;
	int i, j;
	Fill_RAM(0x00);		//����
	char ch_no[5];
	//�ٷ�������ˢ��Rect������BUG 4��һˢ���º����걻ˢ�¹ʴ˴���������ѭ�� ��ˢ���ַ� ����ʱ����и������Ż�
	for(i=0;i<3;i++)
	{
		for(j=0;j<9;j++)
		{
			if(i == 0)
			{
				s_height = 0;
				e_height = 22;
			}
			else
			{
				s_height = 23 + 20 * (i - 1);
				e_height = 23 + 20 * i;
			}
			if(j == 0)
			{
				s_width = 0;
				e_width = 30;
			}
			else
			{
				s_width = 31 + 28 * (j - 1);
				e_width = 31 + 28 * j;
			}
			Draw_Rectangle_LOCAL(0xff, 1, s_width, e_width, s_height, e_height, LCD_CHANNEL_MAP);
		}
	}

	for(j=0;j<8;j++)
	{
		sprintf(ch_no, "%2d", j + 1);
		LOCAL_Asc5_8(31 + 4 + 28 * j, 8, ch_no, LCD_CHANNEL_MAP);
	}

	for(i=0;i<3;i++)
	{
		LOCAL_Asc5_8(6,8+i*21, DISPLAY_TITLE[i], LCD_CHANNEL_MAP);
	}

	Refresh_LCD_CHANNEL_Data();
}

void Vertical_Scroll_Local(unsigned char a, unsigned char b, unsigned char c, void *dataPtr)
{
	unsigned char i,j;
	unsigned char (*DataPtr)[128] = dataPtr;
	Set_Partial_Display(0x00,0x00,Max_Row);
	switch(a)
	{
		case 0:
			for(i=0;i<=Max_Row;i+=b)
			{
				LOCAL_Fill_Line_One_Ch(0,0,0x7F,i,i);
				Set_Display_Offset(i+1);
				LOCAL_Fill_Line(DataPtr[i],0,0x7F,i,i);
				for(j=0;j<c;j++)
				{
					delay_us(200);
				}
			}
			break;
		case 1:
			for(i=0;i<=Max_Row;i+=b)
			{
				LOCAL_Fill_Line_One_Ch(0,0,0x7F,Max_Row-i,Max_Row-i);
				Set_Display_Offset(Max_Row-i);
				LOCAL_Fill_Line(DataPtr[Max_Row-i],0x00,0x7F,Max_Row-i,Max_Row-i);
				for(j=0;j<c;j++)
				{
					delay_us(200);
				}
			}
			break;
	}
	Set_Partial_Display(0x01,0x00,0x00);
}

static unsigned char LCD_NET_CONFIG_MAP[64][128] = {0};

void Refresh_LCD_NET_CONFIG_Data(int selectedIndex, int isLocal)
{
	char c_data[20];
	int i;
	for(i=0;i<3;i++)
	{
		sprintf(c_data,"%3d. %3d. %3d. %3d", ConfigPosStruct[i].s_data[0],
											ConfigPosStruct[i].s_data[1],
											ConfigPosStruct[i].s_data[2],
											ConfigPosStruct[i].s_data[3]);
		if(isLocal)
			LOCAL_Asc6_12(109,8+i*21, c_data, LCD_NET_CONFIG_MAP, i == selectedIndex);
		else
			Asc6_12(109,8+i*21, c_data, i == selectedIndex);
	}
}

void Display_LCD_NET_CONFIG(int selectedIndex, enum LCD_STATE cstate, int forward)
{
	if(cstate == LCD_CHANNEL || cstate == LCD_SAMPLE_MODE)
	{
		Refresh_LCD_NET_CONFIG_Data(selectedIndex, 1);
		Vertical_Scroll_Local(forward, 0x01, 0, LCD_NET_CONFIG_MAP);
	}
	else
	{
		Refresh_LCD_NET_CONFIG_Data(selectedIndex, 0);
	}
}

void LOCAL_LCD_NET_CONFIG(int selectedIndex)
{
	char c_data[20];
	int i;
	for(i=0;i<3;i++)
	{
		LOCAL_Show_HZ16_16_TOEC(8, 4+i*21, 4, 0, 4, ConfigPosStruct[i].imgAddr, LCD_NET_CONFIG_MAP);	// ���꣨64��17�����ּ��4���ֿ��0~3�����¿Ƽ�����16*16����
	}
}

void Display_LCD_CONFIG_CHECKED(enum LCD_STATE selectedIndex, int pos)
{
	char c_data[20];
	sprintf(c_data,"%3d. %3d. %3d. %3d",ConfigPosStruct[selectedIndex].s_data[0],
										ConfigPosStruct[selectedIndex].s_data[1],
										ConfigPosStruct[selectedIndex].s_data[2],
										ConfigPosStruct[selectedIndex].s_data[3]);
	Asc6_12_Char_Checked(109, 8+selectedIndex*21, c_data, pos);
}

void Display_TOEC_LOGO()//���LOGO
{
	LOCAL_LCD_NET_CONFIG(0);
	LOCAL_LCD_CHANNEL();
	LOCAL_LCD_SAMPLE_STATE();
	Fill_RAM(0x00);		//����
	Show_Pattern(gImage_TOEC,2,17,0,63);	 //��ʾ��ɫͼ��ȡģ����16�Ҷ�ȡģ
	Show_HZ16_16_TOEC(80,17,4,0,7, HZ16X16_TOEC_S1);	// ���꣨64��17�����ּ��4���ֿ��0~3�����¿Ƽ�����16*16����
	Show_HZ16_16_TOEC(121,40,4,0,3, HZ16X16_TOEC_S2);	// ���꣨64��17�����ּ��4���ֿ��0~3�����¿Ƽ�����16*16����
}

