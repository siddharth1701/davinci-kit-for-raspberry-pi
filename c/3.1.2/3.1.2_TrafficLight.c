/**********************************************************************
* Filename    : 3.1.2_TrafficLight.c
* Description : 
* Author      : Robot
* E-mail      : support@sunfounder.com
* website     : www.sunfounder.com
* Update      : Jimmy  2019/08/06 
**********************************************************************/
#include <wiringPi.h>
#include <stdio.h>
#include <wiringShift.h>
#include <signal.h>
#include <unistd.h>
#define     SDI     5   //serial data input(DS)
#define     RCLK    4   //memory clock input(STCP)
#define     SRCLK    1    //shift register clock input(SHCP)
const int placePin[]={0,2,3,12};        // Define 4 digit's common pin
const int ledPin[]={6,10,11};   //Define 3 LED pin
unsigned char number[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

int greenLight = 30;
int yellowLight = 5;
int redLight = 60;
int colorState = 0;
char *lightColor[]={"Red","Green","Yellow"};
int counter = 60;

//here is the 4 digital function
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

void display(int num){  //display the number
	hc595_shift(0xff);	
    selectPlace(0x01);      
    hc595_shift(number[num%10]); 
    delay(1); 
 
    hc595_shift(0xff);
    selectPlace(0x02); 
    hc595_shift(number[num%100/10]);
    delay(1);
   
    hc595_shift(0xff);    
    selectPlace(0x04); 
    hc595_shift(number[num%1000/100]);
    delay(1);

    hc595_shift(0xff);    
    selectPlace(0x08);
    hc595_shift(number[num%10000/1000]);
    delay(1);
}

//here is the timer for countdown 
void timer(int  sig){       //Timer function
    if(sig == SIGALRM){   
        counter --;         
        alarm(1); 
        if(counter == 0){
            if(colorState == 0) counter = greenLight;
            if(colorState == 1) counter = yellowLight;
            if(colorState == 2) counter = redLight;
            colorState = (colorState+1)%3; 
        }
        printf("counter : %d \t light color: %s \n",counter,lightColor[colorState]);
    }
}

void lightup(int state)
{
    for(int i=0;i<3;i++){
        digitalWrite(ledPin[i],HIGH);
    }
    digitalWrite(ledPin[state],LOW);    
}

int main(void)
{
    int i;


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
    //set the led pin
    for(i=0;i<3;i++){       
        pinMode(ledPin[i],OUTPUT);
        digitalWrite(ledPin[i],HIGH);
    }
    signal(SIGALRM,timer);  //configure the timer
    alarm(1);               //set the time of timer to 1s
    while(1){
        display(counter);   //display the number counter
        lightup(colorState); //turn on the traffic light
    }
    return 0;
}