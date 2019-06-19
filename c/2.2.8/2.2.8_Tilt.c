/**********************************************************************
* Filename    : 2.2.8_Tilt.c
* Description : 
* Author      : Robot
* E-mail      : support@sunfounder.com
* website     : www.sunfounder.com
* Update      : Cavon    2016/07/01
**********************************************************************/

#include <wiringPi.h>
#include <stdio.h>

#define TiltPin		0
#define Gpin		2
#define Rpin		3

void LED(char* color)
{
	pinMode(Gpin, OUTPUT);
	pinMode(Rpin, OUTPUT);
	if (color == "RED")
	{
		digitalWrite(Rpin, HIGH);
		digitalWrite(Gpin, LOW);
	}
	else if (color == "GREEN")
	{
		digitalWrite(Rpin, LOW);
		digitalWrite(Gpin, HIGH);
	}
	else
		printf("LED Error");
}

int main(void)
{
	printf("\n");
	printf("\n");
	printf("========================================\n");
	printf("|           Tilt control LED           |\n");
	printf("|    ------------------------------    |\n");
	printf("|         Tilt connect to #17          |\n");
	printf("|       Green LED connect to #27       |\n");
	printf("|         Red LED connect to #22       |\n");
	printf("|                                      |\n");
	printf("|       User Tilt to control LED       |\n");
	printf("|                                      |\n");
	printf("|                            SunFounder|\n");
	printf("========================================\n");
	printf("\n");
	printf("\n");
	if(wiringPiSetup() == -1){ //when initialize wiring failed,print message to screen
		printf("setup wiringPi failed !");
		return 1; 
	}

	pinMode(TiltPin, INPUT);
	LED("GREEN");
	
	while(1){
		if(0 == digitalRead(TiltPin)){
			delay(10);
			if(0 == digitalRead(TiltPin)){
				LED("RED");
				printf("Tilt!\n");
			}
		}
		else if(1 == digitalRead(TiltPin)){
			delay(10);
			if(1 == digitalRead(TiltPin)){
				LED("GREEN");
			}
		}
	}
	return 0;
}
