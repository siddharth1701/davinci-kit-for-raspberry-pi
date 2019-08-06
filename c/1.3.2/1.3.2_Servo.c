/**********************************************************************
* Filename    : 1.3.2_Servo.c
* Description : Servo sweep
* Author      : Robot
* E-mail      : support@sunfounder.com
* website     : www.sunfounder.com
* Update      : Daisy    2019/08/05
**********************************************************************/
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

#define servoPin    1       //define the GPIO number connected to servo
long map(long value,long fromLow,long fromHigh,long toLow,long toHigh){
    return (toHigh-toLow)*(value-fromLow) / (fromHigh-fromLow) + toLow;
}
void servoWrite(int pin, int angle){    //Create a funtion, servoWrite() to control the rotate angle of the servo.
    if(angle < 0)
        angle = 0;
    if(angle > 180)
        angle = 180;
    softPwmWrite(pin,map(angle,0,180,5,25));   
} 

int main(void)
{
    int i;
	  
    if(wiringPiSetup() == -1){ //when initialize wiring failed,print message to screen
        printf("setup wiringPi failed !");
        return 1; 
    }
    softPwmCreate(servoPin,  0, 200);       //initialize PMW pin of servo
    while(1){
        for(i=0;i<181;i++){  //make servo rotate from minimum angle to maximum angle
            servoWrite(servoPin,i);
            delay(1);
        }
        delay(500);
        for(i=181;i>-1;i--){  //make servo rotate from maximum angle to minimum angle
            servoWrite(servoPin,i);
            delay(1);
        }
        delay(500);
    }
    return 0;
}

