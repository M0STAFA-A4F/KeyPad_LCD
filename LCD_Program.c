#ifndef _STD_TYPES_h_
#include "STD_TYPES.h"
#endif

#ifndef _DIO_Interface_h_
#include "DIO_Interface.h"
#endif

#ifndef _util_delay_h_
#define F_CPU 8000000UL
#include <util/delay.h>
#endif


static u8 ContPortNo;
static u8 DataPortNo;

static u8 RS;
static u8 RW;
static u8 E;


void LCD_VidSendData(u8 Copy_u8Data)
{
	DIO_VidSetPinValue(ContPortNo,RS,HIGH);	// RS = 1 to send data
	DIO_VidSetPinValue(ContPortNo,RW,LOW);	// RW = 0 to write data
	DIO_VidSetPortValue(DataPortNo,Copy_u8Data);	// send data
	// enable in bit 2
	DIO_VidSetPinValue(ContPortNo,E,HIGH);
	_delay_ms(1);
	DIO_VidSetPinValue(ContPortNo,E,LOW);
	_delay_ms(1);
}

void LCD_VidSendCommand(u8 Copy_u8Command)
{
	DIO_VidSetPinValue(ContPortNo,RS,LOW);	// RS = 0 to send command
	DIO_VidSetPinValue(ContPortNo,RW,LOW);	// RW = 0 to write data
	DIO_VidSetPortValue(DataPortNo,Copy_u8Command);	// send data
	// enable in bit 2
	DIO_VidSetPinValue(ContPortNo,E,HIGH);
	_delay_ms(1);
	DIO_VidSetPinValue(ContPortNo,E,LOW);
	_delay_ms(1);
}

void LCD_VidInit(u8 Copy_u8DataPortNo, u8 Copy_u8ContPortNo, u8 Copy_u8RS, u8 Copy_u8RW, u8 Copy_u8E)
{
	DataPortNo = Copy_u8DataPortNo;
	ContPortNo = Copy_u8ContPortNo;
	RS = Copy_u8RS;
	RW = Copy_u8RW;
	E = Copy_u8E;
	
	DIO_VidSetPortDirection(DataPortNo,0xff);
	DIO_VidSetPinDirection(ContPortNo,RS,OUTPUT);
	DIO_VidSetPinDirection(ContPortNo,RW,OUTPUT);
	DIO_VidSetPinDirection(ContPortNo,E,OUTPUT);
	
	_delay_ms(40);
	LCD_VidSendCommand(0b00111000);
	_delay_ms(1);
	LCD_VidSendCommand(0b00001100);
	_delay_ms(1);
	LCD_VidSendCommand(0b00000001);
	_delay_ms(2);
	LCD_VidSendCommand(0b00000110);
}

void LCD_VidSendString(u8 *u8String)
{
	for(u8 i=0; u8String[i]!='\0'; i++)
	{
		LCD_VidSendData(u8String[i]);
	}
}

void LCD_VidSendNumber(s32 Copy_s32Number)
{
	u8 Digits[20];
	u8 DigitsSize = 0;

	if(Copy_s32Number >= 0)
	{
		do{
			Digits[DigitsSize] = (Copy_s32Number%10)+'0';
			DigitsSize++;
			Copy_s32Number /= 10;
		}while(Copy_s32Number > 0);

		for(s8 i=DigitsSize-1; i>=0; i--)
		{
			LCD_VidSendData(Digits[i]);
		}
	}
	else
	{
		Copy_s32Number *= -1;
		
		do{
			Digits[DigitsSize] = (Copy_s32Number%10)+'0';
			DigitsSize++;
			Copy_s32Number /= 10;
		}while(Copy_s32Number > 0);

		Digits[DigitsSize] = '-';
		DigitsSize++;

		for(s8 i=DigitsSize-1; i>=0; i--)
		{
			LCD_VidSendData(Digits[i]);
		}
	}
}

void LCD_vidSetPosition(u8 Copy_u8Row, u8 Copy_u8Col)
{
	if(0 == Copy_u8Row)
	{
		LCD_VidSendCommand(128+Copy_u8Col);
	}
	else if(1 == Copy_u8Row)
	{
		LCD_VidSendCommand(128+64+Copy_u8Col);
	}
}













