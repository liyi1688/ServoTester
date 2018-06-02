/**********************************************************
 * @file     LCD_UI.c
 * @brief    
 * @author   Liyi
 * @version  V1.0
 * @date     2018.6.1
 * @note
 * @par	
 * Copyright (C) 2018 SLDX Limited. All rights reserved.
 **********************************************************/
 
#include "LCD_UI.h"
#include "Picture.h"	//图片
#include "Pixel_CH.h"	//汉字




/**
  * @brief  启动欢迎界面
  * @param  None
  * @retval None
  * @note   
  */
void UI_Hello()
{
	Nokia5110_ShowPicturePoint(gImage_666, 510);
	LCD5110Clear();
	LCD5110WriteEnStr(0, 1, " Servo Tester", 0);
	
	LCD5110WriteEnStr(0, 3, "@Version:1.0.0", 0);
	LCD5110WriteEnStr(0, 4, "@Author:Liyi", 0);
	LCD5110WriteEnStr(0, 5, "@Date:2018.6.2", 0);
	delay_ms(850);
	LCD5110Clear();	
}


/**
  * @brief  主界面
  * @param  None
  * @retval u8 cmd 被选中的菜单
  * @note   
  */
u8 UI_menu_root()
{	
	char keyScan = 0;
	u8 cmd = 1;
	
	LCD5110Clear();
	
	
	LCD5110WriteEnStr(0, 1, " Servo Tester", 0);
	
	LCD5110WriteEnStr(0, 4, "Begin", 0);
	LCD5110WriteEnStr(0, 5, "About", 0);
	
	while(1)
	{
		//Key_Scan()
		
		if(keyScan == 2)
			break;
		else
			cmd += keyScan;
		
		if(cmd > 2)		//菜单循环显示
			cmd = 1;
		else if(cmd < 1)
			cmd = 2;
		
		switch(cmd)
		{
			case 1:
				LCD5110WriteEnStr(0, 4, "Begin", 1); break;
			case 2:
				LCD5110WriteEnStr(0, 5, "About", 1); break;
		}
	}
	
	return cmd;	
}


/**
  * @brief  通道选择界面
  * @param  None
  * @retval u8 cmd 选中值
  * @note   
  */
u8 UI_menu_Channel()
{
	u8 cmd = 1;
	char keyScan = 0;
	
	LCD5110Clear();
	LCD5110WriteEnStr(0, 0, "Channel 1", 0);
	LCD5110WriteEnStr(0, 1, "Channel 2", 0);
	LCD5110WriteEnStr(0, 2, "Channel 3", 0);
	LCD5110WriteEnStr(0, 3, "Channel 4", 0);	
	LCD5110WriteEnStr(0, 4, "ALL Channel", 0);
	LCD5110WriteEnStr(0, 5, "Break", 0);
	
	while(1)
	{
		//key_scan()
		if(keyScan == 2)
			break;
		else
			cmd += keyScan;
		
		if(cmd < 1)		//选中部分可以循环
			cmd = 6;
		else if(cmd > 6)
			cmd = 1;
		
		switch(cmd)
		{
			case 1:
				LCD5110WriteEnStr(0, 0, "Channel 1", 1); break;
			case 2:
				LCD5110WriteEnStr(0, 1, "Channel 2", 1); break;
			case 3:
				LCD5110WriteEnStr(0, 2, "Channel 3", 1); break;
			case 4:
				LCD5110WriteEnStr(0, 3, "Channel 4", 1); break;
			case 5:
				LCD5110WriteEnStr(0, 4, "ALL Channel", 1); break;
			case 6:
				LCD5110WriteEnStr(0, 5, "Break", 1); break;
		}
	}
	return cmd;	
}


/**
  * @brief  三种工作模式选择
  * @param  None
  * @retval u8 cmd 被选中的模式
  * @note   
  */
u8 UI_menu_mode()
{
	u8 cmd;
	char keyScan;
	
	LCD5110Clear();
	LCD5110WriteEnStr(0, 0, "Auto", 0);	
	LCD5110WriteEnStr(0, 1, "Middle", 0);	
	LCD5110WriteEnStr(0, 2, "Manual", 0);	
	
	while(1)
	{
		//key_scan()
		if(keyScan == 2)
			break;
		else
			cmd += keyScan;
		
		if(cmd < 1)		//选中部分可以循环
			cmd = 3;
		else if(cmd > 3)
			cmd = 1;
		
		switch(cmd)
		{
			case 1:
				LCD5110WriteEnStr(0, 0, "Auto", 1); break;
			case 2:
				LCD5110WriteEnStr(0, 1, "Middle", 1); break;
			case 3:
				LCD5110WriteEnStr(0, 2, "Manual", 1); break;
		}
	}
	return cmd;	
}

/**
  * @brief  自动旋转界面
  * @param  u8 channel 选中的通道值
  * @retval None
  * @note   
  */
void UI_menu_auto(u8 channel)
{	
	char keyScan = 0;
	u16 num = 250;
	
	LCD5110Clear();
	LCD5110WriteEnStr(0, 0, "psc:F1:143", 0);	
	LCD5110WriteEnStr(24, 1,"F4:167", 0);	
	
	LCD5110WriteEnStr(0, 2, "arr:10000", 0);	
	
	LCD5110WriteEnStr(0, 3, "CCR:", 0);	
	
	LCD5110WriteChStr(0, 4, chinese_character[6], 2, 1);	//返回
	
	while(1)
	{
		LCD5110ShowNum(24, 3, num, 0);
		switch(channel)
		{
			case 1:
				TIM3->CCR1 = num; break;
			case 2:
				TIM3->CCR2 = num; break;
			case 3:
				TIM3->CCR3 = num; break;
			case 4:
				TIM3->CCR4 = num; break;
			case 5:
				TIM3->CCR1 = num; 
				TIM3->CCR2 = num;
				TIM3->CCR3 = num;
				TIM3->CCR4 = num; break;		
		}
		
		//key_scan();
		if(keyScan == 2)	//按下确认键
			break;	//认为返回上级菜单
		else
			num += keyScan;
		
		if(num > 1250)		//限定范围
			num = 1250;
		else if(num < 250)
			num = 250;
		
		delay_ms(50);	//为了能看清循环旋转
	}
}


/**
  * @brief  固定中位界面
  * @param  u8 channel 选中的通道
  * @retval None
  * @note   
  */
void UI_menu_middle(u8 channel)
{	
	const u16 num = 750;	//中值
	char keyScan = 0;
	
	LCD5110Clear();
	LCD5110WriteEnStr(0, 0, "psc:F1:143", 0);	
	LCD5110WriteEnStr(24, 1,"F4:167", 0);	
	
	LCD5110WriteEnStr(0, 2, "arr:10000", 0);	
	
	LCD5110WriteEnStr(0, 3, "CCR:", 0);		//（500，1250）
	LCD5110ShowNum(24, 3, num, 0);
	
	switch(channel)
	{
		case 1:
			TIM3->CCR1 = num; break;
		case 2:
			TIM3->CCR2 = num; break;
		case 3:
			TIM3->CCR3 = num; break;
		case 4:
			TIM3->CCR4 = num; break;
		case 5:
			TIM3->CCR1 = num; 
			TIM3->CCR2 = num;
			TIM3->CCR3 = num;
			TIM3->CCR4 = num; break;		
	}
	
	LCD5110WriteChStr(0, 4, chinese_character[6], 2, 1);	//返回
	
	while(1)	//判断退出
	{
		//keyscan();
		if(keyScan == 2)
			break;
	}
}


/**
  * @brief  手动控制界面
  * @param  u8 channel 选中的通道
  * @retval None
  * @note   
  */
void UI_menu_manual(u8 channel)
{
	u16 num = 750;
	char keyScan = 0;
	
	LCD5110Clear();
	LCD5110WriteEnStr(0, 0, "psc:F1:143", 0);	
	LCD5110WriteEnStr(24, 1,"F4:167", 0);	
	
	LCD5110WriteEnStr(0, 2, "arr:10000", 0);	
	
	LCD5110WriteEnStr(0, 3, "CCR:", 0);	
	
	LCD5110WriteChStr(0, 4, chinese_character[6], 2, 1);	//返回
	
	while(1)
	{
		LCD5110ShowNum(24, 3, num, 0);
		switch(channel)
		{
			case 1:
				TIM3->CCR1 = num; break;
			case 2:
				TIM3->CCR2 = num; break;
			case 3:
				TIM3->CCR3 = num; break;
			case 4:
				TIM3->CCR4 = num; break;
			case 5:
				TIM3->CCR1 = num; 
				TIM3->CCR2 = num;
				TIM3->CCR3 = num;
				TIM3->CCR4 = num; break;		
		}
		
		//key_scan();
		if(keyScan == 2)	//按下确认键
			break;	//认为返回上级菜单
		else
			num += keyScan;
		
		if(num > 1250)		//限定范围
			num = 1250;
		else if(num < 250)
			num = 250;
	}
	
}


/**
  * @brief  关于界面
  * @param  None
  * @retval None
  * @note   
  */
void UI_about()
{
	char keyScan = 0;
	
	LCD5110Clear();
	LCD5110WriteEnStr(0, 0, "@Version:1.0.0", 0);
	LCD5110WriteEnStr(0, 1, "@Author:Liyi", 0);
	LCD5110WriteEnStr(0, 2, "@Date:2018.6.2", 0);
	
	while(1)	//判断退出
	{
		//keyscan();
		if(keyScan == 2)
			break;
	}
	
}










