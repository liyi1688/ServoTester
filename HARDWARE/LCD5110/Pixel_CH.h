/**********************************************************
 * @file     Pixel_CH.h
 * @brief    汉字取模
 * @author   Liyi
 * @version  V1.0
 * @date     2018.5.31
 * @note	宋体12号
 *			16*16
 *			纵向取模
 *			字节倒序
 * @par	
 * Copyright (C) 2018 SLDX Limited. All rights reserved.
 **********************************************************/
#ifndef _PIXEL_CH_H
#define _PIXEL_CH_H


//宋体12号
//16*16
//纵向取模
//字节倒序
u8 chinese_character[][5][32]=
{
	{
		/*--  文字:  舵  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x80,0x80,0xFC,0x96,0xE5,0x84,0xFC,0x00,0x38,0xC8,0x09,0x0E,0x08,0xA8,0x18,0x00,
		0x80,0x60,0x1F,0x02,0x4C,0x80,0x7F,0x00,0x00,0x3F,0x44,0x42,0x41,0x40,0x78,0x00,

		/*--  文字:  机  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x10,0x10,0xD0,0xFF,0x90,0x10,0x00,0xFE,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,
		0x04,0x03,0x00,0xFF,0x00,0x83,0x60,0x1F,0x00,0x00,0x00,0x3F,0x40,0x40,0x78,0x00,

		/*--  文字:  测  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x10,0x60,0x02,0x8C,0x00,0xFE,0x02,0xF2,0x02,0xFE,0x00,0xF8,0x00,0xFF,0x00,0x00,
		0x04,0x04,0x7E,0x01,0x80,0x47,0x30,0x0F,0x10,0x27,0x00,0x47,0x80,0x7F,0x00,0x00,

		/*--  文字:  试  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x40,0x40,0x42,0xCC,0x00,0x90,0x90,0x90,0x90,0x90,0xFF,0x10,0x11,0x16,0x10,0x00,
		0x00,0x00,0x00,0x3F,0x10,0x28,0x60,0x3F,0x10,0x10,0x01,0x0E,0x30,0x40,0xF0,0x00,

		/*--  文字:  仪  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x00,0x80,0x60,0xF8,0x07,0x00,0x1C,0xE0,0x01,0x06,0x00,0xE0,0x1E,0x00,0x00,0x00,
		0x01,0x00,0x00,0xFF,0x00,0x80,0x40,0x20,0x13,0x0C,0x13,0x20,0x40,0x80,0x80,0x00,
	},	//0

	{
		/*--  文字:  自  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x00,0x00,0x00,0xF8,0x88,0x8C,0x8A,0x89,0x88,0x88,0x88,0xF8,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0xFF,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0xFF,0x00,0x00,0x00,0x00,

		/*--  文字:  动  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x40,0x44,0xC4,0x44,0x44,0x44,0x40,0x10,0x10,0xFF,0x10,0x10,0x10,0xF0,0x00,0x00,
		0x10,0x3C,0x13,0x10,0x14,0xB8,0x40,0x30,0x0E,0x01,0x40,0x80,0x40,0x3F,0x00,0x00,

		/*--  文字:  旋  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x10,0x10,0xF1,0x96,0x90,0x90,0x10,0x28,0x27,0x24,0xE4,0x24,0x24,0xE4,0x04,0x00,
		0x80,0x60,0x1F,0x40,0x80,0x7F,0x80,0x60,0x1F,0x20,0x7F,0x44,0x44,0x44,0x40,0x00,

		/*--  文字:  转  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0xC8,0xB8,0x8F,0xE8,0x88,0x88,0x40,0x48,0x48,0xE8,0x5F,0x48,0x48,0x48,0x40,0x00,
		0x08,0x18,0x08,0xFF,0x04,0x04,0x00,0x02,0x0B,0x12,0x22,0xD2,0x0A,0x06,0x00,0x00,
	},	//1

	{
		/*--  文字:  固  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x00,0xFE,0x02,0x12,0x92,0x92,0x92,0xFE,0x92,0x92,0x92,0x12,0x02,0xFE,0x00,0x00,
		0x00,0xFF,0x40,0x40,0x5F,0x48,0x48,0x48,0x48,0x48,0x5F,0x40,0x40,0xFF,0x00,0x00,

		/*--  文字:  定  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x10,0x0C,0x44,0x44,0x44,0x44,0x45,0xC6,0x44,0x44,0x44,0x44,0x44,0x14,0x0C,0x00,
		0x80,0x40,0x20,0x1E,0x20,0x40,0x40,0x7F,0x44,0x44,0x44,0x44,0x44,0x40,0x40,0x00,

		/*--  文字:  中  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x00,0x00,0xF0,0x10,0x10,0x10,0x10,0xFF,0x10,0x10,0x10,0x10,0xF0,0x00,0x00,0x00,
		0x00,0x00,0x0F,0x04,0x04,0x04,0x04,0xFF,0x04,0x04,0x04,0x04,0x0F,0x00,0x00,0x00,

		/*--  文字:  位  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x00,0x80,0x60,0xF8,0x07,0x10,0x90,0x10,0x11,0x16,0x10,0x10,0xD0,0x10,0x00,0x00,
		0x01,0x00,0x00,0xFF,0x40,0x40,0x41,0x5E,0x40,0x40,0x70,0x4E,0x41,0x40,0x40,0x00,		
	},	//2

	{
		/*--  文字:  手  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x00,0x00,0x24,0x24,0x24,0x24,0x24,0xFC,0x22,0x22,0x22,0x23,0x22,0x00,0x00,0x00,
		0x02,0x02,0x02,0x02,0x02,0x42,0x82,0x7F,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00,

		/*--  文字:  动  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x40,0x44,0xC4,0x44,0x44,0x44,0x40,0x10,0x10,0xFF,0x10,0x10,0x10,0xF0,0x00,0x00,
		0x10,0x3C,0x13,0x10,0x14,0xB8,0x40,0x30,0x0E,0x01,0x40,0x80,0x40,0x3F,0x00,0x00,

		/*--  文字:  控  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x10,0x10,0x10,0xFF,0x90,0x20,0x98,0x48,0x28,0x09,0x0E,0x28,0x48,0xA8,0x18,0x00,
		0x02,0x42,0x81,0x7F,0x00,0x40,0x40,0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x40,0x00,

		/*--  文字:  制  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x40,0x50,0x4E,0x48,0x48,0xFF,0x48,0x48,0x48,0x40,0xF8,0x00,0x00,0xFF,0x00,0x00,
		0x00,0x00,0x3E,0x02,0x02,0xFF,0x12,0x22,0x1E,0x00,0x0F,0x40,0x80,0x7F,0x00,0x00,
	},	//3

	{
		/*--  文字:  关  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x00,0x00,0x10,0x11,0x16,0x10,0x10,0xF0,0x10,0x10,0x14,0x13,0x10,0x00,0x00,0x00,
		0x81,0x81,0x41,0x41,0x21,0x11,0x0D,0x03,0x0D,0x11,0x21,0x41,0x41,0x81,0x81,0x00,

		/*--  文字:  于  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x40,0x40,0x42,0x42,0x42,0x42,0x42,0xFE,0x42,0x42,0x42,0x42,0x42,0x40,0x40,0x00,
		0x00,0x00,0x00,0x00,0x00,0x40,0x80,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	},	//4

	{
		/*--  文字:  当  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x00,0x40,0x42,0x44,0x58,0x40,0x40,0x7F,0x40,0x40,0x50,0x48,0xC6,0x00,0x00,0x00,
		0x00,0x40,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0xFF,0x00,0x00,0x00,

		/*--  文字:  前  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x08,0x08,0xE8,0x29,0x2E,0x28,0xE8,0x08,0x08,0xC8,0x0C,0x0B,0xE8,0x08,0x08,0x00,
		0x00,0x00,0xFF,0x09,0x49,0x89,0x7F,0x00,0x00,0x0F,0x40,0x80,0x7F,0x00,0x00,0x00,

		/*--  文字:  角  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x20,0x10,0xE8,0x24,0x27,0x24,0x24,0xE4,0x24,0x34,0x2C,0x20,0xE0,0x00,0x00,0x00,
		0x80,0x60,0x1F,0x09,0x09,0x09,0x09,0x7F,0x09,0x09,0x49,0x89,0x7F,0x00,0x00,0x00,

		/*--  文字:  度  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x00,0x00,0xFC,0x24,0x24,0x24,0xFC,0x25,0x26,0x24,0xFC,0x24,0x24,0x24,0x04,0x00,
		0x40,0x30,0x8F,0x80,0x84,0x4C,0x55,0x25,0x25,0x25,0x55,0x4C,0x80,0x80,0x80,0x00,
	},	//5
	
	{
		/*--  文字:  返  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x40,0x40,0x42,0xCC,0x00,0x00,0xFC,0x24,0xA4,0x24,0x22,0x22,0xA3,0x62,0x00,0x00,
		0x00,0x40,0x20,0x1F,0x20,0x58,0x47,0x50,0x48,0x45,0x42,0x45,0x48,0x50,0x40,0x00,

		/*--  文字:  回  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x00,0x00,0xFE,0x02,0x02,0xF2,0x12,0x12,0x12,0xF2,0x02,0x02,0xFE,0x00,0x00,0x00,
		0x00,0x00,0x7F,0x20,0x20,0x27,0x24,0x24,0x24,0x27,0x20,0x20,0x7F,0x00,0x00,0x00,	
	},	//6
};
#endif


