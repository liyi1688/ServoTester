#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "wdg.h"

#include "LCD5110.h"
#include "LCD_UI.h"

int main(void)
{		
	
	u8 menu_cmd_root;
	u8 menu_cmd_channel;
	u8 menu_cmd_mode;
	
	delay_init();	    	 //延时函数初始化	  
	SystemInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
	LED_Init();		  	 //初始化与LED连接的硬件接口
	KEY_Init();          //按键初始化	 

	//	IWDG_Init(4,625);    //与分频数为64,重载值为625,溢出时间为1s	   
	LCD5110_GPIOInit();
	TIM3_PWM_Init();
	LED0=0;				 //点亮LED0
	while(1)
	{
		UI_Hello();
		while(1)
		{
			menu_cmd_root = UI_menu_root();	//Begin  About
			
			if(menu_cmd_root == 1)	//Begin
			{
				while(1)
				{
					menu_cmd_channel = UI_menu_Channel();	//Channel 1 2 3 4 All   Break
					
					if(menu_cmd_channel == 6)	//返回上一级  Break
						break;
					
					//Channel 1 2 3 4 All 
					menu_cmd_mode = UI_menu_mode();	 // Auto  Middle  Manual
					switch(menu_cmd_mode)
					{
						case 1:
							UI_menu_auto(menu_cmd_channel);	break;		//函数内有while(1) 如果跳出证明已经选中返回上级
						case 2:
							UI_menu_middle(menu_cmd_channel); break;
						case 3:
							UI_menu_manual(menu_cmd_channel); break;
					}
					menu_cmd_channel = 0;
				}
			}
			else if(menu_cmd_root == 2)	// About
			{
				UI_about(); //函数内有while(1) 如果跳出证明已经选中返回上级
			}
			menu_cmd_root = 0;
		}
	}
}
  

