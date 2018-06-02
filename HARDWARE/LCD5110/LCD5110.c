/**********************************************************
 * @file     LCD5110.c
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
 
#include "stm32f10x.h"
#include "LCD5110.h"
#include "delay.h"
#include "Pixel_EN.h"	//ascii
//#include "Pixel_CH.h"	//汉字
//#include "Picture.h"	//图片
#include "math.h"

//-------------------------------------------------------------------
//	Nokia5510指令集
//  D7  D6  D5  D4  D3  D2  D1  D0
//  0   0   1   0   0   PD  V   H
//                      |   |   |_______1->扩展指令集  0->基本指令集
//                      |   |___________1->垂直寻址    0->水平寻址 
//                      |_______________1->低功耗模式  0->正常模式
//-------------------------------------------------------------------
//	显示模式
//  D7  D6  D5  D4  D3  D2  D1  D0
//  0   0   0   0   1   D   0   E
//                      |       |_______0    0    1    1
//                      |_______________0    1    0    1
//                                      白屏 正常 全显 反转
//-------------------------------------------------------------------


u8 Value_List[504];



/**
  * @brief  向LCD5110发送数据
  * @param  u8 data		数据
  *   		DCType dc	数据类型 DC_CMD写命令   DC_DATA写数据
  * @retval None
  * @note   诺基亚5110液晶串行总线协议(传送1个字节)
  */
void LCD5110_Send(u8 data, DCType dc)
{
	u8 i=8;

	if (dc==DC_CMD)
		LCD_DC_CMD;	//发送命令
	else
		LCD_DC_DATA;//发送数据	
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
  * @brief  液晶屏初始化
  * @param  None
  * @retval None
  * @note   
  */
void LCD5110_Init(void)
{
	//复位LCD_低电平脉冲
	LCD_RST_L;		
	delay_ms(1);
	LCD_RST_H;
	
	//复位串行接口_高电平脉冲
	LCD_CE_H; 
	delay_ms(1);
	LCD_CE_L; 

	//设置LCD
    LCD5110_Send(0x21, DC_CMD);	//使用扩展命令设置LCD模式
    LCD5110_Send(0xC8, DC_CMD);	//设置偏置电压
    LCD5110_Send(0x06, DC_CMD);	//温度校正
    LCD5110_Send(0x13, DC_CMD);	//1:48
    LCD5110_Send(0x20, DC_CMD);	//使用基本命令
    LCD5110_Send(0x0C, DC_CMD);	//设定显示模式，正常显示

	LCD5110_SetContrast(127);    //对比度为127
	LCD5110Clear();
}


/**
  * @brief  全部初始化
  * @param  None
  * @retval None
  * @note   包含IO口初始化、屏幕初始化
  */
void LCD5110_GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(LCDRCC_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_All;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 	GPIO_Init(LCD_CTRL_PORT, &GPIO_InitStructure);

	LCD5110_Init();	//液晶屏初始化
}

/**
  * @brief  设置LCD对比度
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
  * @brief  设置光标位置
  * @param  u8 X	横坐标 0-83
  * 		u8 Y	纵坐标 0-5
  * @retval None
  * @note   左上角为(0，0)
  */
void LCD5110_SetXY(u8 X, u8 Y)
{
	if(X>83) X=83;
	if(Y>5)	 Y=5;
	LCD5110_Send(0x40 | Y, DC_CMD);    // 行
    LCD5110_Send(0x80 | X, DC_CMD);    // 列

}


/**
  * @brief  LCD5110全部清屏
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
  * @brief  LCD5110矩形区域清屏
  * @param  u8 X	起始点X坐标
  * 	    u8 Y	起始点Y坐标
  * 	    u8 L	清空区域宽度
  * 	    u8 H	清空区域高度
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
  * @brief  写一个字符
  * @param  u8 X 	 光标X位置 0-83
  * 		u8 Y 	 光标Y位置 0-5
  * 		u8 ascii 字符对应的ascii
  * 		u8 mode	0-显示阳文 1-显示阴文
  * @retval None
  * @note   
  */
void LCD5110WriteChar(u8 X, u8 Y,u8 ascii, u8 mode)
{   
    u8 n;
 	LCD5110_SetXY(X,Y);
    ascii -= 32; //ASCII码-32,从空格开始取码
	
	if(!mode)	//阳文
		for (n=0; n<=6; n++)
			LCD5110_Send(Font6x8[ascii][n], DC_DATA);
	else			//阴文
		for (n=0; n<=6; n++)
			LCD5110_Send(~Font6x8[ascii][n], DC_DATA);
}


/**
  * @brief  写字符串
  * @param  u8 X 	 光标X位置 0-83
  * 		u8 Y 	 光标Y位置 0-5
  * 		u8 s 	 字符串地址
  * 		u8 mode	0-显示阳文 1-显示阴文
  * @retval None
  * @note   
  */
void LCD5110WriteEnStr(u8 X, u8 Y, u8* s, u8 mode)
{
	while(*s != '\0') 
	{
		LCD5110WriteChar(X, Y, *s++, mode);
		X=X+6;//每个字符占用行6个像素,至少要6个
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
  * @brief  显示一个数字
  * @param  u8 X 	 光标X位置 0-83
  * 		u8 Y 	 光标Y位置 0-5
  * 		u32 num  要显示的数字
  * 		u8 mode	0-显示阳文 1-显示阴文
  * @retval None
  * @note   直接显示整形数据
  */
void LCD5110ShowNum(u8 X,u16 Y,u32 num, u8 mode)
{      
	u32 res;   	   
	u8 t=0,t1=0;   
	res=num;
	if(!num)LCD5110WriteChar( X,Y,'0', mode);//显示0
	while(res)  //得到数字长度
	{
		res/=10;
		t++;
	}
	t1=t;
	while(t)	//显示数字
	{
		res=pow(10,t-1); 	 
	    LCD5110WriteChar(X+(t1-t)*6,Y,(num/res)%10+'0', mode);//数字字符第一个在'0'之前
		t--;
	}				     
} 


/**
  * @brief  显示中文字符
  * @param  u8 X 	光标X位置 0-83
  * 		u8 Y 	光标Y位置 0-5
  * 		u8 n	要显示的字的标号
  * 		u8 mode	0-显示阳文 1-显示阴文
  * @retval None
  * @note   汉字取模详见 Pixel_CH.h  chinese_character[][]
  */
void LCD5110WriteChChar(u8 X, u8 Y, u8 chinese_character[][32], u8 n, u8 mode)
{
	int i;
	LCD5110_SetXY(X,Y);
	if(mode == 0)			//阳文
	{
		for(i = 0;i < 16; i++)//汉字上半身
			LCD5110_Send(chinese_character[n][i],DC_DATA);
		LCD5110_SetXY(X,Y+1);
		for(i = 16; i < 32; i++)//汉字下半身
			LCD5110_Send(chinese_character[n][i],DC_DATA);
	}
	else if(mode == 1)		//阴文
	{
		for(i = 0;i < 16; i++)//汉字上半身
			LCD5110_Send(~chinese_character[n][i],DC_DATA);
		LCD5110_SetXY(X,Y+1);
		for(i = 16; i < 32; i++)//汉字下半身
			LCD5110_Send(~chinese_character[n][i],DC_DATA);	
	}
}


/**
  * @brief  显示中文字符串

  * @param  u8 X 	光标X位置 0-83
  * 		u8 Y 	光标Y位置 0-5
  * 		u8 n	要显示的字的标号
  * 		u8 mode	0-显示阳文 1-显示阴文
  * @retval None
  * @note   汉字取模详见 Pixel_CH.h  chinese_character[][]
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
  * @brief  画点
  * @param  u8 X 	光标X位置 0-83
  * 		u8 Y 	光标Y位置 0-47
  * @retval 0：失败  1：成功
  * @note   水平寻址
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
	Value_List[y1 *84 + X] |= 0x01 << y2;	 //与事先保存的该位置的数据相或，并将新得到的数据写入显示出来
	LCD5110_Send(Value_List[y1 *84 + X], DC_DATA);
	return 1;
}


/**
  * @brief  显示自定义图片
  * @param  None
  * @retval None
  * @note   取模软件 Img2Lcd.exe
  *			垂直扫描 
  *			字节内像素数据反序
  *			照片存放 Picture.h
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
  * @brief  画直线
  * @param  u8 x1 	起点 X位置 0-83
  * 		u8 y1 	起点 Y位置 0-47
  * 		u8 x2 	终点 X位置 0-83
  * 		u8 y2 	终点 Y位置 0-47
  * @retval None
  * @note   
  */
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		Nokia5110_DrawPoint(uRow,uCol);//画点 
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
  * @brief  画矩形
  * @param  对角线(x1,y1) to   (x2,y2)
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
  * @brief  画圆
  * @param  原点(x,y),半径r
  * @retval None
  * @note   
  */
void Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
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
		//使用Bresenham算法画圆     
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

