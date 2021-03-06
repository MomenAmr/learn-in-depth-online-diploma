/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "stm32f103x6.h"
#include "GPIO.h"
#include "LCD.h"
#include "KEYPAD.h"
#include "SEG_7.h"

void CLK_init ()
{
	//enable clock for GPIOA & GPIOB
	RCC_CLOCK_GPIOA_EN() ;
	RCC_CLOCK_GPIOB_EN() ;

}

void delay_loop(int x)
{
	int i;
	for(i=0;i<x;i++);
}

int main(void)
{
	char c;
	int i=0;
	unsigned char seg_init[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0','n'};

	CLK_init();

	LCD_init();
	LCD_send_string("LCD");
	LCD_send_command(LCD_BEGIN_AT_SECOND_ROW);
	LCD_send_string("initialized");
	delay_loop(50000);
	LCD_send_command(LCD_CLEAR_SCREEN);

	KEYPAD_init();
	LCD_send_string("KEYPAD");
	LCD_send_command(LCD_BEGIN_AT_SECOND_ROW);
	LCD_send_string("initialized");
	delay_loop(50000);
	LCD_send_command(LCD_CLEAR_SCREEN);

	SEG_7_init();
	LCD_send_string("7-SEGMENT");
	LCD_send_command(LCD_BEGIN_AT_SECOND_ROW);
	LCD_send_string("initialized");
	for(i=0;i<12;i++)
	{
		SEG_7_printnum(seg_init[i]);
		delay_loop(5000);
	}
	LCD_send_command(LCD_CLEAR_SCREEN);
	i=0;

	while (1)
    {
		c = KEYPAD_getc();
		switch(c)
		{
			case ('!'):
			LCD_send_command(LCD_CLEAR_SCREEN);
			SEG_7_printnum(c);
			i = 0;
			break;

			case ('N'):
			break;

			default:
			i++;
			LCD_send_data(c);
			SEG_7_printnum(c);
			if (i == 16)
			{
				LCD_send_command(LCD_BEGIN_AT_SECOND_ROW);
			}
			else if (i == 32)
			{
				LCD_send_command(LCD_CLEAR_SCREEN);
				i = 0;
			}
		}
		delay_loop(50);
    }
}
