/*
 * PBL_IR_transfer.c
 *
 * Created: 2023/11/17 14:02:55
 * Author : ygoto
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>

#include "my_lib.h"

void GoTo16MHz(){
    CLKPR = 0x80;
    CLKPR = 0;
}

int main(void)
{
    uint8_t recv_data;

    GoTo16MHz();
    USART1_Init();

    while (1) {
        recv_data = 0x01;
        UART1_Byte_Send(recv_data);
    }
}

