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
	ADMUX &=~ (1<<REFS0); // ���������� ���������  AREF, Internal Vref turned off ,
	ADMUX &=~ (1<<REFS1); // ���������� ��������� AREF, Internal Vref turned off ,
	ADMUX &=~  (1<<ADLAR); // ��������� ��������� � ������� ����
	ADMUX &=~ (1<<MUX3); // ����� 0, 23 ����
	ADMUX &=~ (1<<MUX2); // ����� 0, 23 ����
	ADMUX &=~ (1<<MUX1); // ����� 0, 23 ����
	ADMUX &=~ (1<<MUX0); // ����� 0, 23 ����
	
	ADCSRA |=  (1<<ADPS0); //  �����������  ����������� 128
	ADCSRA |=  (1<<ADPS1); //  �����������  ����������� 128
	ADCSRA |=  (1<<ADPS2); //  �����������  ����������� 128
	ADCSRA &=~ (1<<ADIE); //  ����������   �?�
	ADCSRA |=  (1<<ADATE); //  ����������� ��������������
	ADCSRA |=  (1<<ADSC); //  Start ��������������
	ADCSRA |=  (1<<ADEN); //  enable ��������������
	
	ADCSRB &=~ (1<<ADTS0); // ����� ������������ �������������
	ADCSRB &=~ (1<<ADTS1); // ����� ������������ �������������
	ADCSRB &=~ (1<<ADTS2); // ����� ������������ �������������
	ADCSRB &=~ (1<<ACME); // �� ����� ����� �� ����������� �����������
	return;
}

void ADC_init_NTC(void)
{
//  ���� ������������ ����� �� NTC, �� ��� ��������� �������� �� ���� 21 ���� �������, ����������� ��������
	ADMUX |= (1<<REFS0); // AVCC � ������� ������������� �� ������  AREF pin
	ADMUX &=~ (1<<REFS1); // AVCC with external capacitor at AREF pin
	ADMUX &=~  (1<<ADLAR); // ��������� ��������� � ������� ����
	ADMUX &=~ (1<<MUX3); // ����� 0, 23 ����
	ADMUX &=~ (1<<MUX2); // ����� 0, 23 ����
	ADMUX &=~ (1<<MUX1); // ����� 0, 23 ����
	ADMUX &=~ (1<<MUX0); // ����� 0, 23 ����
	
	ADCSRA |=  (1<<ADPS0); //  �����������  ����������� 128
	ADCSRA |=  (1<<ADPS1); //  �����������  ����������� 128
	ADCSRA |=  (1<<ADPS2); //  �����������  ����������� 128
	ADCSRA &=~ (1<<ADIE); //  ����������   �?�
	ADCSRA |=  (1<<ADATE); //  ����������� ��������������
	ADCSRA |=  (1<<ADSC); //  Start ��������������
	ADCSRA |=  (1<<ADEN); //  enable ��������������
	
	ADCSRB &=~ (1<<ADTS0); // ����� ������������ �������������
	ADCSRB &=~ (1<<ADTS1); // ����� ������������ �������������
	ADCSRB &=~ (1<<ADTS2); // ����� ������������ �������������
	ADCSRB &=~ (1<<ACME); // �� ����� ����� �� ����������� �����������
	return;
}

uint16_t  zamer_ADC_tmprt_Pt1000(float Up_mv, float Aref_mv, float R_om)
{
	//#define PT1000_0_GRAD	1000 // ������������� ������������ ��� ����������� 0 �������� ?�����
	//#define NAKLON_OM_GRAD	3.792 // ������ �������������� ������������ ������������, ����� �� � ���� ��� ����� ����� �� 1 ������
	uint16_t temperatura_tekuzh_x10_plus10=0;
	//float Aref_mv = AREF_MV				; // ����� ��������� �� 21 ����
	//float R_om = R_OM					; // ����� �� �������� �������� ������������ �� +5
	//float Up_mv = UP_MV					; // ��������� ������ mega328, ���������
	float Pt_om_0grad = PT1000_0_GRAD	; // ������������� ������������ ��� ����������� 0 �������� ?�����
	float naklon = NAKLON_OM_GRAD		; // ������ �������������� ������������ ������������, ����� �� � ���� ��� ����� ����� �� 1 ������
	uint16_t Zamer_ADC = (ADCL | (ADCH<<8));
	
	float Zamer_f = (float)Zamer_ADC;
	
	// ������� ���� ��������� ������� ADCdata  temperatura_tekuzh
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
	//float R_om = R_OM					; // ����� �� �������� �������� ������������ �� +5
	uint16_t R_izm_om; // ��������� ������ ������������� NTC
	uint16_t Zamer_ADC = (ADCL | (ADCH<<8));
	float Zamer_f = (float)Zamer_ADC;
	
	// ������� ���� ��������� ������� ADCdata  temperatura_tekuzh
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
				// �������� ����� �� �������  table_NTC_Om[141]
				for(int it=1; it<141; it++) //������ ���� � 0, �� ��� ������� ������� ����� �������� ������� ������� [it-1]
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