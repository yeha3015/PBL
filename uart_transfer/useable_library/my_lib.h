/*
 * my_lib.h
 *
 * Created: 2018/09/19 13:05:45
 *  Author: yama
 */ 


#ifndef MY_LIB_H_
#define MY_LIB_H_

//==================================================
// �V���A���ʐM(UART1)�֘A
//==================================================
#define CTS_ON  1
#define CTS_OFF 0

void USART1_Init( );

// UART1�ւ̃o�C�g�f�[�^�̑��M
void UART1_Byte_Send ( uint8_t );

// UART1����o�C�g�f�[�^�̎�M
uint8_t UART1_Byte_Recv ( void );

void my_printf(char *msg, const char *format, ...);

uint16_t ADC_Read( uint8_t ); //AD�ϊ��f�[�^(10bit)�̑��M
//==================================================

//==================================================
// AD�ϊ���֘A
//==================================================
void     AD_Init     ( void    );
void     selADchannel( uint8_t );
uint16_t ADC_Read    ( uint8_t );
//==================================================

//==================================================
// PWM16�֘A
//==================================================
void PWM16_Init( uint16_t );
void PWM16_PulseWidth( uint8_t, uint16_t);
void PWM16_Start( uint8_t);
void PWM16_Stop( uint8_t ch );
//==================================================

//==================================================
// �ėp�|�[�g�֘A(PB��PD�������፬��)
//==================================================
void PortDirection(uint8_t, uint8_t);
void PortWriteBit (uint8_t, uint8_t);
//==================================================

#endif /* MY_LIB_H_ */