/*
 * my_PWM.c
 *
 * Created: 2018/09/19 12:28:10
 *  Author: yama
 */ 

// 4�o�̓T�|�[�g (OC1A:PB5, OC1B:PB6, OC1C:PB7, OC3A:PC6)
// ������0�`32.8ms�̊�.

#define F_CPU 16000000UL //�}�C�R���̓�����g��(16MHz)

#include <avr/io.h>

void PWM16_Init( uint16_t width ) // width = ����/0.5us
                                  // 0   <= width <= 65535
								  // 0ms <= ����  <= 32.8ms 
{
	//�^�C�}/�J�E���^1���䃌�W�X�^A
	TCCR1A = 0b00000010;  //7-6: 00 (OC1A�̔g�`�o�͖���)
	                      //5-4: 00 (OC1B�̔g�`�o�͖���)
						  //3-2: 00 (OC1C�̔g�`�o�͖���)
						  //1-0: 10 (����PWM����:�ő�lICR1)
	//�^�C�}/�J�E���^1���䃌�W�X�^B
	TCCR1B = 0b00011010;  //7-5:  00 (���g�p)
	                      //4-3:  11 (����PWM����:�ő�lICR1)
	                      //2-0: 010 (����1/8)
						  
	// 1�������̃J�E���g�l 	  	
	ICR1 = width - 1; 
	
	//PB5(OC1A), PB6(OC1B), PB7(OC1C)�̌������o��
	DDRB |= 0b11100000;

	//�^�C�}/�J�E���^3���䃌�W�X�^A
	TCCR3A = 0b00000010;  //7-6: 00 (OC3A�̔g�`�o�͖���)
 	                      //1-0: 10 (����PWM����:�ő�lICR3)
						   
	//�^�C�}/�J�E���^3���䃌�W�X�^B
	TCCR3B = 0b00011010;  //7-5:  00 (���g�p)
	                      //4-3:  11 (����PWM����:�ő�lICR3)
	                      //2-0: 010 (����1/8)
	
	// 1�������̃J�E���g�l
	ICR3 = width - 1;
	
	//�|�[�gPC6(OC3A)�̌������o��
	DDRC |= 0b01000000;
}

// OC1A(0bit), OC1B(1bit), OC1C(2bit), OC3A(3bit)�o�͂�
// �p���X���𐮐��l(width)�Őݒ�
// ���ԕ� = width * 0.5us
void PWM16_PulseWidth( uint8_t ch, uint16_t width)
{
	if ( (ch & 0b0001) != 0 ) OCR1A = width;
	if ( (ch & 0b0010) != 0 ) OCR1B = width;
	if ( (ch & 0b0100) != 0 ) OCR1C = width;
	if ( (ch & 0b1000) != 0 ) OCR3A = width;
}

//PWM�o�͂��J�n
//OC1A(0bit)�COC1B(1bit), OC1C(2bit), OC3A(3bit)
void PWM16_Start( uint8_t ch )
{
	if ( (ch & 0b0001) != 0 ) 
		TCCR1A |= 0b10000000; //7-6: 10 (OC1A�̓R���y�A�}�b�`A��LOW)
		
	if ( (ch & 0b0010) != 0)
		TCCR1A |= 0b00100000; //5-4: 10 (OC1B�̓R���y�A�}�b�`B��LOW)

	if ( (ch & 0b0100) != 0)
		TCCR1A |= 0b00001000; //3-2: 10 (OC1C�̓R���y�A�}�b�`C��LOW)
	
	if ( (ch & 0b1000) != 0)
		TCCR3A |= 0b10000000; //7-6: 10 (OC3A�̓R���y�A�}�b�`A��LOW)	
}

//PWM�o�͂��~
//OC1A(0bit)�COC1B(1bit), OC1C(2bit), OC3A(3bit)
void PWM16_Stop( uint8_t ch )
{
	if ( (ch & 0b0001) != 0 )
	TCCR1A &= ~0b10000000; //7-6: 10 (OC1A�͏o�͖���)
	
	if ( (ch & 0b0010) != 0)
	TCCR1A &= ~0b00100000; //5-4: 10 (OC1B�͏o�͖���)

	if ( (ch & 0b0100) != 0)
	TCCR1A &= ~0b00001000; //3-2: 10 (OC1C�͏o�͖���)
	
	if ( (ch & 0b1000) != 0)
	TCCR3A &= ~0b10000000; //7-6: 10 (OC3A�͏o�͖���)
}