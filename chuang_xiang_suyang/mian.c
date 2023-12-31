#include <REGX52.H>
#include "Delay.h"
unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
static unsigned int cout=0;
static unsigned int time=24;
static unsigned char flag=1;//设置24秒倒计时标志位
static unsigned int sec=0;
static unsigned int fen=0;
static unsigned int fen_shi=0;
static unsigned int fen_ge=0;
static int jia_fen=0;
static int yi_fen=0;
void Nixie(unsigned char Location,Number)
{
	switch(Location)		//位码输出
	{
		case 1:P2_0=0;P2_1=0;P2_2=0;break;
		case 2:P2_0=1;P2_1=0;P2_2=0;break;
		case 3:P2_0=0;P2_1=1;P2_2=0;break;
		case 4:P2_0=1;P2_1=1;P2_2=0;break;
		case 5:P2_0=0;P2_1=0;P2_2=1;break;
		case 6:P2_0=1;P2_1=0;P2_2=1;break;
		case 7:P2_0=0;P2_1=1;P2_2=1;break;
		case 8:P2_0=1;P2_1=1;P2_2=1;break;
	}
	P0=NixieTable[Number];	//段码输出
}
void Timer1Init(void)
{
	TMOD=0x10;
	TL1 = 0x18;		//设置定时初值
	TH1 = 0xFC;		//设置定时初值
	TR1 = 1;		//定时器1开始计时
	ET1=1;
	EA=1;
	PT1=0;
}

//利用余晖效应扫描数码管
void xinshi()
{
		Nixie(1,jia_fen/10);
		Delay(5);
		Nixie(2,jia_fen%10);
		Delay(5);
		Nixie(3,yi_fen/10);
		Delay(5);
		Nixie(4,yi_fen%10);
		Delay(5);
		Nixie(5,fen_shi);
		Delay(5);
		Nixie(6,fen_ge);
		Delay(5);
		Nixie(7,sec/10);
		Delay(5);
		Nixie(8,sec%10);
		Delay(5);
}
void daojishi()
{
		Nixie(1,jia_fen/10);
		Delay(5);
		Nixie(2,jia_fen%10);
		Delay(5);
		Nixie(3,yi_fen/10);
		Delay(5);
		Nixie(4,yi_fen%10);
		Delay(5);
		Nixie(5,0);
		Delay(5);
		Nixie(6,0);
		Delay(5);
		Nixie(7,time/10);
		Delay(5);
		Nixie(8,time%10);
		Delay(5);
}
void button()
{
	char ci=0;
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
	if(P1_4==0)
	{
		EA=1;
		Delay(200);
		if(P1_4==0)
		{
			EA=0;
		}
		while(P1_4==0);
	}
}
/*中断计时，定时器跑满一次是1ms，跑1000次是1s，
跑一次1s*/
void jishi() interrupt 3 
{
		cout++;
		if(flag)
		{
		if(cout>=1000)
		{
			if(fen==1)
			{
				if(sec==36)
				{
					flag=0;
				}
			}
			sec++;
			cout=0;
			if(sec>=60)
			{
				fen++;
				sec=0;
				if(fen>=10)
				{
					fen_shi=fen/10;
					fen_ge=fen%10;
				}
				else
				{
					fen_ge=fen;
				}
			}
		}
		}
		else
		{
			if(cout>=1000)
			{
				time--;
				cout=0;
				if(time==0)
				{
					TR1=0;
				}
			}
		}
	TL1 = 0x18;		//设置定时初值
	TH1 = 0xFC;		//设置定时初值
}

void main()
{
		Timer1Init();
    while (flag)
    {
			button();
			xinshi();
    }
		while(1)
		{
			button();
			daojishi();
		}
}
