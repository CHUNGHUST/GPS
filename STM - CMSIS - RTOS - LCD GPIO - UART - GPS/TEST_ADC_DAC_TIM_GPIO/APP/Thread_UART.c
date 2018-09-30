
#include <cmsis_os.h>                                           // CMSIS RTOS header file
#include <stdio.h>
#include <string.h>

#include "stm32f4xx_hal.h"
#include "Thread_UART.h"
#include "gps.h"

//Variable gobal
extern UART_HandleTypeDef huart3;

uint8_t uart_buffer_rx[16];
uint8_t uart_buffer_tx[16];

uint8_t uart_buffer_gps[200];

int uart_flag_rx;

str_gps gps;

/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 

osThreadId tid_Thread_uart;                                          // thread id
osThreadDef (Thread_Uart, osPriorityNormal, 1, 0);                   // thread object


int Init_Thread_Uart (void) {

  tid_Thread_uart = osThreadCreate (osThread(Thread_Uart), NULL);
  if(!tid_Thread_uart) return(-1);
  
  return(0);
}



void Thread_Uart (void const *argument) {
int count;
	
	count = 0;
	
	uart_flag_rx = 0;
	HAL_UART_Receive_IT(&huart3, uart_buffer_rx , 16);
	
  while (1) {
	
    //sprintf((char*)uart_buffer_tx,"Hola mundo %d\n\r",count);
    //HAL_UART_Transmit(&huart3, &uart_buffer_tx[0] , strlen((char*)uart_buffer_tx),100);
		//count++;
		
		
		
		
		//Bandera de llegada de datos por serial
		if(uart_flag_rx == 1)
		{
			
			for(int i = 0; i<16; i++)
			{
						if(uart_buffer_rx[i] == '$')
						{
							count = 0;
							uart_buffer_gps[count] = uart_buffer_rx[i];
						}
						//SI EL CARACTER ES Nueva LINEA - Hay un frame completo
						else if(uart_buffer_rx[i] ==  0x0A || uart_buffer_rx[i] ==  0x0D)
						{						
							count = 0;		
							GPS_read((char*)uart_buffer_gps,&gps);							
						}
							
						else
						{
							 count++;
							 uart_buffer_gps[count] = uart_buffer_rx[i];
							 uart_buffer_gps[count  + 1] = 0;
							 
						}
						
						if(count > 99)
							count = 0;
			}
			
			uart_flag_rx = 0;
			HAL_UART_Receive_IT(&huart3, uart_buffer_rx , 16);
		
		}                                          
		
			osThreadYield();
		
  }
}



//INTERRUPCION
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	 if(huart->Instance == USART3)
    {
       uart_flag_rx = 1;
    }
	//	else if(huart->Instance == USART6)
  //{
  //     uart_flag_rx_6 = 1;
  //}
	
}

//EN CASO ERROR -- INTERRU
extern void MX_USART3_UART_Init(void);
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
if(huart->Instance == USART3)
    {
       MX_USART3_UART_Init();
			 HAL_UART_Receive_IT(&huart3, uart_buffer_rx , 16);
    }
	}


