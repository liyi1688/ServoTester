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
	
	delay_init();	    	 //��ʱ������ʼ��	  
	SystemInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();          //������ʼ��	 

	//	IWDG_Init(4,625);    //���Ƶ��Ϊ64,����ֵΪ625,���ʱ��Ϊ1s	   
	LCD5110_GPIOInit();
	TIM3_PWM_Init();
	LED0=0;				 //����LED0
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
					
					if(menu_cmd_channel == 6)	//������һ��  Break
						break;
					
					//Channel 1 2 3 4 All 
					menu_cmd_mode = UI_menu_mode();	 // Auto  Middle  Manual
					switch(menu_cmd_mode)
					{
						case 1:
							UI_menu_auto(menu_cmd_channel);	break;		//��������while(1) �������֤���Ѿ�ѡ�з����ϼ�
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
				UI_about(); //��������while(1) �������֤���Ѿ�ѡ�з����ϼ�
			}
			menu_cmd_root = 0;
		}
	}
}
  

