/**********************************************************************
* Filename    : 1.1.6_LedMatrix.c
* Description : Use two 74HC595 to dot matrix.
* Author      : Robot
* E-mail      : support@sunfounder.com
* website     : www.sunfounder.com
* Update      : Cavon    2016/07/01
**********************************************************************/
#include <wiringPi.h>
#include <stdio.h>

#define   SDI   0   //serial data input
#define   RCLK  1   //memory clock input(STCP)
#define   SRCLK 2   //shift register clock input(SHCP)

unsigned char code_H[20] = {0x01,0xff,0x80,0xff,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
unsigned char code_L[20] = {0x00,0x7f,0x00,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};


void init(void){
	pinMode(SDI, OUTPUT); 
	pinMode(RCLK, OUTPUT); 
	pinMode(SRCLK, OUTPUT); 

	digitalWrite(SDI, 0);
	digitalWrite(RCLK, 0);
	digitalWrite(SRCLK, 0);
}

void hc595_in(unsigned char dat){
	int i;

	for(i=0;i<8;i++){
		digitalWrite(SDI, 0x80 & (dat << i));
		digitalWrite(SRCLK, 1);
		delay(1);
		digitalWrite(SRCLK, 0);
	}
}

void hc595_out(){
	digitalWrite(RCLK, 1);
	delay(1);
	digitalWrite(RCLK, 0);
}

int main(void){
	int i;

	if(wiringPiSetup() == -1){ //when initialize wiring failed, print message to screen
		printf("setup wiringPi failed !");
		return 1; 
	}

	init();

	printf("\n");
	printf("\n");
	printf("========================================\n");
	printf("|      Dot matrix with two 74HC595     |\n");
	printf("|    ------------------------------    |\n");
	printf("|         SDI connect to #17           |\n");
	printf("|         RCLK connect to #18          |\n");
	printf("|        SRCLK connect to #27          |\n");
	printf("|                                      |\n");
	printf("|    Control Dot matrix with 74HC595   |\n");
	printf("|                                      |\n");
	printf("|                            SunFounder|\n");
	printf("========================================\n");
	printf("\n");
	printf("\n");

	while(1){
		for(i=0;i<sizeof(code_H);i++){
			hc595_in(code_L[i]);
			hc595_in(code_H[i]);
			hc595_out();
			delay(100);
		}

		for(i=sizeof(code_H);i>=0;i--){
			hc595_in(code_L[i]);
			hc595_in(code_H[i]);
			hc595_out();
			delay(100);
		}
	}

	return 0;
}
