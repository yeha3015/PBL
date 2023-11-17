/*
 * my_ADC.c
 *
 * Created: 2018/09/14 16:58:57
 *  Author: yama
 */ 

#define F_CPU 16000000UL //�}�C�R���̓�����g��(16MHz)

#include <avr/io.h>

void AD_Init( void )
{
	// ADC�̏�����
	ADMUX = 0 ;// �d��5V(AVref)���g�p, �f�[�^�E�l��
	ADCSRA |= _BV(ADPS2) | _BV(ADPS0); // ADEN, ADSC, CK/32
}

void selADchannel(uint8_t x)
{
	uint8_t tmp ;
	
	ADCSRA &= ~_BV(ADEN); // ADC���֎~
	
	/* judge */
	if ( x > 15 ) return ;
	/* get now mode */
	tmp = ADMUX ;
	/* clear multiplexer */
	tmp &= 0xf0 ;
	/* select new channel */
	ADMUX = tmp | x ;
	
	ADCSRA |= _BV(ADEN); // ADC������
}

uint16_t ADC_Read( uint8_t ch_num )
{
	selADchannel(ch_num); // ADC�̃`�����l����I��
	ADCSRA |= _BV(ADSC);     // AD���X�^�[�g
	while( (ADCSRA & _BV(ADIF)) == 0 ); // AD�ϊ��̏I����҂�
	ADCSRA &= ~_BV(ADIF); // �I���t���O�̃��Z�b�g
	return ( ADC & 0x3ff ); // AD�ϊ����ʂ�Ԃ��D
}

