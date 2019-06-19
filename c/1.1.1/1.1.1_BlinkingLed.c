/**********************************************************************
* Filename    : 1.1.1_BlinkingLed.c
* Description : Make an led blinking.
* Author      : Robot
* E-mail      : support@sunfounder.com
* website     : www.sunfounder.com
* Update      : Cavon    2016/07/01
**********************************************************************/
#include <wiringPi.h>
#include <stdio.h>
// Standard I/O library. The pintf function used for printing the data displayed on the screen is realized by this library.  There are many other performance functions for you to explore. 

#define LedPin		0
// Pin B17 of the T_Extension Board is corresponding to the pin0 in wiringPi, namely, GPIO 0 of the raspberry Pi. Assign GPIO 0 to LedPin, LedPin represents GPIO 0 in the code later. 

int main(void)
{
	// When initialize wiring failed, print message to screen
	if(wiringPiSetup() == -1){
		printf("setup wiringPi failed !");
		return 1; 
	}
	
	pinMode(LedPin, OUTPUT);// Set LedPin as output to write value to it. 

	printf("\n");
	printf("\n");
	printf("========================================\n");
	printf("|              Blink LED               |\n");
	printf("|    ------------------------------    |\n");
	printf("|           LED connect to #17         |\n");
	printf("|                                      |\n");
	printf("|        LED will Blink at 500ms       |\n");
	printf("|                                      |\n");
	printf("|                            SunFounder|\n");
	printf("========================================");
	printf("\n");
	printf("\n");
	
	while(1){
		// LED on
		digitalWrite(LedPin, LOW);
		// Set GPIO0 as 0V (low level). Since the cathode of LED is connected to GPIO0, thus the LED will light up if GPIO0 is set low. On the contrary, set GPIO0 as high level, digitalWrite (LedPin, HIGH): LED will go out. 
		printf("...LED on\n");
		delay(500);
		// LED off
		digitalWrite(LedPin, HIGH);
		printf("LED off...\n");
		delay(500);
	}

	return 0;
}

