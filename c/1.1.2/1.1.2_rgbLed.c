/**********************************************************************
* Filename    : 1.1.2_rgbLed.c
* Description : Make a RGB LED emits various color.
* Author      : Robot
* E-mail      : support@sunfounder.com
* website     : www.sunfounder.com
* Update      : Cavon    2016/07/01
**********************************************************************/
#include <wiringPi.h>
#include <softPwm.h>
 // library used for realizing the pwm function of the software. 
#include <stdio.h>

#define uchar unsigned char

#define LedPinRed    0
#define LedPinGreen  1
#define LedPinBlue   2

// define function used for initializing I/O port to output for pwm. 
void ledInit(void){
	softPwmCreate(LedPinRed,  0, 100);
	softPwmCreate(LedPinGreen,0, 100);
	softPwmCreate(LedPinBlue, 0, 100);
 	// LedPinX refers to one pin. 0 is the minimum value and 100 is the maximum (as a percentage). The function is to use software to create a PWM pin, set its value between 0-100%. 
}

void ledColorSet(uchar r_val, uchar g_val, uchar b_val){
// This function is to set the colors of the LED. Using RGB, the formal parameter r_val represents the luminance of the red one, g_val of the green one, b_val of the blue one. The three formal parameters’ different values corresponds to various colors. You can modify the 3 formal parameters randomly to verify. 
	softPwmWrite(LedPinRed,   r_val);
	softPwmWrite(LedPinGreen, g_val);
	softPwmWrite(LedPinBlue,  b_val);
}

int main(void){

	if(wiringPiSetup() == -1){ //when initialize wiring failed, printf message to screen
		printf("setup wiringPi failed !");
		return 1; 
	}

	ledInit();

	printf("\n");
	printf("\n");
	printf("========================================\n");
	printf("|              Breath LED              |\n");
	printf("|    ------------------------------    |\n");
	printf("|       Red Pin connect to #17         |\n");
	printf("|      Green Pin connect to #18        |\n");
	printf("|       Blue Pin connect to #27        |\n");
	printf("|                                      |\n");
	printf("|  Make a RGB LED emits various color  |\n");
	printf("|                                      |\n");
	printf("|                            SunFounder|\n");
	printf("========================================\n");
	printf("\n");
	printf("\n");


	while(1){
		printf("Red\n");
		ledColorSet(0xff,0x00,0x00);   //red
		// red calls the function defined before. Write oxff into LedPinRed and ox00 into LedPinGreen and LedPinBlue. Only the Red LED lights up after running this code. If you want to light up LEDs in other colors, just modify the parameters.  		
		delay(500);
		printf("Green\n");
		ledColorSet(0x00,0xff,0x00);   //green
		delay(500);
		printf("Blue\n");
		ledColorSet(0x00,0x00,0xff);   //blue
		delay(500);

		printf("Yellow\n");
		ledColorSet(0xff,0xff,0x00);   //yellow
		delay(500);
		printf("Purple\n");
		ledColorSet(0xff,0x00,0xff);   //purple
		delay(500);
		printf("Cyan\n");
		ledColorSet(0xc0,0xff,0x3e);   //cyan
		delay(500);
	}

	return 0;
}
