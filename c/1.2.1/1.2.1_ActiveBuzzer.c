/**********************************************************************
* Filename    : 1.2.1_ActiveBuzzer.c
* Description : Make a buzzer beep.
* Author      : Robot
* E-mail      : support@sunfounder.com
* website     : www.sunfounder.com
* Update      : Cavon    2016/07/01
**********************************************************************/
#include <wiringPi.h>
#include <stdio.h>

#define BeepPin 0

int main(void){
	if(wiringPiSetup() == -1){ //when initialize wiring failed, print message to screen
		printf("setup wiringPi failed !");
		return 1; 
	}
	
	pinMode(BeepPin, OUTPUT);   //set GPIO0 output

	printf("\n");
	printf("\n");
	printf("========================================\n");
	printf("|            Active Buzzer             |\n");
	printf("|    ------------------------------    |\n");
	printf("|        Buzzer connect to #17         |\n");
	printf("|                                      |\n");
	printf("|            Make Buzzer beep          |\n");
	printf("|                                      |\n");
	printf("|                            SunFounder|\n");
	printf("========================================\n");
	printf("\n");
	printf("\n");

	while(1){
		//beep on
		printf("Buzzer on\n");
		digitalWrite(BeepPin, LOW);
		delay(100);
		printf("Buzzer off\n");
		//beep off
		digitalWrite(BeepPin, HIGH);
		delay(100);
	}

	return 0;
}

