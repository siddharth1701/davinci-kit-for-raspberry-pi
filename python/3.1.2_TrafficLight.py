#!/usr/bin/env python3

import RPi.GPIO as GPIO
import time
import threading

#define the pins connect to 74HC595
SDI   = 18      #serial data input(DS)
RCLK  = 16      #memory clock input(STCP)
SRCLK = 12       #shift register clock input(SHCP)
number = (0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90)

placePin = (11,13,15,19)   
ledPin =(22,24,26) 

greenLight = 30
yellowLight = 5
redLight = 60
lightColor=("Red","Green","Yellow")

colorState=0
counter = 60      
t = 0         


def setup():
    GPIO.setmode(GPIO.BOARD)   
    GPIO.setup(SDI, GPIO.OUT)   
    GPIO.setup(RCLK, GPIO.OUT)
    GPIO.setup(SRCLK, GPIO.OUT)
    for pin in placePin:
        GPIO.setup(pin,GPIO.OUT)
    for pin in ledPin:
        GPIO.setup(pin,GPIO.OUT)
    
            
def hc595_shift(dat):     
	for bit in range(0, 8):	
		GPIO.output(SDI, 0x80 & (dat << bit))
		GPIO.output(SRCLK, GPIO.HIGH)
		GPIO.output(SRCLK, GPIO.LOW)
	GPIO.output(RCLK, GPIO.HIGH)
	GPIO.output(RCLK, GPIO.LOW)

def selectPlace(digit): 
    GPIO.output(placePin[0],GPIO.LOW if (digit&0x08) else GPIO.HIGH)
    GPIO.output(placePin[1],GPIO.LOW if (digit&0x04) else GPIO.HIGH)
    GPIO.output(placePin[2],GPIO.LOW if (digit&0x02) else GPIO.HIGH)
    GPIO.output(placePin[3],GPIO.LOW if (digit&0x01) else GPIO.HIGH)

def display(num):  
    hc595_shift(0xff) 
    selectPlace(0x01)   
    hc595_shift(number[num%10]) 
    time.sleep(0.003)   
    hc595_shift(0xff)
    selectPlace(0x02) 
    hc595_shift(number[num%100//10])
    time.sleep(0.003)
    hc595_shift(0xff)
    selectPlace(0x04)  
    hc595_shift(number[num%1000//100])
    time.sleep(0.003)
    hc595_shift(0xff)
    selectPlace(0x08) 
    hc595_shift(number[num%10000//1000])
    time.sleep(0.003)

def timer():        #timer function
    global counter
    global colorState
    global t
    t = threading.Timer(1.0,timer)  
    t.start()     
    counter-=1                          
    if (counter is 0):
        if(colorState is 0):
            counter= greenLight
        if(colorState is 1):
            counter=yellowLight
        if (colorState is 2):
            counter=redLight
        colorState=(colorState+1)%3
    print ("counter : %d    color: %s "%(counter,lightColor[colorState]))

def lightup(state):
    for i in range(0,3):
        GPIO.output(ledPin[i], GPIO.HIGH)
    GPIO.output(ledPin[state], GPIO.LOW)

def loop():
    global t
    global counter
    global colorState
    t = threading.Timer(1.0,timer)   
    t.start()                          
    while True:
        display(counter)
        lightup(colorState)
        
def destroy():   # When "Ctrl+C" is pressed, the function is executed. 
    global t
    GPIO.cleanup()      
    t.cancel()      #cancel the timer

if __name__ == '__main__': # Program starting from here 
    setup() 
    try:
        loop()  
    except KeyboardInterrupt:  
        destroy()  
 
