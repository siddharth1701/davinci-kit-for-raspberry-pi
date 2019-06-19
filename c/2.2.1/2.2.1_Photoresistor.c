/**********************************************************************
* Filename    : 2.2.1_Photoresistor.c
* Description : Photoresistor control LED
* Author      : Robot
* E-mail      : support@sunfounder.com
* website     : www.sunfounder.com
* Update      : Cavon    2016/07/01
**********************************************************************/
#include <stdio.h>
#include <wiringPi.h>
#include <pcf8591.h>
#include <math.h>
#include <softPwm.h>

#define		PCF     120
#define		ledPin	0
int main()
{
	int analogVal;
	printf("\n");
	printf("\n");
	printf("========================================\n");
	printf("|             Photoresistor            |\n");
	printf("|    ------------------------------    |\n");
	printf("|           SDA,SCL connect to         |\n");
	printf("|   the corresponding pin of PCF8591   |\n");
	printf("|           #17 connect to LED         |\n");
	printf("|                                      |\n");	
	printf("| Make Photoresistor to contral a led  |\n");
	printf("|                                      |\n");
	printf("|                            SunFounder|\n");
	printf("========================================\n");
	printf("\n");
	printf("\n");	
	if(wiringPiSetup() == -1){
		printf("setup wiringPi failed !");
		return 1;
	}
	// Setup pcf8591 on base pin 120, and address 0x48
	pcf8591Setup(PCF, 0x48);
	softPwmCreate(ledPin,0,100);
	while(1) // loop forever
	{
		analogVal = analogRead(PCF + 0);
		softPwmWrite(ledPin,analogVal*100/255);		
		printf("Value: %d\n", analogVal);

		delay (200);
	}
	return 0;
}