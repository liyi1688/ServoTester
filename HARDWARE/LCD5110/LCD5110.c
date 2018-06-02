/**********************************************************
 * @file     LCD5110.c
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
 
#include "stm32f10x.h"
#include "LCD5110.h"
#include "delay.h"
#include "Pixel_EN.h"	//ascii
//#include "Pixel_CH.h"	//����
//#include "Picture.h"	//ͼƬ
#include "math.h"

//-------------------------------------------------------------------
//	Nokia5510ָ�
//  D7  D6  D5  D4  D3  D2  D1  D0
//  0   0   1   0   0   PD  V   H
//                      |   |   |_______1->��չָ�  0->����ָ�
//                      |   |___________1->��ֱѰַ    0->ˮƽѰַ 
//                      |_______________1->�͹���ģʽ  0->����ģʽ
//-------------------------------------------------------------------
//	��ʾģʽ
//  D7  D6  D5  D4  D3  D2  D1  D0
//  0   0   0   0   1   D   0   E
//                      |       |_______0    0    1    1
//                      |_______________0    1    0    1
//                                      ���� ���� ȫ�� ��ת
//-------------------------------------------------------------------


u8 Value_List[504];



/**
  * @brief  ��LCD5110��������
  * @param  u8 data		����
  *   		DCType dc	�������� DC_CMDд����   DC_DATAд����
  * @retval None
  * @note   ŵ����5110Һ����������Э��(����1���ֽ�)
  */
void LCD5110_Send(u8 data, DCType dc)
{
	u8 i=8;

	if (dc==DC_CMD)
		LCD_DC_CMD;	//��������
	else
		LCD_DC_DATA;//��������	
	while (i--)
	{
		LCD_CLK_L;
		if(data&0x80)
			LCD_MOSI_H;	/* MSB first */
		else 
			LCD_MOSI_L;
		LCD_CLK_H;
		data <<= 1;		/* Data shift */
	}
}


/**
  * @brief  Һ������ʼ��
  * @param  None
  * @retval None
  * @note   
  */
void LCD5110_Init(void)
{
	//��λLCD_�͵�ƽ����
	LCD_RST_L;		
	delay_ms(1);
	LCD_RST_H;
	
	//��λ���нӿ�_�ߵ�ƽ����
	LCD_CE_H; 
	delay_ms(1);
	LCD_CE_L; 

	//����LCD
    LCD5110_Send(0x21, DC_CMD);	//ʹ����չ��������LCDģʽ
    LCD5110_Send(0xC8, DC_CMD);	//����ƫ�õ�ѹ
    LCD5110_Send(0x06, DC_CMD);	//�¶�У��
    LCD5110_Send(0x13, DC_CMD);	//1:48
    LCD5110_Send(0x20, DC_CMD);	//ʹ�û�������
    LCD5110_Send(0x0C, DC_CMD);	//�趨��ʾģʽ��������ʾ

	LCD5110_SetContrast(127);    //�Աȶ�Ϊ127
	LCD5110Clear();
}


/**
  * @brief  ȫ����ʼ��
  * @param  None
  * @retval None
  * @note   ����IO�ڳ�ʼ������Ļ��ʼ��
  */
void LCD5110_GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(LCDRCC_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_All;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 	GPIO_Init(LCD_CTRL_PORT, &GPIO_InitStructure);

	LCD5110_Init();	//Һ������ʼ��
}

/**
  * @brief  ����LCD�Աȶ�
  * @param  u8 contrast	0-127
  * @retval None
  * @note   
  */
void LCD5110_SetContrast(u8 contrast)
{
    LCD5110_Send(0x21, DC_CMD);
    LCD5110_Send(0x80 | contrast, DC_CMD);
    LCD5110_Send(0x20, DC_CMD);
}


/**
  * @brief  ���ù��λ��
  * @param  u8 X	������ 0-83
  * 		u8 Y	������ 0-5
  * @retval None
  * @note   ���Ͻ�Ϊ(0��0)
  */
void LCD5110_SetXY(u8 X, u8 Y)
{
	if(X>83) X=83;
	if(Y>5)	 Y=5;
	LCD5110_Send(0x40 | Y, DC_CMD);    // ��
    LCD5110_Send(0x80 | X, DC_CMD);    // ��

}


/**
  * @brief  LCD5110ȫ������
  * @param  None
  * @retval None
  * @note   
  */
void LCD5110Clear(void)
{
	u16 i;	
	LCD5110_Send(0x0c, DC_CMD);
    LCD5110_Send(0x80, DC_CMD);	
	for (i=0; i<504; i++)
	LCD5110_Send(0, DC_DATA);	
}


/**
  * @brief  LCD5110������������
  * @param  u8 X	��ʼ��X����
  * 	    u8 Y	��ʼ��Y����
  * 	    u8 L	���������
  * 	    u8 H	�������߶�
  * @retval None
  * @note   
  */
void LCD5110ClearPart(u8 X,u8 Y,u8 L,u8 H)
{
	u16 i,j;
	
	LCD5110_Send(0x0c, DC_CMD);
    LCD5110_Send(0x80, DC_CMD);
	
	for (i=Y; i<Y+H+1; i++)
    	for(j=X;j<X+L+1;j++)
         { 
		 	LCD5110_SetXY(j,i);
	     	LCD5110_Send(0, DC_DATA);	
         }
}



/**
  * @brief  дһ���ַ�
  * @param  u8 X 	 ���Xλ�� 0-83
  * 		u8 Y 	 ���Yλ�� 0-5
  * 		u8 ascii �ַ���Ӧ��ascii
  * 		u8 mode	0-��ʾ���� 1-��ʾ����
  * @retval None
  * @note   
  */
void LCD5110WriteChar(u8 X, u8 Y,u8 ascii, u8 mode)
{   
    u8 n;
 	LCD5110_SetXY(X,Y);
    ascii -= 32; //ASCII��-32,�ӿո�ʼȡ��
	
	if(!mode)	//����
		for (n=0; n<=6; n++)
			LCD5110_Send(Font6x8[ascii][n], DC_DATA);
	else			//����
		for (n=0; n<=6; n++)
			LCD5110_Send(~Font6x8[ascii][n], DC_DATA);
}


/**
  * @brief  д�ַ���
  * @param  u8 X 	 ���Xλ�� 0-83
  * 		u8 Y 	 ���Yλ�� 0-5
  * 		u8 s 	 �ַ�����ַ
  * 		u8 mode	0-��ʾ���� 1-��ʾ����
  * @retval None
  * @note   
  */
void LCD5110WriteEnStr(u8 X, u8 Y, u8* s, u8 mode)
{
	while(*s != '\0') 
	{
		LCD5110WriteChar(X, Y, *s++, mode);
		X=X+6;//ÿ���ַ�ռ����6������,����Ҫ6��
		if(X>84)
		{ 
			X=0;
			Y=Y+1;
			s--;
			if(Y>=6)	{Y=0;}
		}
	}
}


/**
  * @brief  ��ʾһ������
  * @param  u8 X 	 ���Xλ�� 0-83
  * 		u8 Y 	 ���Yλ�� 0-5
  * 		u32 num  Ҫ��ʾ������
  * 		u8 mode	0-��ʾ���� 1-��ʾ����
  * @retval None
  * @note   ֱ����ʾ��������
  */
void LCD5110ShowNum(u8 X,u16 Y,u32 num, u8 mode)
{      
	u32 res;   	   
	u8 t=0,t1=0;   
	res=num;
	if(!num)LCD5110WriteChar( X,Y,'0', mode);//��ʾ0
	while(res)  //�õ����ֳ���
	{
		res/=10;
		t++;
	}
	t1=t;
	while(t)	//��ʾ����
	{
		res=pow(10,t-1); 	 
	    LCD5110WriteChar(X+(t1-t)*6,Y,(num/res)%10+'0', mode);//�����ַ���һ����'0'֮ǰ
		t--;
	}				     
} 


/**
  * @brief  ��ʾ�����ַ�
  * @param  u8 X 	���Xλ�� 0-83
  * 		u8 Y 	���Yλ�� 0-5
  * 		u8 n	Ҫ��ʾ���ֵı��
  * 		u8 mode	0-��ʾ���� 1-��ʾ����
  * @retval None
  * @note   ����ȡģ��� Pixel_CH.h  chinese_character[][]
  */
void LCD5110WriteChChar(u8 X, u8 Y, u8 chinese_character[][32], u8 n, u8 mode)
{
	int i;
	LCD5110_SetXY(X,Y);
	if(mode == 0)			//����
	{
		for(i = 0;i < 16; i++)//�����ϰ���
			LCD5110_Send(chinese_character[n][i],DC_DATA);
		LCD5110_SetXY(X,Y+1);
		for(i = 16; i < 32; i++)//�����°���
			LCD5110_Send(chinese_character[n][i],DC_DATA);
	}
	else if(mode == 1)		//����
	{
		for(i = 0;i < 16; i++)//�����ϰ���
			LCD5110_Send(~chinese_character[n][i],DC_DATA);
		LCD5110_SetXY(X,Y+1);
		for(i = 16; i < 32; i++)//�����°���
			LCD5110_Send(~chinese_character[n][i],DC_DATA);	
	}
}


/**
  * @brief  ��ʾ�����ַ���

  * @param  u8 X 	���Xλ�� 0-83
  * 		u8 Y 	���Yλ�� 0-5
  * 		u8 n	Ҫ��ʾ���ֵı��
  * 		u8 mode	0-��ʾ���� 1-��ʾ����
  * @retval None
  * @note   ����ȡģ��� Pixel_CH.h  chinese_character[][]
  */
void LCD5110WriteChStr(u8 X, u8 Y, u8 chinese_character[][32], u8 n, u8 mode)
{
	u8 i = 0;
	for(i = 0; i < n; i++)
	{
		LCD5110WriteChChar(X, Y, chinese_character, i, mode);
		X += 16;
	}
}


/**
  * @brief  ����
  * @param  u8 X 	���Xλ�� 0-83
  * 		u8 Y 	���Yλ�� 0-47
  * @retval 0��ʧ��  1���ɹ�
  * @note   ˮƽѰַ
  */
u8 Nokia5110_DrawPoint(u8 X, u8 Y) 
{
	u8 y1 = 0, y2 = 0;
	if (X > 83 || Y > 47)
	{
		return 0;
	}
	y1 = Y / 8;
	y2 = Y % 8;
	LCD5110_SetXY(X,y1);
	Value_List[y1 *84 + X] |= 0x01 << y2;	 //�����ȱ���ĸ�λ�õ�������򣬲����µõ�������д����ʾ����
	LCD5110_Send(Value_List[y1 *84 + X], DC_DATA);
	return 1;
}


/**
  * @brief  ��ʾ�Զ���ͼƬ
  * @param  None
  * @retval None
  * @note   ȡģ��� Img2Lcd.exe
  *			��ֱɨ�� 
  *			�ֽ����������ݷ���
  *			��Ƭ��� Picture.h
  */
void Nokia5110_ShowPicturePoint(u8 *picture, u16 length)
{
	u8 x_pos = 0, y_pos = 0;
	u8 j, tmp;
	u16 i;
	LCD5110Clear();	
	for (i = 0; i < length; i++)
	{
		tmp = picture[i];
		for (j = 0; j < 8; j++)
		{
			if (tmp & 0x01)
			{
				Nokia5110_DrawPoint(x_pos, y_pos);
				delay_ms(5);
			}
			tmp >>= 1;
			y_pos++;
		}
		if ((i + 1) % 6 == 0)
		{
			x_pos++;
			y_pos = 0;
		}
	}
}


/**
  * @brief  ��ֱ��
  * @param  u8 x1 	��� Xλ�� 0-83
  * 		u8 y1 	��� Yλ�� 0-47
  * 		u8 x2 	�յ� Xλ�� 0-83
  * 		u8 y2 	�յ� Yλ�� 0-47
  * @retval None
  * @note   
  */
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		Nokia5110_DrawPoint(uRow,uCol);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 


/**
  * @brief  ������
  * @param  �Խ���(x1,y1) to   (x2,y2)
  * @retval None
  * @note   
  */
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}


/**
  * @brief  ��Բ
  * @param  ԭ��(x,y),�뾶r
  * @retval None
  * @note   
  */
void Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
          
		Nokia5110_DrawPoint(x0-b,y0-a);             //3           
		Nokia5110_DrawPoint(x0+b,y0-a);             //0           
		Nokia5110_DrawPoint(x0-a,y0+b);             //1       
		Nokia5110_DrawPoint(x0-b,y0-a);             //7           
		Nokia5110_DrawPoint(x0-a,y0-b);             //2             
		Nokia5110_DrawPoint(x0+b,y0+a);             //4               
		Nokia5110_DrawPoint(x0+a,y0-b);             //5
		Nokia5110_DrawPoint(x0+a,y0+b);             //6 
 		Nokia5110_DrawPoint(x0-b,y0+a);       
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)
			di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 
		Nokia5110_DrawPoint(x0+a,y0+b);
	}
} 

