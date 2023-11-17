/*
 * my_uart.c
 *
 * Created: 2018/09/14 14:50:27
 *  Author: yama
 */ 
#define F_CPU 16000000UL //�}�C�R���̓�����g��(16MHz)

#include <stdio.h>

#include <avr/io.h>

 // �V���A���ʐM�̐ݒ� (115.2kbps)
 void USART1_Init( void )
 {
	 UBRR1  = 8; // ������g��(Hz) / (�{�[���[�g * 16) - 1
	 UCSR1A = 0b00000000;
	 UCSR1B = 0b00011000; // ����M��
	 UCSR1C = 0b00000110; // �f�[�^8bit, �񓯊�, �p���e�B�Ȃ�, Stop 1bit
	 //UCSR1D = 0b00000010; // flow control : CTS�L��
	 UCSR1D = 0b00000000; // flow control : CTS����
 }

 // UART1�ւ̃o�C�g�f�[�^�̑��M
 void UART1_Byte_Send ( uint8_t data )
 {
	 while( ( UCSR1A & ( 1 << UDRE1 ) ) == 0 ); // ���M�t���O�����܂ő҂D
	 UDR1 = data;
 }

 // UART1����o�C�g�f�[�^�̎�M
 uint8_t UART1_Byte_Recv ( void )
 {
	 while( ( UCSR1A & 0b10000000 ) == 0 );  // ��M�t���O�����܂ő҂D

	 return UDR1; // UART1�̎�M���W�X�^�̓��e��Ԃ��D
 }
 
 //printf�����̋@�\(C����̉ϒ������Ƃ����e�N�����p)
 void my_printf(char *msg, const char *format, ...) {

	int i;
	int  msg_len;

	va_list ap;
	
	//printf�̏����ɏ]���ĉϒ������𕶎���Ƃ���msg�Ɋi�[�D
	//�i�[����������̕�������Ԃ��D
	va_start(ap, format);
	msg_len = vsprintf(msg, format, ap);
	va_end(ap);

	//���������C�ϊ�������̊e�������p�\�R���ɃV���A�����M
	for(i = 0; i < msg_len ; i++ ) UART1_Byte_Send(msg[i]);
}

// UART1�ւ�10bit��ADC�f�[�^�𑗐M(2�o�C�g���M�ɂȂ�܂�)�D
void UART1_ADC_Data_Send ( uint16_t ad_data )
{
	while( ( UCSR1A & ( 1 << UDRE1 ) ) == 0 ); // ���M�t���O�����܂ő҂D
	UDR1 = ad_data; // ����1�o�C�g�𑗐M
	
	while( ( UCSR1A & ( 1 << UDRE1 ) ) == 0 ); // ���M�t���O�����܂ő҂D
	UDR1 = ad_data >> 8; // ���1�o�C�g�𑗐M	
}

