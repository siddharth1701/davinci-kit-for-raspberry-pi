/**********************************************************************
* Filename    : 2.2.2_Thermometer.c
* Description : Read temperature
* Author      : Robot
* E-mail      : support@sunfounder.com
* website     : www.sunfounder.com
* Update      : Cavon    2016/07/01
**********************************************************************/
#include <stdio.h>
#include <wiringPi.h>
#include <pcf8591.h>
#include <math.h>

#define		PCF     120

int main()
{
	unsigned char analogVal;
	double Vr, Rt, temp;
	printf("\n");
	printf("\n");
	printf("========================================\n");
	printf("|               Thermistor             |\n");
	printf("|    ------------------------------    |\n");
	printf("|           SDA,SCL connect to         |\n");
	printf("|   the corresponding pin of PCF8591   |\n");
	printf("|                                      |\n");	
	printf("| Use thermistor to detect temperature |\n");
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

	while(1) // loop forever
	{
		printf("loop");
		analogVal = analogRead(PCF + 0);
		Vr = 5 * (double)(analogVal) / 255;
		Rt = 10000 * (double)(Vr) / (5 - (double)(Vr));
		temp = 1 / (((log(Rt/10000)) / 3950)+(1 / (273.15 + 25)));
		temp = temp - 273.15;
		printf("Current temperature : %lf\n", temp);

		delay (200);
	}
	return 0;
}