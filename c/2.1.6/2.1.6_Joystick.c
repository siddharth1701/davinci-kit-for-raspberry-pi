/**********************************************************************
* Filename    : 2.1.6_Joystick.c
* Description : Read Joystick
* Author      : Robot
* E-mail      : support@sunfounder.com
* website     : www.sunfounder.com
* Update      : Cavon    2016/07/01
**********************************************************************/
#include <stdio.h>
#include <wiringPi.h>
#include <pcf8591.h>

#define PCF       120
#define uchar	unsigned char

int AIN0 = PCF + 0;
int AIN1 = PCF + 1;


int direction(){
	int x, y, b;
	int tmp;
	x = analogRead(AIN1);
	y = analogRead(AIN0);
	b = digitalRead(0);
	//printf("%d , %d , %d \n",x,y,b);
	if (y <= 5)
		{tmp = 1;		// up
		}
	if (y >= 250)
		{tmp = 2;		// down
		}
	if (x <= 5)
		{tmp = 3;		// left
		}
	if (x >= 250)
		{tmp = 4;		// right
		}
	if (b == 0)
		{tmp = 5;		// button preesd
		}
	if (x-125<60 && x-125>-60 && y-125<60 && y-125>-60 && b == 1)
		{tmp = 0;		// home position
		}
	return tmp;
}

int main (void)
{
	int tmp;
	int status = 0;
	if(wiringPiSetup() == -1){ //when initialize wiring failed,print message to screen
    printf("setup wiringPi failed !");
    return 1; 
    }
	pinMode(0,INPUT);
	pullUpDnControl(0,PUD_UP);

	// Setup pcf8591 on base pin 120, and address 0x48
	pcf8591Setup (PCF, 0x48);
    printf("\n");
	printf("\n");
	printf("========================================\n");
	printf("|               Joystick               |\n");
	printf("|    ------------------------------    |\n");
	printf("|           SDA,SCL connect to         |\n");
	printf("|   the corresponding pin of PCF8591   |\n");
	printf("|                                      |\n");
	printf("|            Use Joystick input        |\n");
	printf("|                                      |\n");
	printf("|                            SunFounder|\n");
	printf("========================================\n");
	printf("\n");
	printf("\n");
	while(1) // loop forever
	{
		tmp = direction();
		if (tmp != status)
		{
			switch (tmp)
			{
				case 1:printf("up \n");break;
				case 2:printf("down \n");break;
				case 3:printf("left \n");break;
				case 4:printf("right \n");break;
				case 5:printf("presssd \n");break;
				case 0:printf("home \n");break;
			}
			status = tmp;
		}
	}
	return 0 ;
}