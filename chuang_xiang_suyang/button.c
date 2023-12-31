#include <REGX52.H>
#include "Delay.h"
static int jia_fen=0;
static int yi_fen=0;
void button(void)
{
	if(P1_0==0)
	{
		Delay(5);
		while(P1_0==0)
		{
		}
		jia_fen++;
	}
	if(P1_1==0)
	{
		Delay(5);
		while(P1_1==0)
		{
		}
		jia_fen--;
		
	}
	if(P1_2==0)
	{
		Delay(5);
		while(P1_2==0)
		{
		}
		yi_fen++;
		
	}
	if(P1_3==0)
	{
		Delay(5);
		while(P1_3==0)
		{
		}
		yi_fen--;
	}
}