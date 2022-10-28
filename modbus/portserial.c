/*
 * FreeModbus Libary: ATMega168 Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *   - Initial version and ATmega168 support
 * Modfications Copyright (C) 2006 Tran Minh Hoang:
 *   - ATmega8, ATmega16, ATmega32 support
 *   - RS485 support for DS75176
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: portserial.c,v 1.6 2006/09/17 16:45:53 wolti Exp $
 */

#include <avr/io.h>
#include <avr/interrupt.h>
//#include <avr/signal.h>

#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "../modbus/mb.h"
#include "../modbus/mbport.h"

#define UART_BAUD_RATE          9600
#define F_CPU 16000000UL
#define UART_BAUD_CALC(UART_BAUD_RATE, F_CPU)   ( ( F_CPU ) / ( ( UART_BAUD_RATE ) * 16UL ) - 1 )
#define _BV(bit)  (1 << (bit))
#define UART_UCSRB  UCSR0B

//
void
vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
//#ifdef RTS_ENABLE
    UCSR0B |= _BV( TXEN0 ) | _BV(TXCIE0);
//#else
//    UCSRB |= _BV( TXEN );
//#endif

    if( xRxEnable )
    {
        UCSR0B |= _BV( RXEN0 ) | _BV( RXCIE0 );
    }
    else
    {
        UCSR0B &= ~( _BV( RXEN0 ) | _BV( RXCIE0 ) );
    }

    if( xTxEnable )
    {
        UCSR0B |= _BV( TXEN0 ) | _BV( UDRE0 );
//#ifdef RTS_ENABLE
        RTS_HIGH;
//#endif
    }
    else
    {
        UCSR0B &= ~( _BV( UDRE0 ) );
    }
}

BOOL
xMBPortSerialInit( UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
//     UCHAR ucUCSRC = 0;
// 
//     /* prevent compiler warning. */
//     (void)ucPORT;
// 	
//     //UBRR = UART_BAUD_CALC( ulBaudRate, F_CPU );
// 		// настроить UART
// 			UCSR0C|=  (1<<UCSZ01) | (1<<UCSZ00);  //  8бит  данных
// 			UCSR0A |= (1<<U2X0);  // это будет  асинхронный  UART
// 			UBRR0L=103;          // 2значени€,  определ€ют 19200  при 16 ћ√ц
// 			PORTC &= ~(1<<3); // пишем 0 дл€ ћј’485, чтбы его перевести в прием
// 			UCSR0B |= (1<<RXEN0);// разрешаем прием
// 	
//     switch ( eParity )
//     {
//         case MB_PAR_EVEN:
//             ucUCSRC |= _BV( UPM01 );
//             break;
//         case MB_PAR_ODD:
//             ucUCSRC |= _BV( UPM01 ) | _BV( UPM00 );
//             break;
//         case MB_PAR_NONE:
//             break;
//     }
// 	
// 	ucUCSRC |= _BV( UCSZ00 ) | _BV( UCSZ01 );  // 8 bit i NO variant
// /*    switch ( ucDataBits )
//     {
//         case 8:
//             ucUCSRC |= _BV( UCSZ0 ) | _BV( UCSZ1 );
//             break;
//         case 7:
//             ucUCSRC |= _BV( UCSZ1 );
//             break;
//     }*/
// //UCSRC = _BV( URSEL ) | ucUCSRC; //#elif defined (__AVR_ATmega8__)
// /*
// #if defined (__AVR_ATmega168__)
//     UCSRC |= ucUCSRC;
// #elif defined (__AVR_ATmega169__)
//     UCSRC |= ucUCSRC;
// #elif defined (__AVR_ATmega8__)
//     
// #elif defined (__AVR_ATmega16__)
//     UCSRC = _BV( URSEL ) | ucUCSRC;
// #elif defined (__AVR_ATmega32__)
//     UCSRC = _BV( URSEL ) | ucUCSRC;
// #elif defined (__AVR_ATmega128__)
//     UCSRC |= ucUCSRC;
// #endif
// */
//     vMBPortSerialEnable( FALSE, FALSE );
// 
// //#ifdef RTS_ENABLE
//     RTS_INIT;
//#endif
    return TRUE;
}

BOOL
xMBPortSerialPutByte( CHAR ucByte )
{
    UDR0 = ucByte;
    return TRUE;
}

// BOOL
// xMBPortSerialGetByte( CHAR * pucByte )
// {
//     *pucByte = UDR0;
//     return TRUE;
// }

//SIGNAL( SIG_USART_DATA )
//{
//    pxMBFrameCBTransmitterEmpty(  );
//}

//SIGNAL( SIG_USART_RECV )
//{
//    pxMBFrameCBByteReceived(  );
//}

//#ifdef RTS_ENABLE
//SIGNAL( SIG_UART_TRANS )
//{
//    RTS_LOW;
//}
//#endif

