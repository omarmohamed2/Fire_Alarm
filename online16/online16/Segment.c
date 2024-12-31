#define F_cpu   8000000
#include <util/delay.h>
#include "MemMap.h"
#define PINA    (*(volatile unsigned char*)0x39)

const char segmentarr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7c,0x07,0x7f,0x6f};
	
void segment_display(char n){
		
		PORTC=~segmentarr[n/10];
		PORTD=segmentarr[n%10]<<1;
		PORTA=segmentarr[n%10];  }
		
void segment_display_MLX(char n){
	
	SET_BIT(PORTB,0);
	CLR_BIT(PORTB,1);
	PORTA=segmentarr[n/10];
	_delay_ms(1);
	SET_BIT(PORTB,1);
	CLR_BIT(PORTB,0);
	PORTA=segmentarr[n%10];
	_delay_ms(1);
}
void segment_display_BCD(char n){
	char d0=n%10;
	char d1=n/10;
	PORTD=(d1<<4)|d0;
}