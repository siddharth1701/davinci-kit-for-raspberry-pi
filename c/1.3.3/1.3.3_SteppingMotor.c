/**********************************************************************
* Filename    : 1.3.3_SteppingMotor.c
* Description : 
* Author      : Robot
* E-mail      : support@sunfounder.com
* website     : www.sunfounder.com
* Update      : Cavon    2016/07/01
**********************************************************************/
#include <stdio.h>
#include <wiringPi.h>

const int motorPins[]={1,4,5,6};    //pins connected to four phase
const int antiClk[]={0x01,0x02,0x04,0x08};  
const int clk[]={0x08,0x04,0x02,0x01};   

void moveSteps(int direction, int steps){
    int step;
    int i=0,j=0;
    for(step=0;step<steps;step++){
        for (j=0;j<4;j++){  //cycle according to power supply order 
        for (i=0;i<4;i++){  //assign to each pin
            if(direction == 1)    //clockwise
                digitalWrite(motorPins[i],antiClk[j] == (1<<i));
            else        //anticlockwise
                digitalWrite(motorPins[i],clk[j] == (1<<i));
        }
        delay(3); //the delay can not be less than 3ms
    }
    }
}
void motorStop(){   //stop rotating
    int i;
    for(i=0;i<4;i++){
        digitalWrite(motorPins[i],LOW);
    }   
}
int main(void){
    int i;
	printf("\n");
	printf("\n");
	printf("========================================\n");
	printf("|             Stepping motor           |\n");
	printf("|    ------------------------------    |\n");
	printf("|          IN1 connect to # 18         |\n");
    printf("|          IN2 connect to # 23         |\n");
    printf("|          IN3 connect to # 24         |\n");
    printf("|          IN4 connect to # 25         |\n");
	printf("|                                      |\n");
	printf("|     Controlling a Stepping motor     |\n");
	printf("|                                      |\n");
	printf("|                            SunFounder|\n");
	printf("========================================\n");
	printf("\n");
	printf("\n");
    if(wiringPiSetup() == -1){ //when initialize wiring failed,print message to screen
        printf("setup wiringPi failed !");
        return 1; 
    }
    for(i=0;i<4;i++){
        pinMode(motorPins[i],OUTPUT);
    } 

    while(1){
        moveSteps(1,512); 
        delay(1000);
        moveSteps(0,512);
        delay(1000);
    }
    return 0;
}

