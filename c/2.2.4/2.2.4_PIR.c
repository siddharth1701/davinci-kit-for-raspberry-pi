/**********************************************************************
* Filename    : 2.2.4_PIR.c
* Description : Controlling an led by infrared Motion sensor.
* Author      : Robot
* E-mail      : support@sunfounder.com
* website     : www.sunfounder.com
* Update      : Daisy    2019/08/01
**********************************************************************/
#include <wiringPi.h>
#include <stdio.h>

#define ledPin    1     //define the ledPin
#define sensorPin 0     //define the sensorPin

int main(void)
{
    if(wiringPiSetup() == -1){ //when initialize wiring failed,print message to screen
        printf("setup wiringPi failed !");
        return 1;
    }
    pinMode(ledPin, OUTPUT);
    pinMode(sensorPin, INPUT);
    while(1){
        if(digitalRead(sensorPin) == HIGH){ //if read sensor for high level
            digitalWrite(ledPin, HIGH);   //led on
            printf("LED ON! \n");
        }
        else {
           digitalWrite(ledPin, LOW);   //led off
            printf("LED OFF!\n");
        }
    }

    return 0;
}