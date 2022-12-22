/*
 * main.h
 *
 *
 * Created: 15.02.2022 14:35:53
 *  Author: user
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL // ���������� ������� ���������������� ��� �������� _delay_us
#include "avr/io.h"
#include "avr/wdt.h"
#include "util/delay.h"
#include "avr/eeprom.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "modbus/mb.h"
#include "modbus/mbrtu.h"
#include "modbus/mbport.h"
#include "modbus/mbutils.h"

/* ----------------------- Defines ------------------------------------------*/
#define REG_INPUT_START 512
#define REG_INPUT_NREGS 16
#define REG_COILS_START     200
#define REG_COILS_SIZE      16
#define REG_HOLDING_START 528
#define REG_HOLDING_NREGS 16
/* ----------------------- Defines ------------------------------------------*/
#define MB_PDU_FUNC_READ_ADDR_OFF               ( MB_PDU_DATA_OFF + 0)
#define MB_PDU_FUNC_READ_REGCNT_OFF             ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_READ_SIZE                   ( 4 )
#define MB_PDU_FUNC_READ_REGCNT_MAX             ( 0x007D )

#define MB_PDU_FUNC_WRITE_ADDR_OFF              ( MB_PDU_DATA_OFF + 0)
#define MB_PDU_FUNC_WRITE_VALUE_OFF             ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_WRITE_SIZE                  ( 4 )

#define MB_PDU_FUNC_WRITE_MUL_ADDR_OFF          ( MB_PDU_DATA_OFF + 0 )
#define MB_PDU_FUNC_WRITE_MUL_REGCNT_OFF        ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_WRITE_MUL_BYTECNT_OFF       ( MB_PDU_DATA_OFF + 4 )
#define MB_PDU_FUNC_WRITE_MUL_VALUES_OFF        ( MB_PDU_DATA_OFF + 5 )
#define MB_PDU_FUNC_WRITE_MUL_SIZE_MIN          ( 5 )
#define MB_PDU_FUNC_WRITE_MUL_REGCNT_MAX        ( 0x0078 )

#define MB_PDU_FUNC_READWRITE_READ_ADDR_OFF     ( MB_PDU_DATA_OFF + 0 )
#define MB_PDU_FUNC_READWRITE_READ_REGCNT_OFF   ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_READWRITE_WRITE_ADDR_OFF    ( MB_PDU_DATA_OFF + 4 )
#define MB_PDU_FUNC_READWRITE_WRITE_REGCNT_OFF  ( MB_PDU_DATA_OFF + 6 )
#define MB_PDU_FUNC_READWRITE_BYTECNT_OFF       ( MB_PDU_DATA_OFF + 8 )
#define MB_PDU_FUNC_READWRITE_WRITE_VALUES_OFF  ( MB_PDU_DATA_OFF + 9 )
#define MB_PDU_FUNC_READWRITE_SIZE_MIN          ( 9 )
/* ----------------------- Defines ------------------------------------------*/
#define MB_PDU_SIZE_MAX     253 /*!< Maximum size of a PDU. */
#define MB_PDU_SIZE_MIN     1   /*!< Function Code */
#define MB_PDU_FUNC_OFF     0   /*!< Offset of function code in PDU. */
#define MB_PDU_DATA_OFF     1   /*!< Offset for response data in PDU. */

#define AREF_MV		2500 // ����� ��������� �� 21 ����
#define MAX_AREF_MV		2800 // ����� ��������� �� 21 ����
#define MIN_AREF_MV		2300 // ����� ��������� �� 21 ����

#define R_OM		2000 // ����� �� �������� �������� ������������ �� +5
#define MAX_R_OM		2300 // ����� �� �������� �������� ������������ �� +5
#define MIN_R_OM		1700 // ����� �� �������� �������� ������������ �� +5

#define UP_MV		5000 // ��������� ������ mega328, ���������
#define MAX_UP_MV		5300 // ��������� ������ mega328, ���������
#define MIN_UP_MV		4700 // ��������� ������ mega328, ���������

 uint16_t Upower_mv_RAM ; //  ���������� ������
 uint16_t Uaref_mv_RAM ; //  ���������� Uaref
 uint16_t Rtd_om_RAM ; //  �������������_�� �������� ������������ �� +5
 uint16_t setup_termo_gradus ;	// LW200_ ==> usReg_HOLDING_Buf[1]		
 uint16_t setup_termo_max_us ; // LW201_termo_max_us ==> usReg_HOLDING_Buf[2]

static uint16_t	usRegInputStart			= REG_INPUT_START;
uint16_t		usRegInputBuf[REG_INPUT_NREGS];
static uint16_t	usReg_HOLDING_Start		= REG_HOLDING_START;
uint16_t		usReg_HOLDING_Buf[REG_HOLDING_NREGS];
static uint8_t	ucRegCoilsBuf[REG_COILS_SIZE / 8];

bool status_pin_ten;		// PC5 =>	pin28
bool status_pin_us;			// PC4 =>	pin27
bool status_pin_us2_out1;	// PD5 =>	pin11
bool status_pin_us3_out2;	// PD2 =>	pin4
bool status_pin_vent_out3;	// PC2 =>	pin25
bool status_pin_out4;		// PB2 =>	pin16
bool status_pin_fs_out5;	// PB1 =>	pin15
bool infa_err_td;			// ==1 ���� ������ ������������,   ==0 ��� ����
uint16_t count_infa_err_td=0;


bool input_IN_main_plata;	// pin24 => PC1 => c ������ LW202.8_mode_DatLevel == usReg_HOLDING_Buf[3].8	���� ���� ������ ����� ������������� ==>  input_DU ==>  ==1 ���� ����,  ==0 ���
bool input_button_US;		// pin18 => PB4 => ������ ������ ==0, �������� ==1 (������ +5)	==> ����� �������� ������� ���������� �� ���������� ������		   ==>	usRegInputBuf[2].1 ==>	LW101i1_btn_us		���������
bool input_button_TEN;		// pin19 => PB5 => ������ ������ ==0, �������� ==1	(������ +5)	==> ����� �������� ������� ���������� �� ���������� ������		   ==>	usRegInputBuf[2].2 ==>	LW101i2_btn_ten		���������
bool input_IN1_adv_plata;	// pin6  => PD4 => ���������� ������� ������ ==0, ������� ==1	==> ������ +24�, ������ ��������, ������ �������� ����� ����������.==>	usRegInputBuf[2].3 ==>	LW101i3_di1_adv		==1 ������ +24�,   ==0 ���
bool input_IN2_adv_plata;	// pin5  => PD3 => ���������� ������� ������ ==0, ������� ==1	==> ������ +24�, ������ ��������, ������ �������� ����� ����������.==>	usRegInputBuf[2].4 ==>	LW101i4_di2_adv		==1 ������ +24�,   ==0 ���
bool input_IN3_adv_plata;	// pin14 => PB0 => ���������� ������� ������ ==0, ������� ==1	==> ������ +24�, ������ ��������, ������ �������� ����� ����������.==>	usRegInputBuf[2].5 ==>	LW101i5_di3_adv		==1 ������ +24�,   ==0 ���
bool input_IN4_adv_plata;	// pin13 => PD7 => ���������� ������� ������ ==0, ������� ==1	==> ������ +24�, ������ ��������, ������ �������� ����� ����������.==>	usRegInputBuf[2].6 ==>	LW101i6_di4_adv		==1 ������ +24�,   ==0 ���
bool input_IN5_adv_plata;	// pin12 => PD6

int8_t count_PC5; // =>	pin28
int8_t count_PC4; // =>	pin27
int8_t count_PD5; // =>	pin11
int8_t count_PD2; // =>	pin4
int8_t count_PC2; // =>	pin25
int8_t count_PB2; // =>	pin16
int8_t count_PB1; // =>	pin15

int8_t count_PC1; // => pin24
int8_t count_PB4; // => pin18
int8_t count_PB5; // => pin19
int8_t count_PD4; // => pin6
int8_t count_PD3; // => pin5
int8_t count_PB0; // => pin14
int8_t count_PD7; // => pin13
int8_t count_PD6; // => pin12

eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode );
eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs );
eMBException eMBFuncWriteMultipleHoldingRegister( UCHAR * pucFrame, USHORT * usLen );
eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode );
eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete);


void ADC_init_Pt1000(void);
void ADC_init_NTC(void);
uint16_t  zamer_ADC_tmprt_Pt1000(float Up_mv, float Aref_mv, float R_om);
uint16_t  zamer_ADC_tmprt_NTC(float R_om);
void read_pin_in_out(void);

#endif /* MAIN_H_ */