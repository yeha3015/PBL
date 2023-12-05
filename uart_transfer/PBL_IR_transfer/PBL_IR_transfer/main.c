/*
 * PBL_IR_transfer.c
 *
 * Created: 2023/11/17 14:02:55
 * Author : ygoto
 
 *D2 RX
 *D3 TX
 *B0 B0
 *B1 1
 54(T) 3F(?), 92
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
	return 0;
}

int uart1_send_uint8t(uint8_t *data){
	int i = 0;
	while(data[i] != 0xFF){
		UART1_Byte_Send(data[i++]);
	}
	return 0;
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

uint8_t* make_transit_signal(uint8_t *data, uint8_t ret[4]){
	/*
	fixme: null data
	*///data[2]‚É‚µ‚½‚¢
	//init_arr(ret, DATA_LENGTH);
	ret[0] = 0xA5;
	for(int i = 0; i < 3; i++){
		ret[i] = data[i + 3];
	}
	ret[3] = 0xFF;
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
		uint8_t send_data[4] = {0x00, 0x00, 0x00, 0xFF};
		data[DATA_LENGTH] = '\0';
		if(!check_signal(data)){
			uart1_send_strings("Data was broken");
			uart1_send_strings("\r\n");
			continue;
		}
		uart1_send_uint8t(make_transit_signal(data, send_data));
		uart1_send_strings("\r\n");
		_delay_ms(500);
    }
	
}

/*
	while(1){
		//uart1_send_strings("start");
		//UART1_Byte_Send(0xA5);
		//uart1_send_strings("\n");
		_delay_ms(100);
		uint8_t d[8]  = {0xA5, 0x5A, 0x10, 0x01, 0x11, 0x12, 0x21, 0x0A};
		uint8_t ret[4] = {0x00, 0x00, 0x00, 0xFF};
		uart1_send_uint8t(make_transit_signal(d, ret));
		uart1_send_strings("\n");
		//uart1_send_strings("\n");
		PORTB = 0x02;
		_delay_ms(100);
		PORTB = 0x00;
		//uart1_send_strings(d);
		_delay_ms(800);
	}
*/
