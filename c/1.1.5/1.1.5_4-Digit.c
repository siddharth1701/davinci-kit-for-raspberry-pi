/**********************************************************************
* Filename    : 1.1.5_4-Digit.c
* Description : Control 4 Digit 7-Segment Display
* Author      : Robot
* E-mail      : support@sunfounder.com
* website     : www.sunfounder.com
* Update      : Cavon    2016/07/01
**********************************************************************/
#include <wiringPi.h>
#include <stdio.h>
#include <wiringShift.h>
#include <signal.h>
#include <unistd.h>
#define     SDI     5   
#define     RCLK    4  
#define     SRCLK    1   
const int placePin[]={0,2,3,12};        // Define 4 digit's common pin

// A segment code array from 0 to 9 in Hexadecimal (Common anode) 
unsigned char number[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

int counter = 0;    //variable counter,the number will be displayed 

//select the place of the value, this is only one place that will be enable each time.
//the parameter digit is optional for 0001,0010,0100,1000
void selectPlace(int digit){    
    digitalWrite(placePin[0],!(digit&0x08));
    digitalWrite(placePin[1],!(digit&0x04));
    digitalWrite(placePin[2],!(digit&0x02));
    digitalWrite(placePin[3],!(digit&0x01));
}

void hc595_shift(int8_t data){      //To assign 8 bit value to 74HC595’s shift register

    int i;  
    for(i = 0; i < 8; i++){
        digitalWrite(SDI, 0x80 & (data << i));
        digitalWrite(SRCLK,1);
        delayMicroseconds(1);
        digitalWrite(SRCLK,0);
	}
        digitalWrite(RCLK,1);
        delayMicroseconds(1);
        digitalWrite(RCLK,0);        
}

void display(int counter){  //display the number
	hc595_shift(0xff);	
    selectPlace(0x01);      
    hc595_shift(number[counter%10]); //Display the number on the single digit of the value  
    delay(1); 
    
    hc595_shift(0xff);    
    selectPlace(0x02); 
    hc595_shift(number[counter%100/10]);
    delay(1);
    
    hc595_shift(0xff);    
    selectPlace(0x04); 
    hc595_shift(number[counter%1000/100]);
    delay(1);
    
    hc595_shift(0xff);    
    selectPlace(0x08);
    hc595_shift(number[counter%10000/1000]);
    delay(1);
}
void timer(int  sig){       //Timer function
    if(sig == SIGALRM){   //If the signal is SIGALRM, the value of counter plus 1, and update the number displayed by 7-segment display
        counter ++;         
        alarm(1);           //set the next timer time
        printf("counter : %d \n",counter);
    }
}
int main(void)
{
    int i;
    printf("\n");
	printf("========================================\n");
	printf("|        4 Digit 7-Segment Display     |\n");
	printf("|    ------------------------------    |\n");
	printf("|     4 Digit display common pin       |\n");
	printf("|         connect to #17 #27 #22 MOSI  |\n");
	printf("|     74HC595 CH_CP ST_CP DS pin       |\n");
	printf("|         connect to #18 #23 #24       |\n");
	printf("|                                      |\n");
	printf("|                            SunFounder|\n");
	printf("========================================\n");
	printf("\n");

    if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
        printf("setup wiringPi failed !");
        return 1; 
    }
    pinMode(SDI,OUTPUT);        //set the pin connected to74HC595 for output mode
    pinMode(RCLK,OUTPUT);
    pinMode(SRCLK,OUTPUT);
    //set the pin connected to 7-segment display common end to output mode
    for(i=0;i<4;i++){       
        pinMode(placePin[i],OUTPUT);
        digitalWrite(placePin[i],HIGH);
    }
    signal(SIGALRM,timer);  //configure the timer
    alarm(1);               //set the time of timer to 1s
    while(1){
        display(counter);   //display the number counter
    }
    return 0;
}


