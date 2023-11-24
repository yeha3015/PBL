/*
 * PBL_IR_transfer.c
 *
 * Created: 2023/11/17 14:02:55
 * Author : ygoto
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
//#include <stdio.h>
#include <util/delay.h>

#include "my_lib.h"

void GoTo16MHz(){
    CLKPR = 0x80;
    CLKPR = 0;
}

int main(void)
{
    uint8_t recv_data;
	uint8_t send_byte;

    GoTo16MHz();
    USART1_Init();
    DDRB &= ~0x01;
	DDRB |= 0x02;
	
	PORTB &= ~0x02;

    while (1) {
        //printf("%d\n", PINB & 0x01);
        recv_data = PINB & 0x01;
		while((PINB & 0x01) == 0x01){
			PORTB = 0x02;
		}
		_delay_ms(1);
		PORTB = 0x00;
		uint8_t recv_byte = 0x00;
		for(int i = 0; i < 8; i++){
			recv_data = PINB & 0x01;
			recv_byte += recv_data << i;
			_delay_ms(1);
			send_byte = ~recv_byte;
			if(send_byte == 0x00){
				continue;
			}
		}
		UART1_Byte_Send((char)send_byte);
		//_delay_ms(500);
    }
}

