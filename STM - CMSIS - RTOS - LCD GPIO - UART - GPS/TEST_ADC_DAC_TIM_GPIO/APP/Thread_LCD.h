
#ifndef __THREAD_LCD
#define __THREAD_LCD

int Init_Thread_LCD (void);
void Thread_LCD (void const *argument);
void Lcd_Write_Data(char rs, char data);
void Lcd_write_char(char data);
void Lcd_write_str(char* buffer);


#endif

