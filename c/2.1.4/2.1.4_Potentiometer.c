/**********************************************************************
* Filename    : 2.1.4_Potentiometer.c
* Description : 
* Author      : Robot
* E-mail      : support@sunfounder.com
* website     : www.sunfounder.com
* Update      : Cavon    2016/07/01
**********************************************************************/

#include <stdio.h>
#include <wiringPi.h>
#include <pcf8591.h>

#define PCF       120

int main (void)
{
	printf("\n");
	printf("\n");
	printf("========================================\n");
	printf("|             Potentiometer            |\n");
	printf("|    ------------------------------    |\n");
	printf("|           SDA,SCL connect to         |\n");
	printf("|   the corresponding pin of PCF8591   |\n");
	printf("|                                      |\n");
	printf("| Make potentiometer to contral a led  |\n");
	printf("|                                      |\n");
	printf("|                            SunFounder|\n");
	printf("========================================\n");
	printf("\n");
	printf("\n");
	int value ;
	wiringPiSetup () ;
	// Setup pcf8591 on base pin 120, and address 0x48
	pcf8591Setup (PCF, 0x48) ;
	while(1) // loop forever
	{
		value = analogRead  (PCF + 0) ;
		printf("Value: %d\n", value);
		analogWrite (PCF + 0, value) ;
		delay (200) ;
	}
	return 0 ;
}
