/**********************************************************
 * @file     LCD5110.h
 * @brief    Nokia5110Һ����Ļ
 * @author   Liyi
 * @version  V1.0
 * @date     2018.5.31
 * @note	 Nokia5110Һ������������
 *				�ֱ��� 84*48
 * 				STM32F103ƽ̨
 * @par	
 * Copyright (C) 2018 SLDX Limited. All rights reserved.
 **********************************************************/

#ifndef _LCD5110_H
#define _LCD5110_H

#include "sys.h"

//�������
//#define LCD_X_RES		84
//#define LCD_Y_RES		48

//ö�� D/Cģʽѡ�� 
typedef enum  //emumΪö�ٳ���
{
    DC_CMD  = 0,	//д����
	DC_DATA = 1		//д����
		
}DCType;


#define LCD_CTRL_PORT	GPIOB
#define LCDRCC_CLK      RCC_APB2Periph_GPIOB
#define LCD_RST			GPIO_Pin_3
#define LCD_CE			GPIO_Pin_5
#define LCD_DC			GPIO_Pin_7
#define LCD_MOSI		GPIO_Pin_9
#define LCD_CLK			GPIO_Pin_11

//H��βΪ1��L��βΪ0
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


void LCD5110_GPIOInit(void);	//ȫ����ʼ��
void LCD5110_SetContrast(u8 contrast);	//���öԱȶ�

void LCD5110Clear(void);				//����
void LCD5110ClearPart(u8 X,u8 Y,u8 L,u8 H);	//��ղ�������

void LCD5110_SetXY(u8 X, u8 Y);			//���ù��

void LCD5110WriteChar(u8 X, u8 Y,u8 ascii, u8 mode);	//д�ַ�
void LCD5110WriteEnStr(u8 X, u8 Y, u8* s, u8 mode);	//д�ַ���
void LCD5110ShowNum(u8 X,u16 Y,u32 num, u8 mode);	//ֱ����ʾ����
void LCD5110WriteChChar(u8 X, u8 Y, u8 chinese_character[][32], u8 n, u8 mode);	//��ʾ�����ַ�
void LCD5110WriteChStr(u8 X, u8 Y, u8 chinese_character[][32], u8 n, u8 mode);

u8 Nokia5110_DrawPoint(u8 X, u8 Y) ;		//����
void Draw_Circle(u16 x0,u16 y0,u8 r);		//��Բ
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);	//����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);	//������
void Nokia5110_ShowPicturePoint(u8 *picture, u16 length);		//��ʾͼƬ
#endif




