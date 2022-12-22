/*
 * mb485_16_mega328_US.cpp
 *
 *
 * Created: 17.03.2022 7:23:14
 * Author : durov_av
 
				 LW200_termo_set	==> usReg_HOLDING_Buf[1]	==> setup_termo_gradus
				 LW201_termo_max_us ==> usReg_HOLDING_Buf[2]	==> setup_termo_max_us
				 LW202_cmd__xx__	==> usReg_HOLDING_Buf[3]	==> входящие команды от кинко
				 LW203_Upower_td	==> usReg_HOLDING_Buf[4]	==> напряжение питания +5в на термодатчике 
				 LW204_Uaref_td		==> usReg_HOLDING_Buf[5]	==> напряжение Aref   +5=2kom=Aref=2kom=GND   для термодатчика
				 LW205_Rtd5v		==> usReg_HOLDING_Buf[6]	==> сопротивление (2кОм), подвески ТД на   +5  от термодатчика
				 
				 termo_curr_x10			==> usRegInputBuf[1]	=> LW100_termo_current_x10  +10
				 infa_discret ._x_		==> usRegInputBuf[2]	=> LW101.x
				 info_OUT_onoff ._x_	==> usRegInputBuf[3]	=> LW102.x
				 motochas_mm_US			==> usRegInputBuf[4]	==>LW103
				 motochas_hh_US			==> usRegInputBuf[5]	==>LW104
				 motochas_mm_TEN		==> usRegInputBuf[6]	==>LW105
				 motochas_hh_TEN		==> usRegInputBuf[7]	==>LW106
				 motochas_mm_FS			==> usRegInputBuf[8]	==>LW107
				 motochas_hh_FS			==> usRegInputBuf[9]	==>LW108
				 
				 // ================== CMD ===================== //cmd_vent_out3
				 LW202.0_cmd_nagrev		==>	usReg_HOLDING_Buf[3].0 ==>	PC5 =>	pin28 => status_pin_ten	=>	LED-HEAT =>		Выход ТEN-triac		==>	info_ten	==>	usRegInputBuf[3].0 ==>	LW102i0_info_onoff_ten		
				 LW202.1_cmd_nagrev2	==>	usReg_HOLDING_Buf[3].1 ==>
				 LW202.2_cmd_us			==>	usReg_HOLDING_Buf[3].2 ==>	PC4 =>	pin27 => status_pin_us		=>	LED-SONIC =>	Выход OK TIMER ==>	info_us		==>	usRegInputBuf[3].2 ==>	LW102i2_infa_us
				 LW202.3_cmd_us2_out1	==>	usReg_HOLDING_Buf[3].3 ==>	PD5 =>	pin11 => status_pin_us2_out1 =>	плата_расш =>	Выход_ OUT1 ==>		info_out1	==>	usRegInputBuf[3].3 ==>	LW102i3_infa_onoff_out1
				 LW202.4_cmd_us3_out2	==>	usReg_HOLDING_Buf[3].4 ==>	PD2 =>	pin4  => status_pin_us3_out2 =>	плата_расш =>	Выход_ OUT2 ==>		info_out2	==>	usRegInputBuf[3].4 ==>	LW102i4_infa_onoff_out2
				 LW202.5_cmd_out4		==>	usReg_HOLDING_Buf[3].5 ==>	PB2 =>	pin16 => status_pin_out4	=>	плата_расш =>	Выход_ OUT4 ==>		info_out4	==>	usRegInputBuf[3].5 ==>	LW102i5_infa_onoff_out4
				 LW202.6_cmd_fs_out5	==>	usReg_HOLDING_Buf[3].6 ==>	PB1 =>	pin15 => status_pin_fs_out5 =>	плата_расш =>	Выход_ OUT5 ==>		info_out5	==>	usRegInputBuf[3].6 ==>	LW102i6_infa_onoff_out5
				 LW202.7_cmd_vent_out3  ==>	usReg_HOLDING_Buf[3].7 ==>	PC2 =>	pin25 => status_pin_vent_out3=>	плата_расш =>	Выход_ OUT3 ==>		info_out3	==>	usRegInputBuf[3].7 ==>	LW102i7_infa_onoff_out3
				 LW202.8_mode_termodat	==>	usReg_HOLDING_Buf[3].8 ==>  ==0 термодатчик NTC_10kOm,    ==1 термодатчик Pt1000
				 LW202.9_mode_DatLevel	==>	usReg_HOLDING_Buf[3].9 ==>  ==0 геркон на +24в,    ==1 датчик уровня термический OK-NPN
				 LW202.F_modbus			==>	usReg_HOLDING_Buf[3].F ==>		=== modbus_on_off ===																==>	usRegInputBuf[3].F ==>	LW102iF_modbus_onoff
				 
				 // ================ Input ===================== //
				 input_IN_main_plata ==>	pin24 => PC1 => зажигается входной оптрон ==0, погашен ==1	==> нет воды геркон опущен-закорочен-оптрон-горит, сигнал идет 1к1 ==>	input_DU ==>  usRegInputBuf[2].0 ==>	LW101i0_du		==1 есть вода,  ==0 нет
				 input_IN1_adv_plata ==>	pin6  => PD4 => зажигается входной оптрон ==0, погашен ==1	==> подано +24в, оптрон зажжется, сигнал дискрета будет инвертиров.==>	usRegInputBuf[2].1 ==>	LW101i1_di1_adv		==1 подано +24в,   ==0 нет
				 input_IN2_adv_plata ==>	pin5  => PD3 => зажигается входной оптрон ==0, погашен ==1	==> подано +24в, оптрон зажжется, сигнал дискрета будет инвертиров.==>	usRegInputBuf[2].2 ==>	LW101i2_di2_adv		==1 подано +24в,   ==0 нет
				 input_IN3_adv_plata ==>	pin14 => PB0 => зажигается входной оптрон ==0, погашен ==1	==> подано +24в, оптрон зажжется, сигнал дискрета будет инвертиров.==>	usRegInputBuf[2].3 ==>	LW101i3_di3_adv		==1 подано +24в,   ==0 нет
				 input_button_US	 ==>	pin18 => PB4 => нажата кнопка ==0, отпущена ==1 (подвес +5)	==> будет работать функция перекидоса по отпусканию кнопки		   ==>	usRegInputBuf[2].4 ==>	LW101i4_btn_us		перекидос
				 input_button_TEN	 ==>	pin19 => PB5 => нажата кнопка ==0, отпущена ==1	(подвес +5)	==> будет работать функция перекидоса по отпусканию кнопки		   ==>	usRegInputBuf[2].5 ==>	LW101i5_btn_ten		перекидос
				 input_IN4_adv_plata ==>	pin13 => PD7 => зажигается входной оптрон ==0, погашен ==1	==> подано +24в, оптрон зажжется, сигнал дискрета будет инвертиров.==>	usRegInputBuf[2].6 ==>	LW101i6_di4_adv		==1 подано +24в,   ==0 нет
				 input_IN5_adv_plata ==>	pin12 => PD6 => зажигается входной оптрон ==0, погашен ==1	==> подано +24в, оптрон зажжется, сигнал дискрета будет инвертиров.==>	usRegInputBuf[2].7 ==>	LW101i7_di5_adv		==1 подано +24в,   ==0 нет
				 
*/ 

#include "main.h"

uint8_t			flag_count_press_button	= 0; // ==0xFF значит надо опросить кнопки и сбросить флаг,  ==0 прокинуть опрос.

uint8_t			MB_adres ;
const uint8_t	ucSlaveID[] = { 0xAA, 0xBB, 0xDD };
eMBErrorCode    eStatus;
bool			flag_USART_TX_vect ; // ==1 значит закончилась передача, можно переводить приемник на прием

uint8_t			count_61_isr16ms;
uint8_t			temp_portB;
uint8_t			temp_portC;
uint8_t			temp_portD;
uint16_t		temp_usRegInputBuf;
float		tmprt_curr_float;
float		tmprt_izm_float;
uint16_t	temp_tmprt_uint16;
float		array_tmprt_izm[100];
uint8_t		index_tmprt=0;
bool		DatLevel; //  ==1 есть уровень,   ==0 нет воды

uint16_t	temp_zero =0;
uint16_t	adr_offset_EE ; //			EE[0] - смещение адреса в еепроме, где лежат моточасы, будет кратно 65500, после превышения счетчика записей будет перескакивать на страничку адреса +16
uint16_t	count_65500;	//			EE[adr_offset_EE +2]
uint16_t	motochas_mm_US; //			EE[adr_offset_EE +4] ==> usRegInputBuf[4]	==>LW103
uint16_t	motochas_hh_US; //			EE[adr_offset_EE +6] ==> usRegInputBuf[5]	==>LW104
uint16_t	motochas_mm_TEN; //			EE[adr_offset_EE +8] ==> usRegInputBuf[6]	==>LW105
uint16_t	motochas_hh_TEN; //			EE[adr_offset_EE +10] ==> usRegInputBuf[7]	==>LW106
uint16_t	motochas_mm_FS; //			EE[adr_offset_EE +12] ==> usRegInputBuf[8]	==>LW107
uint16_t	motochas_hh_FS; //			EE[adr_offset_EE +14] ==> usRegInputBuf[9]	==>LW108
uint8_t		count_sec_motochas_US;	
uint8_t		count_sec_motochas_TEN;
uint8_t		count_sec_motochas_FS;
uint16_t	count_600sec_vent; //  600 сек должны работать вентиляторы после УЗ любого
			 
bool cmd_nagrev_mb;		// usReg_HOLDING_Buf[3].0 == LW202.x
bool cmd_nagrev2_mb;	// usReg_HOLDING_Buf[3].1
bool cmd_us_mb;			// usReg_HOLDING_Buf[3].2
bool cmd_us2_out1_mb;	// usReg_HOLDING_Buf[3].3
bool cmd_us3_out2_mb;	// usReg_HOLDING_Buf[3].4
bool cmd_out4_mb;		// usReg_HOLDING_Buf[3].5
bool cmd_fs_out5_mb;	// usReg_HOLDING_Buf[3].6
bool cmd_vent_out3_mb;	// usReg_HOLDING_Buf[3].7
bool mode_termodat;		// usReg_HOLDING_Buf[3].8 ==>  ==0 термодатчик NTC_10kOm,    ==1 термодатчик Pt1000
bool mode_DatLevel;		// usReg_HOLDING_Buf[3].9 ==>  ==0 геркон вверх на +24в,    ==1 датчик уровня термический OK-NPN(или болт - тоже самое)
bool cmd_0xA_mb;		// usReg_HOLDING_Buf[3].A
bool cmd_0xB_mb;		// usReg_HOLDING_Buf[3].B
bool cmd_0xC_mb;		// usReg_HOLDING_Buf[3].C
bool cmd_0xD_mb;		// usReg_HOLDING_Buf[3].D
bool cmd_0xE_mb;		// usReg_HOLDING_Buf[3].E
bool status_indikator_MB;//usReg_HOLDING_Buf[3].F ==>  получаем в регистр LW202.f->usReg_HOLDING_Buf[3].f  в инверсии уходит на   usRegInputBuf[3].f->LW102.f
bool old_mode_termodat =0;	// для выделения фронта флага изменения типа термодатчика

bool cmd_ten_real;		// cmd_nagrev_mb ==> с учетом температуры и датчика уровня
bool cmd_us_real;		// cmd_us_mb ==> с учетом MAX-температуры и датчика уровня
bool cmd_us2_out1_real;	// cmd_us2_mb ==> с учетом MAX-температуры и датчика уровня
bool cmd_us3_out2_real;	// cmd_us3_mb ==> с учетом MAX-температуры и датчика уровня
bool cmd_vent_out3_real;// или cmd_vent_out3_mb <==> или 600сек после любого cmd_usX_real
bool cmd_out4_real;		// пока  ==cmd_out4_mb, но потом могут появиться какие либо доп условия
bool cmd_fs_out5_real;	// cmd_fs_out5_mb  с учетом  датчика уровня


// -----------------------INTERRUPT ---------------------------------------- //
// -----------------------INTERRUPT ---------------------------------------- //
ISR (USART_TX_vect)
{  PORTC &= ~( 1<< 3); } // перевод UART в режим приема

ISR (USART_UDRE_vect)
{ xMBRTUTransmitFSM();}

ISR (USART_RX_vect)
{ xMBRTUReceiveFSM();}

ISR( TIMER1_COMPA_vect )
{ ( void )xMBRTUTimerT35Expired();}

ISR (TIMER2_OVF_vect) /** Timer interrupt to control the sampling interval */
{ flag_count_press_button =0xFF; } // флаг опроса кнопок поднимаем, получитьс¤ опрос через ~~16,4 ms,  там же и стартует ј?ѕ

// --------------------------- fun === fun === fun === fun === fun === fun === fun ------------------------------------------------------ //
// --------------------------- fun === fun === fun === fun === fun === fun === fun ------------------------------------------------------ //
void initTimer2() 
{           // счЄтчик будет тикать до 256, такт 16Мгц будет делиться предделителем на 1024, COUNT_secunda будет делиться на 61 в main() - это будет считаться 1сек.
	TCNT2 = 0x00; // initial value
	//	TCCR2A |= (1<< COM2B0) ; //| (1<< COM2B1); //(1 << WGM21) | (1 << WGM20) |   // перекид ноги 5 - PORTD3 - OC2B этот вывод ¤ подключал дл¤ проверки частоты кварца, OCR2B = pin.5 PORTD.3
	TCCR2B |= (1 << CS20) | (1 << CS21) | (1 << CS22); // | (1 << WGM22) ; // frequency F_CPU/1024
	TIMSK2 |= (1<< TOIE2);
}
uint16_t write_new_motochas(uint16_t address_offset);


int main(void)
{
 Upower_mv_RAM = 5000; //  миливольты питани¤
 Uaref_mv_RAM = 2500; //  миливольты Uaref
 Rtd_om_RAM = 2000; //  сопротивление_ќм подвески термодатчика на +5


 // вначале считаем значения моточасов из памяти, потом читать не будем, только записывать, паралельно с ++ counta
 adr_offset_EE		= eeprom_read_word((uint16_t *)temp_zero); // смещение адреса в еепроме, где лежат моточасы, будет кратно 65500, после превышения счетчика записей будет перескакивать на страничку адреса +16
 count_65500		= eeprom_read_word((uint16_t *)(adr_offset_EE + 2)); //
 motochas_mm_US		= eeprom_read_word((uint16_t *)(adr_offset_EE + 4)); //	==> usRegInputBuf[4]	==>LW103
 motochas_hh_US		= eeprom_read_word((uint16_t *)(adr_offset_EE + 6)); //	==> usRegInputBuf[5]	==>LW104
 motochas_mm_TEN	= eeprom_read_word((uint16_t *)(adr_offset_EE + 8)); //	==> usRegInputBuf[6]	==>LW105
 motochas_hh_TEN	= eeprom_read_word((uint16_t *)(adr_offset_EE + 10)); //	==> usRegInputBuf[7]	==>LW106
 motochas_mm_FS		= eeprom_read_word((uint16_t *)(adr_offset_EE + 12)); //	==> usRegInputBuf[8]	==>LW107
 motochas_hh_FS		= eeprom_read_word((uint16_t *)(adr_offset_EE + 14)); //	==> usRegInputBuf[9]	==>LW108
				 
		DDRB  = 0; // везде назначаем входа,
		PORTB = 0xFF; // подт¤жка всех входов к плюсу
		DDRC  = 0; // везде назначаем входа,
		//                                                PORTC = 0xFF; // подт¤жка всех входов к плюсу
		PORTC = 0;
		DDRD  = 0; // везде назначаем входа,
		PORTD = 0xFF ; // подт¤жка всех входов к плюсу

		// нo некоторые будут выходами, назначаем:
		DDRC |=(1<<3);		//	pin.26 mega328.PC3   выход для переключени¤  MAX485
		PORTC &= ~( 1<< 3); //	pin.26 mega328.PC3     =0 -Read_max485
		DDRC |=(1<<5);		//	PC5 =>	pin28 => status_pin_ten	=>		LED-HEAT =>		Выход ТEN-triac	==>	info_ten	==>	usRegInputBuf[3].0 ==>	LW102i0_info_onoff_ten	
							//					 status_pin_ten2=>		LED-HEAT =>										==>	usRegInputBuf[3].1 ==>	LW102i1_info_onoff_ten2
		DDRC |=(1<<4);		//	PC4 =>	pin27 => status_pin_us	=>		LED-SONIC =>	Выход OK TIMER ==>	info_us		==>	usRegInputBuf[3].2 ==>	LW102i2_infa_us
		DDRD |=(1<<5);		//	PD5 =>	pin11 => status_pin_us2_out1 =>	плата_расш =>	Выход_ OUT1 ==>		info_out1	==>	usRegInputBuf[3].3 ==>	LW102i3_infa_us2_onoff_out1
		DDRD |=(1<<2);		//	PD2 =>	pin4  => status_pin_us3_out2 =>	плата_расш =>	Выход_ OUT2 ==>		info_out2	==>	usRegInputBuf[3].4 ==>	LW102i4_infa_us3_onoff_out2
		DDRB |=(1<<2);		//	PB2 =>	pin16 => status_pin_out4 =>		плата_расш =>	Выход_ OUT4 ==>		info_out4	==>	usRegInputBuf[3].5 ==>	LW102i5_infa_onoff_out4
		DDRB |=(1<<1);		//	PB1 =>	pin15 => status_pin_fs_out5 =>	плата_расш =>	Выход_ OUT5 ==>		info_out5	==>	usRegInputBuf[3].6 ==>	LW102i6_infa_fs_onoff_out5
		DDRC |=(1<<2);		//	PC2 =>	pin25 => status_pin_vent_out3 =>плата_расш =>	Выход_ OUT3 ==>		info_out3	==>	usRegInputBuf[3].7 ==>	LW102i7_infa_vent_onoff_out3
		

		// PC0 будет входом АЦП, убрать подтяжку
		PORTC &= ~( 1<< 0); //	pin.23 mega328.PC0

		// ========== Timer2 будет долбить такты 16,4 мсек, использовать будем для запуска измерений ј?ѕ и для опроса клавиатур ”«-“ЁЌ============= //
		initTimer2();
		sei();
		

		// ========== сначала инициализируем наобум, потом придет флаг по модбусу, и поправим если надо будет
		ADC_init_NTC();

		// ====== setup ModBUS ===================== setup ModBUS ========= setup ModBUS =========================================//
		MB_adres = 16 ;  // такой адрес будет у всех плат УЗ-ванна
		cli();
		eStatus =	eMBInit( MB_RTU, MB_adres, 0, 9600, MB_PAR_NONE ); // скорость 9600, исключительно, потому что предполагается ещё на шине PHASER
		eStatus = 	eMBSetSlaveID( 0x34, TRUE, ucSlaveID, 3 );
		sei();
		eStatus = eMBEnable();// Enable the Modbus Protocol Stack.
		
		// ============ сторожевой таймер должен быть ============================== //
		wdt_reset(); // сброс сторожевого таймера
		wdt_enable(WDTO_1S);// включаем сторожевой таймер
		
		// =========== ну сначала, с разбега, пишем ADC_NTC, потом разберемся ==================== //
		ADC_init_NTC(); 

// ========== MAIN цикл цикл =========================== MAIN цикл цикл ========== MAIN цикл цикл ========== MAIN цикл цикл ==================================================//
// ========== MAIN цикл цикл =========================== MAIN цикл цикл ========== MAIN цикл цикл ========== MAIN цикл цикл ==================================================//
    while (1) 
    {
						// ====== проверим ModBUS ===================== проверим ModBUS ========= проверим ModBUS =========================================//
						if ( MB_ENOERR == eMBPoll() )
						{
							wdt_reset();  // сброс сторожевого таймера, если запрос модбуса NO ошибкой
							setup_termo_gradus = usReg_HOLDING_Buf[1];	// LW200_set_termo ==> usReg_HOLDING_Buf[1]	==> setup_termo_gradus
							setup_termo_max_us = usReg_HOLDING_Buf[2]; // LW201_time_obduv ==> usReg_HOLDING_Buf[2]	==> setup_termo_max75_gradus
							Upower_mv_RAM	=  usReg_HOLDING_Buf[4]	; // ==> напряжение питания +5в на термодатчике
							Uaref_mv_RAM	=  usReg_HOLDING_Buf[5]	; // ==> напряжение Aref   +5=2kom=Aref=2kom=GND   для термодатчика
							Rtd_om_RAM		=  usReg_HOLDING_Buf[6]	; // ==> сопротивление (2кОм), подвески ТД на   +5  от термодатчика

							// z = (x > y) ? x : y;
							cmd_nagrev_mb	=	((usReg_HOLDING_Buf[3] & (1 << 0))> 0) ? true : false; //LW202_cmd_x_ ==> usReg_HOLDING_Buf[3].0
							cmd_nagrev2_mb	=	((usReg_HOLDING_Buf[3] & (1 << 1))> 0) ? true : false;
							cmd_us_mb		=	((usReg_HOLDING_Buf[3] & (1 << 2))> 0) ? true : false; 
							cmd_us2_out1_mb	=	((usReg_HOLDING_Buf[3] & (1 << 3))> 0) ? true : false;
							cmd_us3_out2_mb	=	((usReg_HOLDING_Buf[3] & (1 << 4))> 0) ? true : false;
							cmd_out4_mb		=	((usReg_HOLDING_Buf[3] & (1 << 5))> 0) ? true : false;
							cmd_fs_out5_mb	=	((usReg_HOLDING_Buf[3] & (1 << 6))> 0) ? true : false;
							cmd_vent_out3_mb=	((usReg_HOLDING_Buf[3] & (1 << 7))> 0) ? true : false;
							mode_termodat	=	((usReg_HOLDING_Buf[3] & (1 << 8))> 0) ? true : false; // usReg_HOLDING_Buf[3].8 ==>  ==0 термодатчик NTC_10kOm,    ==1 термодатчик Pt1000
							mode_DatLevel	=	((usReg_HOLDING_Buf[3] & (1 << 9))> 0) ? true : false; // usReg_HOLDING_Buf[3].9 ==>  ==0 геркон на +24в,    ==1 датчик уровня термический OK-NPN
							cmd_0xA_mb		=	((usReg_HOLDING_Buf[3] & (1 <<0xA))>0) ? true : false;	// usReg_HOLDING_Buf[3].A
							cmd_0xB_mb		=	((usReg_HOLDING_Buf[3] & (1 <<0xB))>0) ? true : false;	// usReg_HOLDING_Buf[3].B
							cmd_0xC_mb		=	((usReg_HOLDING_Buf[3] & (1 <<0xC))>0) ? true : false;	// usReg_HOLDING_Buf[3].C
							cmd_0xD_mb		=	((usReg_HOLDING_Buf[3] & (1 <<0xD))>0) ? true : false;	// usReg_HOLDING_Buf[3].D
							cmd_0xE_mb		=	((usReg_HOLDING_Buf[3] & (1 <<0xE))>0) ? true : false;	// usReg_HOLDING_Buf[3].E
							status_indikator_MB=((usReg_HOLDING_Buf[3] & (1 <<0xF))>0) ? true : false;	// usReg_HOLDING_Buf[3].F  бит гоняется в инверсии для индикации модбуса  LW202.F != LW102.F

							// ============= настроим термодатчик ==========
							if (old_mode_termodat != mode_termodat)
							{			
								if (mode_termodat == true) 
									{ ADC_init_Pt1000(); }
								else
									{ ADC_init_NTC(); }	
							}//  if (old_mode_termodat != mode_termodat)
							else
							{// ===== если нет изменений термодатчика, делаем замер ============ 
								if (mode_termodat == true)
									{ 
										temp_tmprt_uint16 = zamer_ADC_tmprt_Pt1000 ((float) Upower_mv_RAM, (float) Uaref_mv_RAM, (float) Rtd_om_RAM);
										if (temp_tmprt_uint16 < 1900)
											{	tmprt_izm_float = ((float) temp_tmprt_uint16 ) /10.f -10.f; }	
									}
								else
									{ 
										temp_tmprt_uint16 = zamer_ADC_tmprt_NTC((float) Rtd_om_RAM);
										if (temp_tmprt_uint16 < 1900)
										{ tmprt_izm_float = ((float) temp_tmprt_uint16) /10.f -10.f; }
									}
								//  тут надо сделать усреднение для 10 последних значениям 					
								array_tmprt_izm[index_tmprt] = tmprt_izm_float;
								index_tmprt ++;
								if (index_tmprt >= 100) { index_tmprt =0; }
								tmprt_curr_float =0;
								for (int i=0; i<100; i++)
									{ tmprt_curr_float = tmprt_curr_float +array_tmprt_izm[i]; }
								tmprt_curr_float = tmprt_curr_float /100;
							}
							old_mode_termodat = mode_termodat;
						} //   if ( MB_ENOERR == eMBPoll() )


						// ====== опрос входов, таймер++ ===================== опрос входов, таймер++ ====== опрос входов, таймер++ =========================================//
						if (flag_count_press_button > 0) // 1 раз через 16,4 мсек флаг будет подниматьс¤ счётчиком таймера Timer2
						{
							read_pin_in_out();
							flag_count_press_button=0; // этот флажок был поднят в обработчике прерывани¤ таймера-2, с периодом 16,4 мсек
							// =========== ну и таймеры тут тоже плюсовать будем ================= // а их тут нет, ХА ХА
							count_61_isr16ms++;
							if(count_61_isr16ms >60)	// ==61 делим на 61
							{
								count_61_isr16ms =0;
								// COUNT_sec_obduv ++ ;    //  А если будут какие секундомеры, то ВОТ
								if((cmd_us_real ==TRUE) | (cmd_us2_out1_real ==TRUE) | (cmd_us3_out2_real ==TRUE))	{ count_sec_motochas_US++; }
								if (cmd_ten_real ==TRUE)															{ count_sec_motochas_TEN++; }
								if (cmd_fs_out5_real ==TRUE)														{ count_sec_motochas_FS++; }
								// если какой-то счетчик работы дотикал до 60 секунд, ++ минуту, и пишем в память новые моточасы
								if ((count_sec_motochas_US >=60) | (count_sec_motochas_TEN >=60) | (count_sec_motochas_FS >=60))
									{ adr_offset_EE = write_new_motochas(adr_offset_EE); }	
								if (count_600sec_vent >1)
									{ count_600sec_vent--;	}							
							}
							// проверить какой тип датчика задан и сформировать DatLevel  ==1 есть уровень,   ==0 нет воды
							if (mode_DatLevel ==1)//  ==0 геркон на +24в,    ==1 датчик уровня термический OK-NPN
								{ DatLevel = ~input_IN_main_plata; } // датчик уровня термический OK-NPN
							else
								{ DatLevel = input_IN_main_plata; }// геркон на +24в,
									
						}// ===== END END END ====== опрос входов, таймер++ ===================== опрос входов, таймер++ ====== опрос входов, таймер++ =========================================//

				
				// надо отработать допусловия  и  передать значения команд на пинЫ 
				// надо отработать допусловия  и  передать значения команд на пинЫ 
				// надо отработать допусловия  и  передать значения команд на пинЫ 
				if ((DatLevel ==1) & ((cmd_nagrev_mb==1) | (cmd_nagrev2_mb==1)))
					{
						if (tmprt_curr_float < ((float)setup_termo_gradus) -2) 
							{ 
								cmd_ten_real = 1;	// cmd_nagrev_mb ==> с учетом температуры и датчика уровня
							}
											
						if ( tmprt_curr_float > ( (float)setup_termo_gradus +2) )
							{
								cmd_ten_real = 0;	// cmd_nagrev_mb ==> с учетом температуры и датчика уровня
							}	
					}
				else
					{ cmd_ten_real = 0; }

				if ((tmprt_curr_float < ((float)setup_termo_max_us)) & (DatLevel ==1))
					{ 
						cmd_us_real			= cmd_us_mb;	// cmd_us_mb ==> с учетом температуры и датчика уровня	
						cmd_us2_out1_real	= cmd_us2_out1_mb;
						cmd_us3_out2_real	= cmd_us3_out2_mb;
					}	
				else
					{ 
						cmd_us_real = 0; 
						cmd_us2_out1_real = 0;
						cmd_us3_out2_real = 0;
					}
				if (cmd_us_real | cmd_us2_out1_real | cmd_us3_out2_real) // вентилятор работает или 600 сек после УЗ, или по команде от HMI
					{ count_600sec_vent =600; }
				cmd_vent_out3_real = cmd_vent_out3_mb | (count_600sec_vent >2);  // вентилятор работает или 600 сек после УЗ, или по команде от HMI
				cmd_out4_real = cmd_out4_mb;						// пока  ==cmd_out4_mb, но потом могут появиться какие либо доп условия
				cmd_fs_out5_real = cmd_fs_out5_mb & DatLevel;		// cmd_fs_out5_real - фильтр работает только при наличии воды


				// ============== формируем флаговые регистры на отправку ===============================
				// ============== формируем флаговые регистры на отправку ===============================
				usRegInputBuf[1] = (uint16_t) ((tmprt_curr_float +100.f) *100.f); // termo_curr_x100			==> usRegInputBuf[1]		=> LW100_termo_current_x100
				temp_usRegInputBuf =0;
				if (DatLevel			==true)	{ temp_usRegInputBuf |=(1<<0); } // pin24 => PC1 => c учетом LW202.8_mode_DatLevel == usReg_HOLDING_Buf[3].8	типа датч уровня будет формироваться ==>  input_DU ==>  ==1 есть вода,  ==0 нет
				if (input_IN1_adv_plata	==true)	{ temp_usRegInputBuf |=(1<<1); } // pin6  => PD4 => зажигается входной оптрон ==0, погашен ==1	==> подано +24в, оптрон зажжется, сигнал дискрета будет инвертиров.==>	usRegInputBuf[2].3 ==>	LW101i3_di1_adv		==1 подано +24в,   ==0 нет
				if (input_IN2_adv_plata	==true)	{ temp_usRegInputBuf |=(1<<2); } // pin5  => PD3 => зажигается входной оптрон ==0, погашен ==1	==> подано +24в, оптрон зажжется, сигнал дискрета будет инвертиров.==>	usRegInputBuf[2].4 ==>	LW101i4_di2_adv		==1 подано +24в,   ==0 нет
				if (input_IN3_adv_plata	==true)	{ temp_usRegInputBuf |=(1<<3); } // pin14 => PB0 => зажигается входной оптрон ==0, погашен ==1	==> подано +24в, оптрон зажжется, сигнал дискрета будет инвертиров.==>	usRegInputBuf[2].5 ==>	LW101i5_di3_adv		==1 подано +24в,   ==0 нет
				if (input_button_US		==true)	{ temp_usRegInputBuf |=(1<<4); } // pin18 => PB4 => нажата кнопка ==0, отпущена ==1 (подвес +5)	==> будет работать функция перекидоса по отпусканию кнопки		   ==>	usRegInputBuf[2].1 ==>	LW101i1_btn_us		перекидос
				if (input_button_TEN	==true)	{ temp_usRegInputBuf |=(1<<5); } // pin19 => PB5 => нажата кнопка ==0, отпущена ==1	(подвес +5)	==> будет работать функция перекидоса по отпусканию кнопки		   ==>	usRegInputBuf[2].2 ==>	LW101i2_btn_ten		перекидос
				if (input_IN4_adv_plata	==true)	{ temp_usRegInputBuf |=(1<<6); } // pin13 => PD7 => зажигается входной оптрон ==0, погашен ==1	==> подано +24в, оптрон зажжется, сигнал дискрета будет инвертиров.==>	usRegInputBuf[2].6 ==>	LW101i6_di4_adv		==1 подано +24в,   ==0 нет
				if (input_IN5_adv_plata	==true)	{ temp_usRegInputBuf |=(1<<7); } // pin12 => PD6
				usRegInputBuf[2] = temp_usRegInputBuf; // LW101.x
				temp_usRegInputBuf =0; 
				if (status_pin_ten	==true)		{ temp_usRegInputBuf |=(1<<0); } // PC5 =>	pin28
				if (status_pin_ten	==true)		{ temp_usRegInputBuf |=(1<<1); } // PC5 =>	pin28
				if (status_pin_us	==true)		{ temp_usRegInputBuf |=(1<<2); } // PC4 =>	pin27
				if (status_pin_us2_out1	==true)	{ temp_usRegInputBuf |=(1<<3); } // PD5 =>	pin11
				if (status_pin_us3_out2	==true)	{ temp_usRegInputBuf |=(1<<4); } // PD2 =>	pin4
				if (status_pin_out4	==true)		{ temp_usRegInputBuf |=(1<<5); } // PB2 =>	pin16
				if (status_pin_fs_out5	==true)	{ temp_usRegInputBuf |=(1<<6); } // PB1 =>	pin15		
				if (status_pin_vent_out3==true)	{ temp_usRegInputBuf |=(1<<7); } // PC2 =>	pin25
				if (infa_err_td	==true)			{ temp_usRegInputBuf |=(1<<14);} // ==1 есть авария термодатчика,   ==0 все норм
				if (status_indikator_MB ==false){ temp_usRegInputBuf |=(1<<15);} // получаем в регистр LW202.f->usReg_HOLDING_Buf[3].f  в инверсии уходит на   usRegInputBuf[3].f->LW102.f
				usRegInputBuf[3] = temp_usRegInputBuf; // LW102.x
				usRegInputBuf[4] = motochas_mm_US; //			==> usRegInputBuf[4]	==>LW103
				usRegInputBuf[5] = motochas_hh_US; //			==> usRegInputBuf[5]	==>LW104
				usRegInputBuf[6] = motochas_mm_TEN; //  		==> usRegInputBuf[6]	==>LW105
				usRegInputBuf[7] = motochas_hh_TEN; //  		==> usRegInputBuf[7]	==>LW106
				usRegInputBuf[8] = motochas_mm_FS; // 		==> usRegInputBuf[8]	==>LW107
				usRegInputBuf[9] = motochas_hh_FS; // 		==> usRegInputBuf[9]	==>LW108
				
				// ============== по сформированым cmd_xx_real  надо отправить их в порта  ===============================
				temp_portC =0;	
				temp_portD =0;
				temp_portB =0;	
				if(cmd_ten_real == true)		{ temp_portC |=(1<<5); }//	PC5 =>	pin28 => status_pin_ten	=>	LED-HEAT =>		Выход ТEN-triac	==>				
				if(cmd_us_real == true)			{ temp_portC |=(1<<4); }//	PC4 =>	pin27 => status_pin_us	=>	LED-SONIC =>	Выход OK TIMER ==> УЗ-дно
				if(cmd_us2_out1_real == true)	{ temp_portD |=(1<<5); }//	PD5 =>	pin11 => status_pin_us2_out1 =>	плата_расш =>	Выход_ OUT1 ==> УЗ-лево
				if(cmd_us3_out2_real == true)	{ temp_portD |=(1<<2); }//	PD2 =>	pin4  => status_pin_us3_out2 =>	плата_расш =>	Выход_ OUT2 ==>	УЗ-право
				if(cmd_vent_out3_real == true)	{ temp_portC |=(1<<2); }//	PC2 =>	pin25 => status_pin_vent_out3 =>плата_расш =>	Выход_ OUT3 ==> УЗ-вент
				if(cmd_out4_real == true)		{ temp_portB |=(1<<2); }//	PB2 =>	pin16 => status_pin_out4 =>	плата_расш =>		Выход_ OUT4 ==> резерв, может быть барботаж
				if(cmd_fs_out5_real == true)	{ temp_portB |=(1<<1); }//	PB1 =>	pin15 => status_pin_fs_out5 =>	плата_расш =>	Выход_ OUT5 ==> насос Фильтовальная Система
				PORTD = temp_portD;
				PORTB = temp_portB;
				// нефиг тут мешать работать модбусу, PORTC.3  сразу в обработчиик прерывания конца передачи
				cli();
					if((PORTC & (1 << 3)) == 0) // только если идет прием, меняем значение порта, если передача - то прокидываем
					{ PORTC = temp_portC; } // что бы случайно не помешать работе приемапередачи UART
				sei();
						
    } // while (1)
} // int main(void)

// ================================== функции модбуса ================================== функции модбуса ================================== функции модбуса ============= //

eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs ) 
{
	//(  4 ) //(0x04) Чтение значений из нескольких регистров ввода (Read Input Registers).
	//		REG_INPUT_START 100
	//		REG_INPUT_NREGS 16
	//		usRegInputStart = REG_INPUT_START;
	//		usRegInputBuf[REG_INPUT_NREGS];
	
	eMBErrorCode    eStatus = MB_ENOERR;
	int             iRegIndex;

	if( ( usAddress >= REG_INPUT_START ) && ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
	{
		iRegIndex = ( int )( usAddress - usRegInputStart );
		while( usNRegs > 0 )
		{
			*pucRegBuffer++ = ( unsigned char )( usRegInputBuf[iRegIndex] >> 8 );
			*pucRegBuffer++ =( unsigned char )( usRegInputBuf[iRegIndex] & 0xFF );
			iRegIndex++;
			usNRegs--;
		}
	}
	else
	{
		eStatus = MB_ENOREG;
	}

	return eStatus;
} // eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs ) 

eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
	// (  3 ) //(0x03) Ч чтение значений из нескольких регистров хранени¤ (Read Holding Registers).
	// (  6 ) //(0x06) Ч запись значени¤ в один регистр хранени¤ (Preset Single Register).
	//		REG_HOLDING_START 50
	//		REG_HOLDING_NREGS 16
	//		usReg_HOLDING_Start = REG_HOLDING_START;
	//		usReg_HOLDING_Buf[REG_HOLDING_NREGS];
	
	eMBErrorCode    eStatus = MB_ENOERR;
	int             iRegIndex;
	
////////////////////////////////////////////////////////       =========   „“?Ќ»?    ==============    ///////////////////////////////////////
	if( ( usAddress >= REG_HOLDING_START ) && ( usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS ) && ( eMode == MB_REG_READ))
	{
		
		//PORTD &=~(1<<2);
		iRegIndex = ( int )( usAddress - usReg_HOLDING_Start );
		while( usNRegs > 0 )
		{
			//PORTD &=~(1<<2);
			*pucRegBuffer++ =( unsigned char )( usReg_HOLDING_Buf[iRegIndex] >> 8 );
			*pucRegBuffer++ =( unsigned char )( usReg_HOLDING_Buf[iRegIndex] & 0x00FF );
			iRegIndex++;
			usNRegs--;
		}
	}
	else
	{
		if( ( eMode == MB_REG_READ)) {eStatus = MB_ENOREG;}
	}
	
////////////////////////////////////////////////////////       =========   «јѕ»—№    ==============    ///////////////////////////////////////	
	if( ( usAddress >= REG_HOLDING_START ) && ( usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS ) && ( eMode == MB_REG_WRITE))
	{
		eStatus = MB_ENOERR; // потому что там на команде 3 срабатывает ELSE
		iRegIndex = ( int )( usAddress - usReg_HOLDING_Start );
		while( usNRegs > 0 )
		{
			  usReg_HOLDING_Buf[iRegIndex] = (USHORT) * pucRegBuffer <<8;
			  *pucRegBuffer++;
			  usReg_HOLDING_Buf[iRegIndex] = usReg_HOLDING_Buf[iRegIndex] + (*pucRegBuffer);
			  *pucRegBuffer++;
			//*pucRegBuffer++ =( unsigned char )( usReg_HOLDING_Buf[iRegIndex] & 0xFF );
			iRegIndex++;
			usNRegs--;
		}
	}
	else
	{
		if( ( eMode == MB_REG_WRITE)) {eStatus = MB_ENOREG;}
	}
	return eStatus;
}// eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )

eMBException  eMBFuncWriteMultipleHoldingRegister( UCHAR * pucFrame, USHORT * usLen ) // команда 16
{
	USHORT          usRegAddress;
	USHORT          usRegCount;
	UCHAR           ucRegByteCount;

	eMBException    eStatus = MB_EX_NONE;
	eMBErrorCode    eRegStatus;

	if( *usLen >=  ( MB_PDU_FUNC_WRITE_MUL_SIZE_MIN + MB_PDU_SIZE_MIN ) )
	{
		usRegAddress = ( USHORT )( pucFrame[MB_PDU_FUNC_WRITE_MUL_ADDR_OFF] << 8 );
		usRegAddress |= ( USHORT )( pucFrame[MB_PDU_FUNC_WRITE_MUL_ADDR_OFF + 1] );
		usRegAddress++;

		usRegCount = ( USHORT )( pucFrame[MB_PDU_FUNC_WRITE_MUL_REGCNT_OFF] << 8 );
		usRegCount |= ( USHORT )( pucFrame[MB_PDU_FUNC_WRITE_MUL_REGCNT_OFF + 1] );

		ucRegByteCount = pucFrame[MB_PDU_FUNC_WRITE_MUL_BYTECNT_OFF];

		if( ( usRegCount >= 1 ) &&
		( usRegCount <= MB_PDU_FUNC_WRITE_MUL_REGCNT_MAX ) &&
		( ucRegByteCount == ( UCHAR ) ( 2 * usRegCount ) ) )
		{
			// Make callback to update the register values.
			eRegStatus = eMBRegHoldingCB( &pucFrame[MB_PDU_FUNC_WRITE_MUL_VALUES_OFF], usRegAddress, usRegCount, MB_REG_WRITE );

			// If an error occured convert it into a Modbus exception.
			if( eRegStatus != MB_ENOERR )
			{
				eStatus = MB_EX_NONE; //prveMBError2Exception( eRegStatus );
				switch (eRegStatus) //( eErrorCode )
				{
					case MB_ENOERR:
					eStatus = MB_EX_NONE;
					break;

					case MB_ENOREG:
					eStatus = MB_EX_ILLEGAL_DATA_ADDRESS;
					break;

					case MB_ETIMEDOUT:
					eStatus = MB_EX_SLAVE_BUSY;
					break;

					default:
					eStatus = MB_EX_SLAVE_DEVICE_FAILURE;
					break;
				}
			}
			else
			{
				// The response contains the function code, the starting
				// * address and the quantity of registers. We reuse the
				// * old values in the buffer because they are still valid.
				//
				*usLen = MB_PDU_FUNC_WRITE_MUL_BYTECNT_OFF;
			}
		}
		else
		{
			eStatus = MB_EX_ILLEGAL_DATA_VALUE;
		}
	}
	else
	{
		// Can't be a valid request because the length is incorrect.
		eStatus = MB_EX_ILLEGAL_DATA_VALUE;
	}
	return eStatus;
} // eMBException  eMBFuncWriteMultipleHoldingRegister( UCHAR * pucFrame, USHORT * usLen ) // команда 16

eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{
	//	define REG_COILS_START     200
	//	define REG_COILS_SIZE      16
	// static unsigned char        ucRegCoilsBuf    [REG_COILS_SIZE / 8];

	eMBErrorCode    eStatus = MB_ENOERR;
	short           iNCoils = ( short )usNCoils;
	unsigned short  usBitOffset;
	// PORTD |=(1<<2);
	/* Check if we have registers mapped at this block. */
	if( ( usAddress >= REG_COILS_START ) && ( usAddress + usNCoils <= REG_COILS_START + REG_COILS_SIZE ) )
	{
		usBitOffset = ( unsigned short )( usAddress - REG_COILS_START );
		switch ( eMode )
		{
			/* Read current values and pass to protocol stack. */
			case MB_REG_READ:
			while( iNCoils > 0 )
			{
				*pucRegBuffer++ =
				xMBUtilGetBits( ucRegCoilsBuf, usBitOffset,
				( unsigned char )( iNCoils >
				8 ? 8 :
				iNCoils ) );
				iNCoils -= 8;
				usBitOffset += 8;
			}
			break;

			/* Update current register values. */
			case MB_REG_WRITE:
			while( iNCoils > 0 )
			{
				xMBUtilSetBits( ucRegCoilsBuf, usBitOffset,
				( unsigned char )( iNCoils > 8 ? 8 : iNCoils ),
				*pucRegBuffer++ );
				iNCoils -= 8;
			}
			break;
		}

	}
	else
	{
		eStatus = MB_ENOREG;
	}
	return eStatus;
} // eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )

eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
	//(  2 ) //(0x02) Ч чтение значений из нескольких дискретных входов (Read Discrete Inputs).
	
	eMBErrorCode    eStatus = MB_ENOERR;
	int             iRegIndex;

	if( ( usAddress >= REG_INPUT_START ) && ( usAddress + usNDiscrete <= REG_INPUT_START + REG_INPUT_NREGS ) )
	{
		iRegIndex = ( int )( usAddress - usRegInputStart );
		while( usNDiscrete > 0 )
		{
			*pucRegBuffer++ =( unsigned char )( usRegInputBuf[iRegIndex] >> 8 );
			*pucRegBuffer++ =( unsigned char )( usRegInputBuf[iRegIndex] & 0xFF );
			iRegIndex++;
			usNDiscrete--;
		}
	}
	else
	{
		eStatus = MB_ENOREG;
	}

	return eStatus;
} // eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )

uint16_t write_new_motochas(uint16_t address_offset)
{
	 if (count_65500 >=65500) 
		{
			if(address_offset <496) // 512 смещение блока данных уже запрещено, последняя страница - 496
				{ 
					address_offset = address_offset + 16;  // и начинаем писать в новую страницу
					eeprom_write_word((uint16_t *)temp_zero, address_offset); // смещение адреса странички всегда пишется только в нулевой адрес
				}
			count_65500 =0;
		}
		else
		{ count_65500 ++;  }
		
	eeprom_write_word( (uint16_t *)(address_offset + 2), count_65500); // счетчик записей увеличиваем полюбому каждый заход

	// --------- count_sec_motochas_US
	if( count_sec_motochas_US >= 60)
	{
		count_sec_motochas_US=0;
		motochas_mm_US++;
		if (motochas_mm_US >=60)
		{
			motochas_mm_US =0;
			motochas_hh_US ++;
			eeprom_write_word((uint16_t *)(address_offset + 6), motochas_hh_US);
		}
		eeprom_write_word((uint16_t *)(address_offset + 4), motochas_mm_US);
	}
	
		// --------- count_sec_motochas_TEN
		if( count_sec_motochas_TEN >= 60)
		{
			count_sec_motochas_TEN=0;
			motochas_mm_TEN++;
			if (motochas_mm_TEN >=60)
			{
				motochas_mm_TEN =0;
				motochas_hh_TEN ++;
				eeprom_write_word((uint16_t *)(address_offset + 10), motochas_hh_TEN);
			}
			eeprom_write_word((uint16_t *)(address_offset + 8), motochas_mm_TEN);
		}
		
			// --------- count_sec_motochas_FS
			if( count_sec_motochas_FS >= 60)
			{
				count_sec_motochas_FS=0;
				motochas_mm_FS++;
				if (motochas_mm_FS >=60)
				{
					motochas_mm_FS =0;
					motochas_hh_FS ++;
					eeprom_write_word((uint16_t *)(address_offset + 14), motochas_hh_FS);
				}
				eeprom_write_word((uint16_t *)(address_offset + 12), motochas_mm_FS);
			}	
	 
	 // если создали новую страницу в памяти, выводим адрес этой страницы, чтобы он лежал в RAM до следующего перегруза
	return address_offset;
}