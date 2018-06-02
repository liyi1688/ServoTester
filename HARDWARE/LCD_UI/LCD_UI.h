/**********************************************************
 * @file     LCD_UI.h
 * @brief    
 * @author   Liyi
 * @version  V1.0
 * @date     2018.6.1
 * @note
 * @par	
 * Copyright (C) 2018 SLDX Limited. All rights reserved.
 **********************************************************/
 
 #ifndef _LCD_UI_H
 #define _LCD_UI_H
 
 
#include "LCD5110.h"
#include "delay.h"
 
 
void UI_Hello(void);
u8	 UI_menu_root(void);
u8	 UI_menu_Channel(void);
u8	 UI_menu_mode(void);
void UI_menu_auto(u8 channel);
void UI_menu_middle(u8 channel);
void UI_menu_manual(u8 channel);
void UI_about(void);


 
 
 
 
 
 #endif







