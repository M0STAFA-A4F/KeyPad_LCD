#define F_CPU 8000000UL
#include <util/delay.h>
#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "KPD_Interface.h"


int main(void)
{
	LCD_VidInit(PORTC,PORTA,2,1,0);

	u8 name[] = "mostafa";
	LCD_VidSendString(name);
	LCD_VidSendNumber(-123);

	KPD_VidInit(PORTD);

	u8 x;

	while(1)
	{
		if(KPD_BoolGetPressedKey(&x))
		{
			LCD_VidSendNumber(x);
		}
	}

	return 0;
}
