/*
 * fun_ADC.cpp
 *
 *
 * Created: 18.03.2022 9:20:32
 *  Author: durov_av
 */ 
#include "fun_ADC.h"

extern bool infa_err_td ;
extern uint16_t count_infa_err_td;

void ADC_init_Pt1000(void)
{
	//  ==1 Pt1000_<<>>_2k,
	ADMUX &=~ (1<<REFS0); // ѕодключено напр¤жение  AREF, Internal Vref turned off ,
	ADMUX &=~ (1<<REFS1); // ѕодключено напр¤жение AREF, Internal Vref turned off ,
	ADMUX &=~  (1<<ADLAR); // прижимать результат к нижнему краю
	ADMUX &=~ (1<<MUX3); // канал 0, 23 нога
	ADMUX &=~ (1<<MUX2); // канал 0, 23 нога
	ADMUX &=~ (1<<MUX1); // канал 0, 23 нога
	ADMUX &=~ (1<<MUX0); // канал 0, 23 нога
	
	ADCSRA |=  (1<<ADPS0); //  коэффициент  предделител¤ 128
	ADCSRA |=  (1<<ADPS1); //  коэффициент  предделител¤ 128
	ADCSRA |=  (1<<ADPS2); //  коэффициент  предделител¤ 128
	ADCSRA &=~ (1<<ADIE); //  прерывание   Ќ?“
	ADCSRA |=  (1<<ADATE); //  непрерывное преобразование
	ADCSRA |=  (1<<ADSC); //  Start преобразование
	ADCSRA |=  (1<<ADEN); //  enable преобразование
	
	ADCSRB &=~ (1<<ADTS0); // режим непрерывного преобразовани¤
	ADCSRB &=~ (1<<ADTS1); // режим непрерывного преобразовани¤
	ADCSRB &=~ (1<<ADTS2); // режим непрерывного преобразовани¤
	ADCSRB &=~ (1<<ACME); // не нужен старт по аналоговому компаратору
	return;
}

void ADC_init_NTC(void)
{
//  если использовать замер по NTC, то два резистора делитель на ногу 21 надо отпаять, конденсатор оставить
	ADMUX |= (1<<REFS0); // AVCC с внешним конденсатором на выводе  AREF pin
	ADMUX &=~ (1<<REFS1); // AVCC with external capacitor at AREF pin
	ADMUX &=~  (1<<ADLAR); // прижимать результат к нижнему краю
	ADMUX &=~ (1<<MUX3); // канал 0, 23 нога
	ADMUX &=~ (1<<MUX2); // канал 0, 23 нога
	ADMUX &=~ (1<<MUX1); // канал 0, 23 нога
	ADMUX &=~ (1<<MUX0); // канал 0, 23 нога
	
	ADCSRA |=  (1<<ADPS0); //  коэффициент  предделител¤ 128
	ADCSRA |=  (1<<ADPS1); //  коэффициент  предделител¤ 128
	ADCSRA |=  (1<<ADPS2); //  коэффициент  предделител¤ 128
	ADCSRA &=~ (1<<ADIE); //  прерывание   Ќ?“
	ADCSRA |=  (1<<ADATE); //  непрерывное преобразование
	ADCSRA |=  (1<<ADSC); //  Start преобразование
	ADCSRA |=  (1<<ADEN); //  enable преобразование
	
	ADCSRB &=~ (1<<ADTS0); // режим непрерывного преобразовани¤
	ADCSRB &=~ (1<<ADTS1); // режим непрерывного преобразовани¤
	ADCSRB &=~ (1<<ADTS2); // режим непрерывного преобразовани¤
	ADCSRB &=~ (1<<ACME); // не нужен старт по аналоговому компаратору
	return;
}

uint16_t  zamer_ADC_tmprt_Pt1000(float Up_mv, float Aref_mv, float R_om)
{
	//#define PT1000_0_GRAD	1000 // сопротивление термодатчика при температуре 0 градусов ?ельси¤
	//#define NAKLON_OM_GRAD	3.792 // наклон характеристики сопротивлени¤ термодатчика, скока ом в плюс при росте тмпрт на 1 градус
	uint16_t temperatura_tekuzh_x10_plus10=0;
	//float Aref_mv = AREF_MV				; // скока миливольт на 21 ноге
	//float R_om = R_OM					; // скока ќм резистор подвески термодатчика на +5
	//float Up_mv = UP_MV					; // напр¤жение питани¤ mega328, миливольт
	float Pt_om_0grad = PT1000_0_GRAD	; // сопротивление термодатчика при температуре 0 градусов ?ельси¤
	float naklon = NAKLON_OM_GRAD		; // наклон характеристики сопротивлени¤ термодатчика, скока ом в плюс при росте тмпрт на 1 градус
	uint16_t Zamer_ADC = (ADCL | (ADCH<<8));
	
	float Zamer_f = (float)Zamer_ADC;
	
	// сначала надо проверить пределы ADCdata  temperatura_tekuzh
	infa_err_td =false;
	if(((Zamer_ADC < 685 ) | (Zamer_ADC > 1000) ) )
	{
		count_infa_err_td ++;
		temperatura_tekuzh_x10_plus10 = 1900;
	}
	else
	{
		temperatura_tekuzh_x10_plus10 = 100 + (uint16_t) (10*  ( (Aref_mv*R_om*Zamer_f/(1024*Up_mv - Aref_mv*Zamer_f)) - Pt_om_0grad ) / naklon );
		count_infa_err_td=0;
	}
	
	if (count_infa_err_td >20)
	{
		count_infa_err_td=20;
		infa_err_td =true;
	}
	
	
	return temperatura_tekuzh_x10_plus10;
}

uint16_t  zamer_ADC_tmprt_NTC(float R_om)
{
	uint16_t temperatura_tekuzh_x10_plus10=0;
	//float R_om = R_OM					; // скока ќм резистор подвески термодатчика на +5
	uint16_t R_izm_om; // разультат замера сопротивления NTC
	uint16_t Zamer_ADC = (ADCL | (ADCH<<8));
	float Zamer_f = (float)Zamer_ADC;
	
	// сначала надо проверить пределы ADCdata  temperatura_tekuzh
	infa_err_td =false;
	if(((Zamer_ADC < 130 ) | (Zamer_ADC > 990) ) )
		{ 
			temperatura_tekuzh_x10_plus10 = 1900; 
			//infa_err_td =true;
			count_infa_err_td ++;
		}
	else
		{
			// infa_err_td =false;
			count_infa_err_td=0;
			R_izm_om = (uint16_t) ( R_om*Zamer_f / (1024 - Zamer_f));
				// Двоичный поиск по таблице  table_NTC_Om[141]
				for(int it=1; it<141; it++) //массив идет с 0, но для точного деления нужно значение нижнего индекса [it-1]
				{
					if (R_izm_om < table_NTC_Om[it])
						{ temperatura_tekuzh_x10_plus10= it * 10; }
					else
						{
							temperatura_tekuzh_x10_plus10 = (table_NTC_Om[it-1] - R_izm_om) *10 / (table_NTC_Om[it-1] - table_NTC_Om[it])   + (it-1)*10;
							it=142;
						}
				}
		}
		
		if (count_infa_err_td >20)
		{
			count_infa_err_td=20;
			infa_err_td =true;
		}
		
	return temperatura_tekuzh_x10_plus10;
}