#include "StdTypes.h"
#include "MOTOR_int.h"
#include "MemMap.h"
#include "DIO_int.h"
#include "LCD_int.h"
#include "KEYPAD_int.h"
#include "KEYPAD_Cfg.h"
#include "ADC_int.h"

#define F_CPU  8000000
#include <util/delay.h>

#define password 1234

int main(void)
{
	u16 x, pass=0,k,flag=0 ;
	
	  DIO_Init();
	  LCD_Init();
      KEYPAD_Init();
	  ADC_Init(VREF_VCC,ADC_SCALER_64);
	  
	  
      c8 str1[20]="Fire Alarm Sys";
      LCD_WriteStringCursor(0,0,str1);
      LCD_SetCursor(1,0);
      LCD_WriteString("by Omar Mohamed");
      _delay_ms(100);
      LCD_Clear();
	
   while (1)
 {   
	x=SENSOR_ReadTemp();
	LCD_SetCursor(0,0);
	LCD_WriteString("Temp:"); 
	LCD_SetCursor(0,6);
	LCD_WriteNumber(x/10);
	LCD_WriteChar('.');
	LCD_WriteNumber(x%10);
	LCD_WriteString(" C  "); 
	LCD_SetCursor(1,0);
	LCD_WriteString("Status:");
	
    if ( x < 400)
  {
	 _delay_ms(30);
	  LCD_SetCursor(1,8);
	  LCD_WriteString("Normal");
	  CLR_BIT(PORTD,0);
	  CLR_BIT(PORTD,1);
	  CLR_BIT(PORTD,6);
	  CLR_BIT(PORTB,3); 
  }
	else if ( x  >= 400 && x <550 )
	{ 
	   _delay_ms(30);
	  LCD_SetCursor(1,8);
	  LCD_WriteString("Heat       ");
	  SET_BIT(PORTD,0);
	  CLR_BIT(PORTD,1);
	  CLR_BIT(PORTD,6);
	  CLR_BIT(PORTB,3); 
	}
	else if( x  >= 600)
	 {	
		_delay_ms(15);		
		LCD_SetCursor(1,8);
		LCD_WriteString("FIRE!!!");
		SET_BIT(PORTD,1);
		CLR_BIT(PORTD,0); 
		SET_BIT(PORTD,6);
		SET_BIT(PORTB,3);
		
		_delay_ms(400);
		LCD_Clear();
		 while ( pass != password)
		 {
			 k = KEYPAD_GetKey();
			  LCD_SetCursor(0,0);
			  LCD_WriteString("password:");
			 if (k!= NO_KEY && flag == 0)
			 {
				 pass =pass *10+ (k-'0');
				 LCD_SetCursor(0,9);
				 LCD_WriteNumber(pass);
				 
				 if (pass > 10000) // exceeds 4 digits
				 {
					 pass=0 ;
					  LCD_Clear();
					  _delay_ms(50);
					  LCD_SetCursor(0,0);
					  LCD_WriteString("password:");
					  LCD_SetCursor(0,9);
					  LCD_WriteNumber(pass);
				 }
				  if (k == 'c'){
					  pass = 0;
					  flag = 0;
					  LCD_Clear();
					  _delay_ms(50);
					  LCD_SetCursor(0,0);
					  LCD_WriteString("password:");
					  LCD_SetCursor(0,9);
					  LCD_WriteNumber(pass); 
				  }
			 }
		 }
	 }
					    if (pass == password)
					  {
					     // CLR_BIT(PORTD,0);
					      CLR_BIT(PORTD,1);
					      CLR_BIT(PORTD,6);
						  CLR_BIT(PORTB,3);
						  _delay_ms(200);
					  }
					   
		
			 	  
		  
	  
    
			 }
		 }



















/*x=ADC_ReadVolt(CH_7);
	LCD_SetCursor(1,0);
	LCD_WriteNumber(x);
	LCD_WriteString(" ");   
	LCD_SetCursor(1,0);
	LCD_WriteString("Status:");
	LCD_SetCursor(1,8);
	LCD_WriteString("Normal");   */