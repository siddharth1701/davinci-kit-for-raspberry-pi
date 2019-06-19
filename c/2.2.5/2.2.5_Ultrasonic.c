/**********************************************************************
* Filename    : 2.2.5_Ultrasonic.c
* Description : Get distance from UltrasonicRanging
* Author      : Robot
* E-mail      : support@sunfounder.com
* website     : www.sunfounder.com
* Update      : Cavon    2016/07/01
**********************************************************************/
#include <wiringPi.h>
#include <stdio.h>
#include <sys/time.h>

#define Trig    4
#define Echo    5

void ultraInit(void)
{
	pinMode(Echo, INPUT);
	pinMode(Trig, OUTPUT);
}

float disMeasure(void)
{
	struct timeval tv1;
	struct timeval tv2;
	long time1, time2;
    float dis;

	digitalWrite(Trig, LOW);
	delayMicroseconds(2);

	digitalWrite(Trig, HIGH);
	delayMicroseconds(10);     
	digitalWrite(Trig, LOW);
								
	while(!(digitalRead(Echo) == 1));	
	gettimeofday(&tv1, NULL);           

	while(!(digitalRead(Echo) == 0));   
	gettimeofday(&tv2, NULL);           

	time1 = tv1.tv_sec * 1000000 + tv1.tv_usec;   
	time2  = tv2.tv_sec * 1000000 + tv2.tv_usec;

	dis = (float)(time2 - time1) / 1000000 * 34000 / 2; 

	return dis;
}

int main(void)
{
	float dis;
	printf("\n");
	printf("\n");
	printf("========================================\n");
	printf("|              Ultrasonic              |\n");
	printf("|    ------------------------------    |\n");
	printf("|         Trig connect to #23          |\n");
	printf("|         Echo connect to #24          |\n");
	printf("|                                      |\n");
	printf("|   Use ultrasonic to detect distance  |\n");
	printf("|                                      |\n");
	printf("|                            SunFounder|\n");
	printf("========================================\n");
	printf("\n");
	printf("\n");
	if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !");
		return 1; 
	}

	ultraInit();
	
	while(1){
		dis = disMeasure();
		printf("%0.2f cm\n\n",dis);
		delay(300);
	}

	return 0;
}