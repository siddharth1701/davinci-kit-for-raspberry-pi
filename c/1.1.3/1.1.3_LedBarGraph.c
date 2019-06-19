/**********************************************************************
* Filename    : 1.1.3_LedBarGraph.c
* Description : Make an led bar graph work.
* Author      : Robot
* E-mail      : support@sunfounder.com
* website     : www.sunfounder.com
* Update      : Cavon    2016/07/01
**********************************************************************/
#include <wiringPi.h>
#include <stdio.h>
int pins[10] = {0,1,2,3,4,5,6,8,9,10};//pin 7 is not outpin

int main(void)
{
	int i;
	if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !");
		return 1; 
	}

	printf("\n");
	printf("========================================\n");
	printf("|             LED Bargraph             |\n");
	printf("|    ------------------------------    |\n");
	printf("|  Pin connect to #17 #18 #27 #22 #23  |\n");
	printf("|        #24 #25 #SDA #SCL #CE0        |\n");
	printf("|                                      |\n");
	printf("|  Use LED bargraph for loop iteration |\n");
	printf("|                                      |\n");
	printf("|                            SunFounder|\n");
	printf("========================================\n");
	printf("\n");

	for(i=0;i<=10;i++){       //make led pins' mode is output
		pinMode(pins[i], OUTPUT);
	}
	while(1){
		for(i=0;i<=10;i++){   //make led on from left to right
			if(i==7){continue;} //skip pin 7
			digitalWrite(i, LOW);
			delay(100);
			digitalWrite(i, HIGH);
		}
		for(i=10;i>-1;i--){   //make led on from right to left
			if(i==7){continue;}
			digitalWrite(i, LOW);
			delay(100);
			digitalWrite(i, HIGH);
		}
	}
	return 0;
}

