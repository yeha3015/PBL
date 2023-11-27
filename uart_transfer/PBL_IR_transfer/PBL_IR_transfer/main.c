/*
 * PBL_IR_transfer.c
 *
 * Created: 2023/11/17 14:02:55
 * Author : ygoto
 
 *D2 RX
 *D3 TX
 *B0 B0
 *B1 1
 */ 


#define F_CPU 16000000UL
#define BAUD_RATE 1000 // per sec
#define WAIT_TIME_MS 1
#define DATA_LENGTH 7

#include <avr/io.h>
//#include <stdio.h>
#include <util/delay.h>

#include "my_lib.h"


void GoTo16MHz(){
    CLKPR = 0x80;
    CLKPR = 0;
}

int uart1_send_strings(char *string){
	int i = 0;
	while(string[i] != '\0'){
		UART1_Byte_Send(string[i++]);
	}
	return i;
}

int init_arr(uint8_t *arr, int length){
	for(int i = 0; i < length; i++){
		arr[i] = 0x00;
	}
}

uint8_t Calc_CheckSum(uint8_t* data){
	uint8_t size = data[2];
	uint8_t ret = size;
	for(uint8_t i = 0; i < size;i++){
		ret ^= data[i+3];
	}
	return ret;
}



uint8_t make_byte(){
	uint8_t recv_data;
	uint8_t recv_byte = 0x00;
	uint8_t send_byte;
	for(int i = 0; i < 8; i++){
		recv_data = PINB & 0x01;
		recv_byte += recv_data << i;
		_delay_ms(WAIT_TIME_MS);
		send_byte = ~recv_byte;
	}
	return send_byte;
}


int check_signal(uint8_t *data){
	if(data[0] != 0xA5 || data[1] != 0x5A) return 0;
	return data[DATA_LENGTH - 1] == Calc_CheckSum(data);
}

uint8_t make_transit_signal(uint8_t *data){
	/*
	fixme: null data
	*/
	uint8_t ret[DATA_LENGTH]; //data[2]‚É‚µ‚½‚¢
	init_arr(ret, DATA_LENGTH);
	ret[0] = 0xa5;
	for(int i = 0; i < DATA_LENGTH - 5; i++){
		//ret[i] = 0xa5;
	}
	data[DATA_LENGTH - 2] = '\0';
	return ret;
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
        recv_data = PINB & 0x01;
		while((PINB & 0x01) == 0x01){
			PORTB = 0x02;
		}
		_delay_ms(WAIT_TIME_MS);
		PORTB = 0x00;
		uint8_t data[DATA_LENGTH + 1];
		init_arr(data, DATA_LENGTH + 1);
		for(int i = 0; i < DATA_LENGTH; i++){
			data[i] =  make_byte();
			_delay_ms(WAIT_TIME_MS);
		}
		data[DATA_LENGTH] = '\0';
		if(!check_signal(data)){
			uart1_send_strings("Data was broken");
			//continue;
		}
		uart1_send_strings(data);
		uart1_send_strings("\r\n");
		uart1_send_strings(make_transit_signal(data));
		//uart1_send_strings(data);
		uart1_send_strings("\r\n");
		//UART1_Byte_Send((char)send_byte);
		//_delay_ms(500);
    }
	
}

