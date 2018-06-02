/**********************************************************
 * @file     LCD5110.h
 * @brief    Nokia5110液晶屏幕
 * @author   Liyi
 * @version  V1.0
 * @date     2018.5.31
 * @note	 Nokia5110液晶屏驱动程序
 *				分辨率 84*48
 * 				STM32F103平台
 * @par	
 * Copyright (C) 2018 SLDX Limited. All rights reserved.
 **********************************************************/

#ifndef _LCD5110_H
#define _LCD5110_H

#include "sys.h"

//宽高像素
//#define LCD_X_RES		84
//#define LCD_Y_RES		48

//枚举 D/C模式选择 
typedef enum  //emum为枚举常量
{
    DC_CMD  = 0,	//写命令
	DC_DATA = 1		//写数据
		
}DCType;


#define LCD_CTRL_PORT	GPIOB
#define LCDRCC_CLK      RCC_APB2Periph_GPIOB
#define LCD_RST			GPIO_Pin_3
#define LCD_CE			GPIO_Pin_5
#define LCD_DC			GPIO_Pin_7
#define LCD_MOSI		GPIO_Pin_9
#define LCD_CLK			GPIO_Pin_11

//H结尾为1，L结尾为0
#define LCD_RST_H		GPIO_SetBits(LCD_CTRL_PORT, LCD_RST)
#define LCD_RST_L		GPIO_ResetBits(LCD_CTRL_PORT, LCD_RST)

#define LCD_CE_H		GPIO_SetBits(LCD_CTRL_PORT, LCD_CE)
#define LCD_CE_L		GPIO_ResetBits(LCD_CTRL_PORT, LCD_CE)

#define LCD_DC_DATA		GPIO_SetBits(LCD_CTRL_PORT, LCD_DC)
#define LCD_DC_CMD		GPIO_ResetBits(LCD_CTRL_PORT, LCD_DC)

#define LCD_MOSI_H		GPIO_SetBits(LCD_CTRL_PORT, LCD_MOSI)
#define LCD_MOSI_L		GPIO_ResetBits(LCD_CTRL_PORT, LCD_MOSI)

#define LCD_CLK_H		GPIO_SetBits(LCD_CTRL_PORT, LCD_CLK)
#define LCD_CLK_L		GPIO_ResetBits(LCD_CTRL_PORT, LCD_CLK)

#define LCD_VCC_H		GPIO_SetBits(LCD_CTRL_PORT, LCD_VCC)

#define	LCD_BGL_H		GPIO_SetBits(LCD_CTRL_PORT, LCD_BGL)

#define LCD_GND_L		GPIO_ResetBits(LCD_CTRL_PORT, LCD_GND)


void LCD5110_GPIOInit(void);	//全部初始化
void LCD5110_SetContrast(u8 contrast);	//设置对比度

void LCD5110Clear(void);				//清屏
void LCD5110ClearPart(u8 X,u8 Y,u8 L,u8 H);	//清空部分区域

void LCD5110_SetXY(u8 X, u8 Y);			//设置光标

void LCD5110WriteChar(u8 X, u8 Y,u8 ascii, u8 mode);	//写字符
void LCD5110WriteEnStr(u8 X, u8 Y, u8* s, u8 mode);	//写字符串
void LCD5110ShowNum(u8 X,u16 Y,u32 num, u8 mode);	//直接显示数字
void LCD5110WriteChChar(u8 X, u8 Y, u8 chinese_character[][32], u8 n, u8 mode);	//显示中文字符
void LCD5110WriteChStr(u8 X, u8 Y, u8 chinese_character[][32], u8 n, u8 mode);

u8 Nokia5110_DrawPoint(u8 X, u8 Y) ;		//画点
void Draw_Circle(u16 x0,u16 y0,u8 r);		//画圆
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);	//画线
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);	//画矩形
void Nokia5110_ShowPicturePoint(u8 *picture, u16 length);		//显示图片
#endif




