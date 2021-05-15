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


#define KPD_Size	4

static u8 PortNo;

void KPD_VidInit(u8 Copy_u8PortNo)
{
	PortNo = Copy_u8PortNo;
	
	DIO_VidSetPortDirection(PortNo,0x0f);
	DIO_VidSetPortValue(PortNo,0xff);
}

u8 KPD_BoolGetPressedKey(u8 *Ptr_u8Value)
{
	u8 FLAG = 0; 
	
	for(u8 COL=0; COL<KPD_Size; COL++)
	{
		DIO_VidSetPinValue(PortNo,COL,LOW);
		for(u8 ROW=0; ROW<KPD_Size; ROW++)
		{
			if(0 == DIO_U8GetPinValue(PortNo, ROW+4))
			{
				*Ptr_u8Value = (ROW*KPD_Size)+(KPD_Size-COL-1);
				FLAG = 1;
				while(0 == DIO_U8GetPinValue(PortNo, ROW+4));
				_delay_ms(2);
			}
		}
		DIO_VidSetPinValue(PortNo,COL,HIGH);
	}
	
	return FLAG;
}


