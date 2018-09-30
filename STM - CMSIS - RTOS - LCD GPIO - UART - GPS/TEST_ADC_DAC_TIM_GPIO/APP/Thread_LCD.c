
#include <cmsis_os.h>                                           // CMSIS RTOS header file
#include "Thread_LCD.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "gps.h"

/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 

osThreadId tid_Thread_lcd;                                          // thread id
osThreadDef (Thread_LCD, osPriorityNormal, 1, 0);                   // thread object

extern str_gps gps;

int Init_Thread_LCD (void) {

  tid_Thread_lcd = osThreadCreate (osThread(Thread_LCD), NULL);
  if(!tid_Thread_lcd) return(-1);
  
  return(0);
}




void Thread_LCD (void const *argument) {
	
	char saludo[] = "HOLA MUNDO";
	char datos_lcd[32];
	int cont;
	
	//INIT LCD
	osDelay(100);
  Lcd_Write_Data(0, 0x03);
	
	osDelay(100);
  Lcd_Write_Data(0, 0x03);
	
	osDelay(100);
  Lcd_Write_Data(0, 0x03);
	
		osDelay(100);
  Lcd_Write_Data(0, 0x02);
	
	Lcd_Write_Data(0, 0x02);
	Lcd_Write_Data(0, 0x08);
	
	Lcd_Write_Data(0, 0x00);
	Lcd_Write_Data(0, 0x08);
	
	Lcd_Write_Data(0, 0x00);
	Lcd_Write_Data(0, 0x01);
	
	Lcd_Write_Data(0, 0x00);
	Lcd_Write_Data(0, 0x06);
	
	
	Lcd_Write_Data(0, 0x00);
	Lcd_Write_Data(0, 0x0F);
	
	Lcd_Write_Data(0, 0x00);
	Lcd_Write_Data(0, 0x02);
	
	//DISPLAY ON - WRITE	
	Lcd_write_str(&saludo[0]);
	
	 cont = 0;
	
  while (1) {
		
	   Lcd_Write_Data(0, 0x00);
	   Lcd_Write_Data(0, 0x01);
		 sprintf (datos_lcd, "LT=%4.2f", gps.Latitude);
		 Lcd_write_str(datos_lcd);
		
		 Lcd_Write_Data(0,0x0C);
	   Lcd_Write_Data(0,0x00);		
		
		  sprintf (datos_lcd, "LN=%4.2f", gps.Longitude);
		  Lcd_write_str(datos_lcd);
		  
		cont ++;
		
		osDelay(1000);
		  
		
  }
}




void Lcd_Write_Data(char rs, char data)
{

  //RS 
	if(rs == 1)
	{
		//DATA
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
	}
	else
	{
	 //Comando de configuracion	
	 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
	}
	
	//ENABLE -> 1
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);
	
	//DATA
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);
	
  //BIT 1
	if(data & 0x0001)
	{
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);
	}
	else
	{
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
	}	
	
	//BIT 2
	if(data & 0x0002)
	{
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
	}
	else
	{
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
	}	
	
	//BIT3
	if(data & 0x0004)
	{
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
	}
	else
	{
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
	}	
	
	//Bit4
	if(data & 0x0008)
	{
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);
	}
	else
	{
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);
	}	
	
	//DATA VALID---
	osDelay(1);
	
	//ENABLE -> 0
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);

	
}


void Lcd_write_char(char data)
{
char temp;
	
	//Bits del 7:4
	temp = (data & 0xF0)>>4;
      Lcd_Write_Data(1,temp);
	
	//Bits del 3:0
	temp = data & 0x0F;
	    Lcd_Write_Data(1,temp);
	
}

void Lcd_write_str(char* buffer)
{
	do{
		Lcd_write_char(*buffer);
		buffer++;
		
	}while(*buffer);
}

