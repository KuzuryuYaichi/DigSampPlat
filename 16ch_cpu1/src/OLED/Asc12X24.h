// ------------------  ASCII��ģ�����ݱ� ------------------------ //
// �����0x20~0x7e                                                //
// �ֿ�:  ʵ�ʵ��� 16*24��������빲12�У��ҿ�4�У��ϼ�16�� 24��
// ȡģ��SSD1322������ ����ȡģ���λ 
//�����ߣ�www/lcdsoc.com
// -------------------------------------------------------------- //

#ifndef SRC_OLED_ASC12X24_H_
#define SRC_OLED_ASC12X24_H_

unsigned char ASC12X24[] =              // ASCII
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // - -
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x02,0x00,0x07,0x00,0x07,0x00,  // -!-
	0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,
	0x07,0x00,0x07,0x00,0x02,0x00,0x02,0x00,
	0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,
	0x02,0x00,0x00,0x00,0x00,0x00,0x02,0x00,
	0x07,0x00,0x07,0x00,0x02,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x39,0xC0,0x39,0xC0,  // -"-
	0x39,0xC0,0x10,0x80,0x10,0x80,0x10,0x80,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -#-
	0x01,0x80,0x31,0x80,0x31,0x80,0x31,0xE0,
	0x3F,0x80,0xF1,0x80,0x31,0x80,0x31,0x80,
	0x31,0x80,0x31,0xE0,0x3F,0x80,0xF1,0x80,
	0x31,0x80,0x31,0x80,0x31,0x80,0x31,0x80,
	0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x06,0x00,0x06,0x00,  // -$-
	0x3F,0xC0,0x66,0x60,0xC6,0x30,0xC6,0x30,
	0xC6,0x00,0xC6,0x00,0x66,0x00,0x3E,0x00,
	0x0F,0x80,0x07,0xC0,0x06,0x60,0x06,0x30,
	0xC6,0x30,0xC6,0x30,0xC6,0x30,0x66,0x60,
	0x3F,0xC0,0x06,0x00,0x06,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x30,0x00,0x48,0x20,  // -%-
	0xCC,0x60,0xCC,0x40,0xCC,0xC0,0xCC,0x80,
	0xCD,0x80,0x4B,0x00,0x32,0x00,0x06,0x00,
	0x04,0x00,0x0C,0x00,0x09,0x80,0x1A,0x40,
	0x36,0x60,0x26,0x60,0x66,0x60,0x46,0x60,
	0xC6,0x60,0x82,0x40,0x01,0x80,0x00,0x00,

	0x00,0x00,0x00,0x00,0x1C,0x00,0x22,0x00,  // -&-
	0x42,0x00,0x42,0x00,0x42,0x00,0x64,0x00,
	0x28,0x00,0x30,0x00,0x38,0x00,0x48,0x00,
	0x4C,0x00,0xC4,0x00,0xC6,0x70,0xC3,0x20,
	0xC3,0x20,0xC1,0xC0,0xC0,0xC0,0xC1,0xC0,
	0x67,0x60,0x3C,0x30,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x07,0x00,0x07,0x00,  // -'-
	0x07,0x00,0x07,0x00,0x02,0x00,0x02,0x00,
	0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x20,0x00,0x40,0x00,0x80,0x01,0x80,  // -(-
	0x01,0x00,0x03,0x00,0x03,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x03,0x00,0x03,0x00,0x01,0x00,
	0x01,0x80,0x00,0x80,0x00,0x40,0x00,0x20,

	0x40,0x00,0x20,0x00,0x10,0x00,0x18,0x00,  // -)-
	0x08,0x00,0x0C,0x00,0x0C,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x0C,0x00,0x0C,0x00,0x08,0x00,
	0x18,0x00,0x10,0x00,0x20,0x00,0x40,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -*-
	0x04,0x00,0x0E,0x00,0x0E,0x00,0xC4,0x60,
	0xE4,0xE0,0x64,0xC0,0x11,0x00,0x00,0x00,
	0x00,0x00,0x11,0x00,0x64,0xC0,0xE4,0xE0,
	0xC4,0x60,0x0E,0x00,0x0E,0x00,0x04,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -+-
	0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x7F,0xE0,
	0x7F,0xE0,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -,-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x0C,0x00,0x1E,0x00,0x1E,0x00,
	0x0E,0x00,0x06,0x00,0x0C,0x00,0x18,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // ---
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xE0,
	0x7F,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -.-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x0C,0x00,0x1E,0x00,
	0x1E,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x20,0x00,0x60,0x00,0x40,  // -/-
	0x00,0xC0,0x00,0x80,0x01,0x80,0x01,0x00,
	0x03,0x00,0x02,0x00,0x06,0x00,0x04,0x00,
	0x0C,0x00,0x08,0x00,0x18,0x00,0x10,0x00,
	0x30,0x00,0x20,0x00,0x60,0x00,0x40,0x00,
	0xC0,0x00,0x80,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x0E,0x00,0x1B,0x00,  // -0-
	0x31,0x80,0x31,0x80,0x60,0xC0,0x60,0xC0,
	0xC0,0x60,0xC0,0x60,0xC0,0x60,0xC0,0x60,
	0xC0,0x60,0xC0,0x60,0xC0,0x60,0xC0,0x60,
	0x60,0xC0,0x60,0xC0,0x31,0x80,0x31,0x80,
	0x1B,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x06,0x00,0x1E,0x00,  // -1-
	0x7E,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x3F,0xC0,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x1F,0x00,0x31,0x80,  // -2-
	0x60,0xC0,0xE0,0x60,0xE0,0x60,0x60,0x60,
	0x00,0x60,0x00,0xC0,0x00,0xC0,0x01,0x80,
	0x03,0x00,0x06,0x00,0x0C,0x00,0x18,0x00,
	0x30,0x00,0x70,0x00,0x60,0x20,0xE0,0x20,
	0xFF,0xE0,0xFF,0xE0,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x0F,0x00,0x39,0xC0,  // -3-
	0x70,0xE0,0x70,0x60,0x30,0x60,0x00,0x60,
	0x00,0xC0,0x01,0x80,0x03,0x00,0x0E,0x00,
	0x03,0x80,0x00,0xC0,0x00,0x60,0x00,0x60,
	0x00,0x60,0x60,0x60,0xE0,0x60,0xE0,0xE0,
	0x71,0xC0,0x3F,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x01,0x80,0x03,0x80,  // -4-
	0x03,0x80,0x07,0x80,0x05,0x80,0x0D,0x80,
	0x09,0x80,0x19,0x80,0x11,0x80,0x31,0x80,
	0x21,0x80,0x61,0x80,0x41,0x80,0xC1,0x80,
	0xFF,0xF0,0x01,0x80,0x01,0x80,0x01,0x80,
	0x01,0x80,0x07,0xE0,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x7F,0xC0,0x7F,0xC0,  // -5-
	0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,
	0x60,0x00,0x67,0x00,0x69,0x80,0x70,0xC0,
	0x40,0xC0,0x00,0x60,0x00,0x60,0x00,0x60,
	0x00,0x60,0x60,0x60,0xE0,0xC0,0xE0,0xC0,
	0x71,0x80,0x3F,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x1F,0x00,0x33,0x80,  // -6-
	0x61,0xC0,0x61,0xC0,0xC1,0x80,0xC0,0x00,
	0xC0,0x00,0xCF,0x00,0xD1,0x80,0xE0,0xC0,
	0xC0,0xC0,0xC0,0x60,0xC0,0x60,0xC0,0x60,
	0xC0,0x60,0xC0,0x60,0x60,0xC0,0x60,0xC0,
	0x31,0x80,0x1F,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x7F,0xE0,0xFF,0xE0,  // -7-
	0xC0,0x60,0x80,0x40,0x80,0xC0,0x00,0x80,
	0x01,0x80,0x01,0x00,0x03,0x00,0x03,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x0C,0x00,
	0x0C,0x00,0x0C,0x00,0x0C,0x00,0x0C,0x00,
	0x0C,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x1F,0x00,0x31,0x80,  // -8-
	0x60,0xC0,0x60,0xC0,0x60,0xC0,0x60,0xC0,
	0x31,0x80,0x1B,0x00,0x0E,0x00,0x1F,0x00,
	0x31,0x80,0x60,0xC0,0xC0,0x60,0xC0,0x60,
	0xC0,0x60,0xC0,0x60,0xC0,0x60,0x60,0xC0,
	0x31,0x80,0x1F,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x1F,0x00,0x31,0x80,  // -9-
	0x60,0xC0,0x60,0xC0,0xC0,0x60,0xC0,0x60,
	0xC0,0x60,0xC0,0x60,0xC0,0x60,0x60,0x60,
	0x60,0xE0,0x31,0x60,0x1E,0x60,0x00,0x60,
	0x00,0x60,0x30,0x60,0x70,0xC0,0x70,0xC0,
	0x39,0x80,0x1F,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -:-
	0x00,0x00,0x00,0x00,0x06,0x00,0x0F,0x00,
	0x0F,0x00,0x06,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x06,0x00,0x0F,0x00,
	0x0F,0x00,0x06,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -;-
	0x00,0x00,0x00,0x00,0x06,0x00,0x0F,0x00,
	0x0F,0x00,0x06,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x06,0x00,0x0F,0x00,
	0x0F,0x00,0x07,0x00,0x03,0x00,0x06,0x00,
	0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,  // -<-
	0x00,0xC0,0x01,0x80,0x03,0x00,0x06,0x00,
	0x0C,0x00,0x18,0x00,0x30,0x00,0x60,0x00,
	0xC0,0x00,0x60,0x00,0x30,0x00,0x18,0x00,
	0x0C,0x00,0x06,0x00,0x03,0x00,0x01,0x80,
	0x00,0xC0,0x00,0x60,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -=-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x7F,0xE0,0x7F,0xE0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x7F,0xE0,0x7F,0xE0,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,  // ->-
	0x60,0x00,0x30,0x00,0x18,0x00,0x0C,0x00,
	0x06,0x00,0x03,0x00,0x01,0x80,0x00,0xC0,
	0x00,0x60,0x00,0xC0,0x01,0x80,0x03,0x00,
	0x06,0x00,0x0C,0x00,0x18,0x00,0x30,0x00,
	0x60,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x0F,0x80,0x18,0xC0,  // -?-
	0x30,0x60,0x70,0x60,0x70,0x60,0x20,0x60,
	0x00,0xC0,0x00,0xC0,0x01,0x80,0x01,0x00,
	0x03,0x00,0x02,0x00,0x02,0x00,0x02,0x00,
	0x02,0x00,0x00,0x00,0x00,0x00,0x02,0x00,
	0x07,0x00,0x07,0x00,0x02,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x1F,0x00,0x20,0x80,  // -@-
	0x40,0x40,0x80,0x20,0x8F,0x20,0x99,0xA0,
	0xB1,0xA0,0xB1,0xA0,0xB1,0xA0,0xB1,0xA0,
	0xB1,0xA0,0xB1,0xA0,0xB1,0xA0,0xBF,0xA0,
	0x9C,0xC0,0x80,0x00,0x80,0x00,0x40,0x20,
	0x20,0x40,0x1F,0x80,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x06,0x00,0x06,0x00,  // -A-
	0x0B,0x00,0x0B,0x00,0x09,0x00,0x09,0x00,
	0x19,0x80,0x19,0x80,0x10,0x80,0x10,0x80,
	0x30,0xC0,0x30,0xC0,0x3F,0xC0,0x30,0xC0,
	0x20,0x40,0x60,0x60,0x60,0x60,0x60,0x60,
	0x60,0x60,0xF0,0xF0,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0xFE,0x00,0x63,0x00,  // -B-
	0x61,0x80,0x60,0xC0,0x60,0xC0,0x60,0xC0,
	0x60,0xC0,0x61,0x80,0x63,0x00,0x7E,0x00,
	0x63,0x80,0x60,0xC0,0x60,0xC0,0x60,0x60,
	0x60,0x60,0x60,0x60,0x60,0xC0,0x60,0xC0,
	0x61,0x80,0xFF,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x1F,0x20,0x31,0xE0,  // -C-
	0x60,0xE0,0x60,0x60,0xC0,0x20,0xC0,0x00,
	0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,
	0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,
	0xC0,0x00,0xC0,0x60,0x60,0x60,0x60,0xC0,
	0x31,0x80,0x1F,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0xFE,0x00,0x63,0x00,  // -D-
	0x61,0x80,0x60,0xC0,0x60,0xC0,0x60,0x60,
	0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,
	0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,
	0x60,0x60,0x60,0xC0,0x60,0xC0,0x61,0x80,
	0x63,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0xFF,0xE0,0x60,0xE0,  // -E-
	0x60,0x60,0x60,0x20,0x60,0x20,0x60,0x00,
	0x61,0x00,0x61,0x00,0x63,0x00,0x7F,0x00,
	0x63,0x00,0x61,0x00,0x61,0x00,0x60,0x00,
	0x60,0x00,0x60,0x20,0x60,0x20,0x60,0x60,
	0x60,0xE0,0xFF,0xE0,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0xFF,0xE0,0x60,0xE0,  // -F-
	0x60,0x60,0x60,0x20,0x60,0x20,0x60,0x00,
	0x61,0x00,0x61,0x00,0x63,0x00,0x7F,0x00,
	0x63,0x00,0x61,0x00,0x61,0x00,0x60,0x00,
	0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,
	0x60,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x1E,0x40,0x33,0xC0,  // -G-
	0x60,0xC0,0x60,0x40,0xC0,0x40,0xC0,0x00,
	0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC1,0xE0,
	0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
	0xC0,0xC0,0xC0,0xC0,0x61,0xC0,0x63,0xC0,
	0x36,0xC0,0x1C,0xC0,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0xF1,0xE0,0x60,0xC0,  // -H-
	0x60,0xC0,0x60,0xC0,0x60,0xC0,0x60,0xC0,
	0x60,0xC0,0x60,0xC0,0x60,0xC0,0x7F,0xC0,
	0x60,0xC0,0x60,0xC0,0x60,0xC0,0x60,0xC0,
	0x60,0xC0,0x60,0xC0,0x60,0xC0,0x60,0xC0,
	0x60,0xC0,0xF1,0xE0,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x1F,0xE0,0x03,0x00,  // -I-
	0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,
	0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,
	0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,
	0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,
	0x03,0x00,0x1F,0xE0,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x07,0xE0,0x01,0x80,  // -J-
	0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,
	0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,
	0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,
	0x61,0x80,0xF1,0x80,0xE1,0x80,0xC1,0x80,
	0x67,0x00,0x3E,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0xF3,0xE0,0x61,0x80,  // -K-
	0x61,0x80,0x63,0x00,0x63,0x00,0x66,0x00,
	0x66,0x00,0x6C,0x00,0x6C,0x00,0x7C,0x00,
	0x7C,0x00,0x76,0x00,0x76,0x00,0x63,0x00,
	0x63,0x00,0x61,0x80,0x61,0x80,0x60,0xC0,
	0x60,0xC0,0xF1,0xF0,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0xF0,0x00,0x60,0x00,  // -L-
	0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,
	0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,
	0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,
	0x60,0x00,0x60,0x20,0x60,0x20,0x60,0x60,
	0x60,0xE0,0xFF,0xE0,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0xE0,0x70,0x60,0x60,  // -M-	www/lcdsoc.com
	0x60,0x60,0x60,0x60,0x70,0xE0,0x70,0xE0,
	0x70,0xE0,0x70,0xE0,0x79,0xE0,0x69,0x60,
	0x69,0x60,0x6F,0x60,0x66,0x60,0x66,0x60,
	0x66,0x60,0x60,0x60,0x60,0x60,0x60,0x60,
	0x60,0x60,0xF0,0xF0,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0xE1,0xE0,0x60,0xC0,  // -N-
	0x60,0xC0,0x70,0xC0,0x70,0xC0,0x70,0xC0,
	0x78,0xC0,0x68,0xC0,0x6C,0xC0,0x64,0xC0,
	0x66,0xC0,0x62,0xC0,0x63,0xC0,0x61,0xC0,
	0x61,0xC0,0x61,0xC0,0x60,0xC0,0x60,0xC0,
	0x60,0x40,0xF0,0x40,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x1F,0x00,0x31,0x80,  // -O-
	0x60,0xC0,0xC0,0x60,0xC0,0x60,0xC0,0x60,
	0xC0,0x60,0xC0,0x60,0xC0,0x60,0xC0,0x60,
	0xC0,0x60,0xC0,0x60,0xC0,0x60,0xC0,0x60,
	0xC0,0x60,0xC0,0x60,0xC0,0x60,0x60,0xC0,
	0x31,0x80,0x1F,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0xFE,0x00,0x63,0x80,  // -P-
	0x60,0xC0,0x60,0xC0,0x60,0x60,0x60,0x60,
	0x60,0x60,0x60,0xC0,0x60,0xC0,0x63,0x80,
	0x7E,0x00,0x60,0x00,0x60,0x00,0x60,0x00,
	0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,
	0x60,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x1F,0x00,0x31,0x80,  // -Q-
	0x60,0xC0,0xC0,0x60,0xC0,0x60,0xC0,0x60,
	0xC0,0x60,0xC0,0x60,0xC0,0x60,0xC0,0x60,
	0xC0,0x60,0xC0,0x60,0xC0,0x60,0xC0,0x60,
	0xC0,0x60,0xCC,0x60,0xC6,0x60,0x63,0x60,
	0x31,0xC0,0x1E,0xC0,0x00,0x70,0x00,0x00,

	0x00,0x00,0x00,0x00,0xFE,0x00,0x63,0x80,  // -R-
	0x61,0x80,0x60,0xC0,0x60,0xC0,0x60,0xC0,
	0x60,0xC0,0x61,0x80,0x63,0x80,0x7E,0x00,
	0x6C,0x00,0x6C,0x00,0x66,0x00,0x66,0x00,
	0x63,0x00,0x63,0x00,0x61,0x80,0x61,0x80,
	0x60,0xC0,0xF1,0xE0,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x1E,0x40,0x73,0xC0,  // -S-
	0xC1,0xC0,0xC0,0xC0,0xC0,0x40,0xE0,0x00,
	0x70,0x00,0x38,0x00,0x1C,0x00,0x0E,0x00,
	0x07,0x00,0x03,0x80,0x01,0xC0,0x00,0xE0,
	0x80,0x60,0xC0,0x60,0xE0,0x60,0xF0,0xC0,
	0xD9,0x80,0x8F,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0xFF,0xF0,0xE6,0x70,  // -T-
	0xC6,0x30,0x86,0x10,0x86,0x10,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x1F,0x80,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0xF1,0xE0,0x60,0xC0,  // -U-
	0x60,0xC0,0x60,0xC0,0x60,0xC0,0x60,0xC0,
	0x60,0xC0,0x60,0xC0,0x60,0xC0,0x60,0xC0,
	0x60,0xC0,0x60,0xC0,0x60,0xC0,0x60,0xC0,
	0x60,0xC0,0x60,0xC0,0x60,0xC0,0x60,0xC0,
	0x31,0x80,0x1F,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0xF1,0xE0,0x60,0xC0,  // -V-
	0x60,0xC0,0x60,0xC0,0x60,0xC0,0x60,0xC0,
	0x31,0x80,0x31,0x80,0x31,0x80,0x31,0x80,
	0x31,0x80,0x31,0x80,0x1B,0x00,0x1B,0x00,
	0x1B,0x00,0x1B,0x00,0x0E,0x00,0x0E,0x00,
	0x0E,0x00,0x04,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0xF0,0xF0,0x60,0x60,  // -W-
	0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,
	0x60,0x60,0x60,0x60,0x26,0x40,0x26,0x40,
	0x26,0x40,0x26,0x40,0x26,0x40,0x36,0xC0,
	0x36,0xC0,0x36,0xC0,0x19,0x80,0x19,0x80,
	0x19,0x80,0x19,0x80,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0xF0,0xF0,0x60,0x60,  // -X-
	0x60,0x60,0x30,0xC0,0x30,0xC0,0x19,0x80,
	0x19,0x80,0x0F,0x00,0x0F,0x00,0x06,0x00,
	0x06,0x00,0x0F,0x00,0x0F,0x00,0x19,0x80,
	0x19,0x80,0x30,0xC0,0x30,0xC0,0x60,0x60,
	0x60,0x60,0xF0,0xF0,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0xF0,0xF0,0x60,0x60,  // -Y-
	0x60,0x60,0x30,0xC0,0x30,0xC0,0x30,0xC0,
	0x19,0x80,0x19,0x80,0x19,0x80,0x0F,0x00,
	0x0F,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x1F,0x80,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0xFF,0xC0,0xE0,0xC0,  // -Z-
	0xC1,0xC0,0x81,0x80,0x83,0x00,0x03,0x00,
	0x06,0x00,0x06,0x00,0x0C,0x00,0x0C,0x00,
	0x18,0x00,0x18,0x00,0x30,0x00,0x30,0x00,
	0x60,0x00,0x60,0x20,0xC0,0x20,0xC0,0x60,
	0xC0,0xE0,0xFF,0xE0,0x00,0x00,0x00,0x00,

	0x07,0xE0,0x04,0x00,0x04,0x00,0x04,0x00,  // -[-
	0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,
	0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,
	0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,
	0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,
	0x04,0x00,0x04,0x00,0x04,0x00,0x07,0xE0,

	0x00,0x00,0x80,0x00,0xC0,0x00,0x40,0x00,  // -\-
	0x60,0x00,0x20,0x00,0x30,0x00,0x10,0x00,
	0x18,0x00,0x08,0x00,0x0C,0x00,0x04,0x00,
	0x06,0x00,0x02,0x00,0x03,0x00,0x01,0x00,
	0x01,0x80,0x00,0x80,0x00,0xC0,0x00,0x40,
	0x00,0x60,0x00,0x20,0x00,0x00,0x00,0x00,

	0x7E,0x00,0x02,0x00,0x02,0x00,0x02,0x00,  // -]-
	0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,
	0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,
	0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,
	0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,
	0x02,0x00,0x02,0x00,0x02,0x00,0x7E,0x00,

	0x00,0x00,0x06,0x00,0x0F,0x00,0x19,0x80,  // -^-
	0x30,0xC0,0x60,0x60,0x40,0x20,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -_-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xF0,

	0x18,0x00,0x3C,0x00,0x0F,0x00,0x01,0xC0,  // -`-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -a-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x3F,0x00,0x61,0x80,0xF0,0xC0,
	0x60,0xC0,0x00,0xC0,0x0F,0xC0,0x38,0xC0,
	0x60,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
	0xE3,0xC0,0x3E,0x60,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0xE0,0x00,0x60,0x00,  // -b-
	0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,
	0x60,0x00,0x6F,0x00,0x79,0x80,0x70,0xC0,
	0x60,0xC0,0x60,0x60,0x60,0x60,0x60,0x60,
	0x60,0x60,0x60,0x60,0x60,0xC0,0x70,0xC0,
	0x79,0x80,0xCF,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -c-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x1F,0x00,0x31,0xC0,0x60,0xE0,
	0x61,0xE0,0xC0,0xC0,0xC0,0x00,0xC0,0x00,
	0xC0,0x00,0xC0,0x00,0x60,0x00,0x60,0x60,
	0x30,0xC0,0x1F,0x80,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0xE0,0x00,0x60,  // -d-
	0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,
	0x00,0x60,0x1F,0x60,0x31,0xE0,0x60,0xE0,
	0x60,0x60,0xC0,0x60,0xC0,0x60,0xC0,0x60,
	0xC0,0x60,0xC0,0x60,0x60,0x60,0x60,0xE0,
	0x31,0xE0,0x1F,0x20,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -e-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x1F,0x00,0x31,0x80,0x60,0xC0,
	0x60,0xC0,0xC0,0x60,0xC0,0x60,0xFF,0xE0,
	0xC0,0x00,0xC0,0x00,0x60,0x00,0x60,0x60,
	0x30,0xC0,0x1F,0x80,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x07,0xC0,0x0C,0xE0,  // -f-
	0x18,0xE0,0x18,0x40,0x18,0x00,0x18,0x00,
	0x18,0x00,0xFF,0x00,0x18,0x00,0x18,0x00,
	0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,
	0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,
	0x18,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -g-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x3E,0x60,0x63,0xE0,0xC1,0x80,
	0xC1,0x80,0xC1,0x80,0x63,0x00,0x3E,0x00,
	0x60,0x00,0x78,0x00,0xCF,0x80,0xC1,0xC0,
	0xC0,0x60,0xC0,0x60,0x60,0xC0,0x3F,0x80,

	0x00,0x00,0x00,0x00,0xE0,0x00,0x60,0x00,  // -h-
	0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,
	0x60,0x00,0x67,0x00,0x6D,0x80,0x78,0xC0,
	0x70,0xC0,0x60,0xC0,0x60,0xC0,0x60,0xC0,
	0x60,0xC0,0x60,0xC0,0x60,0xC0,0x60,0xC0,
	0x60,0xC0,0xF1,0xE0,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x06,0x00,0x0F,0x00,  // -i-
	0x0F,0x00,0x06,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x1E,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x1F,0x80,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x03,0x00,0x07,0x80,  // -j-  www/lcdsoc.com
	0x07,0x80,0x03,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x07,0x80,0x01,0x80,0x01,0x80,
	0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,
	0x01,0x80,0x01,0x80,0x01,0x80,0x61,0x80,
	0xF1,0x80,0xE1,0x80,0x63,0x00,0x3E,0x00,

	0x00,0x00,0x00,0x00,0xE0,0x00,0x60,0x00,  // -k-
	0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,
	0x60,0x00,0x63,0xE0,0x61,0x80,0x63,0x00,
	0x66,0x00,0x6C,0x00,0x7E,0x00,0x76,0x00,
	0x63,0x00,0x63,0x00,0x61,0x80,0x61,0x80,
	0x60,0xC0,0xF1,0xE0,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x1E,0x00,0x06,0x00,  // -l-
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x1F,0x80,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -m-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0xED,0xC0,0x7F,0xE0,0x66,0x60,
	0x66,0x60,0x66,0x60,0x66,0x60,0x66,0x60,
	0x66,0x60,0x66,0x60,0x66,0x60,0x66,0x60,
	0x66,0x60,0xF7,0x70,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -n-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0xE7,0x00,0x6D,0x80,0x78,0xC0,
	0x70,0xC0,0x60,0xC0,0x60,0xC0,0x60,0xC0,
	0x60,0xC0,0x60,0xC0,0x60,0xC0,0x60,0xC0,
	0x60,0xC0,0xF1,0xE0,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -o-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x1F,0x00,0x31,0x80,0x60,0xC0,
	0x60,0xC0,0xC0,0x60,0xC0,0x60,0xC0,0x60,
	0xC0,0x60,0xC0,0x60,0x60,0xC0,0x60,0xC0,
	0x31,0x80,0x1F,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -p-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0xEF,0x00,0x79,0x80,0x70,0xC0,
	0x60,0xC0,0x60,0x60,0x60,0x60,0x60,0x60,
	0x60,0xC0,0x70,0xC0,0x79,0x80,0x6F,0x00,
	0x60,0x00,0x60,0x00,0x60,0x00,0xF0,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -q-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x1E,0x40,0x33,0xC0,0x61,0xC0,
	0x60,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
	0x60,0xC0,0x61,0xC0,0x33,0xC0,0x1E,0xC0,
	0x00,0xC0,0x00,0xC0,0x00,0xC0,0x01,0xE0,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -r-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0xE7,0x80,0x6C,0xC0,0x78,0xE0,
	0x70,0xC0,0x60,0x00,0x60,0x00,0x60,0x00,
	0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,
	0x60,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -s-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x3F,0x00,0x61,0xC0,0xC0,0xC0,
	0xC0,0x40,0xE0,0x00,0x78,0x00,0x1F,0x00,
	0x03,0xC0,0x00,0xE0,0x80,0x60,0xC0,0x60,
	0xE0,0xC0,0x3F,0x80,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -t-
	0x08,0x00,0x18,0x00,0x18,0x00,0x18,0x00,
	0x18,0x00,0xFF,0xC0,0x18,0x00,0x18,0x00,
	0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,
	0x18,0x00,0x18,0x00,0x18,0x60,0x18,0x60,
	0x0C,0xC0,0x07,0x80,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -u-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0xE1,0xC0,0x60,0xC0,0x60,0xC0,
	0x60,0xC0,0x60,0xC0,0x60,0xC0,0x60,0xC0,
	0x60,0xC0,0x60,0xC0,0x61,0xC0,0x63,0xC0,
	0x36,0xC0,0x1C,0xE0,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -v-   www/lcdsoc.com
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0xF1,0xE0,0x60,0xC0,0x60,0xC0,
	0x31,0x80,0x31,0x80,0x31,0x80,0x1B,0x00,
	0x1B,0x00,0x1B,0x00,0x0E,0x00,0x0E,0x00,
	0x0E,0x00,0x04,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -w-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0xF0,0xF0,0x60,0x60,0x60,0x60,
	0x66,0x60,0x66,0x60,0x36,0xC0,0x36,0xC0,
	0x36,0xC0,0x3F,0xC0,0x19,0x80,0x19,0x80,
	0x19,0x80,0x19,0x80,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -x-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0xF1,0xE0,0x60,0xC0,0x60,0xC0,
	0x31,0x80,0x1B,0x00,0x0E,0x00,0x0E,0x00,
	0x0E,0x00,0x1B,0x00,0x31,0x80,0x60,0xC0,
	0x60,0xC0,0xF1,0xE0,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -y-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0xF1,0xE0,0x60,0xC0,0x30,0xC0,
	0x31,0x80,0x19,0x80,0x19,0x80,0x0F,0x00,
	0x0F,0x00,0x07,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0xCC,0x00,0xCC,0x00,0x78,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -z-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x7F,0xE0,0x40,0x60,0x40,0xC0,
	0x01,0x80,0x03,0x00,0x06,0x00,0x0C,0x00,
	0x18,0x00,0x30,0x00,0x60,0x20,0xC0,0x20,
	0xC0,0x60,0xFF,0xE0,0x00,0x00,0x00,0x00,

	0x01,0xE0,0x03,0x00,0x06,0x00,0x06,0x00,  // -{-
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x0C,0x00,0x18,0x00,
	0x18,0x00,0x0C,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x03,0x00,0x01,0xE0,

	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,  // -|-
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,

	0x78,0x00,0x0C,0x00,0x06,0x00,0x06,0x00,  // -}-
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x03,0x00,0x01,0x80,
	0x01,0x80,0x03,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,
	0x06,0x00,0x06,0x00,0x0C,0x00,0x78,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -~-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x38,0x00,0x6C,0x30,
	0xC3,0x60,0x01,0xC0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // -- www/lcdsoc.com
	0x04,0x00,0x04,0x00,0x0E,0x00,0x0A,0x00,
	0x1B,0x00,0x11,0x00,0x31,0x80,0x20,0x80,
	0x60,0xC0,0x40,0x40,0xC0,0x60,0xFF,0xE0,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

#endif