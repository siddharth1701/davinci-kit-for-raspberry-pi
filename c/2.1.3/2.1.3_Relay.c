/**********************************************************************
* Filename 		: 2.1.3_Relay.c
* Description 	: Make a relay to contral led blinking
* Author 		: Dream
* E-mail 		: support@sunfounder.com
* Website 		: www.sunfounder.com
* Update 		: Dream    <2016-07-26>
**********************************************************************/
#include <wiringPi.h>
#include <stdio.h>

#define RelayPin 0

int main(void){
	if(wiringPiSetup() == -1){ //when initialize wiring failed, print message to screen
		printf("setup wiringPi failed !");
		return 1; 
	}
	
	pinMode(RelayPin, OUTPUT);   //set #17(GPIO0) output

	printf("\n");
	printf("\n");
	printf("========================================\n");
	printf("|                 Relay                |\n");
	printf("|    ------------------------------    |\n");
	printf("|   #17 connect to relay's control pin |\n");
	printf("| led connect to relay's NormalOpen pin|\n");
	printf("|  5v connect to relay's com pin       |\n");
	printf("|                                      |\n");
	printf("|      Make relay to contral a led     |\n");
	printf("|                                      |\n");
	printf("|                            SunFounder|\n");
	printf("========================================\n");
	printf("\n");
	printf("\n");

	while(1){
		// Tick
		printf("Relay Open......\n");
		digitalWrite(RelayPin, LOW);
		delay(1000);
		// Tock
		printf("......Relay Close\n");
		digitalWrite(RelayPin, HIGH);
		delay(1000);
	}

	return 0;
}


