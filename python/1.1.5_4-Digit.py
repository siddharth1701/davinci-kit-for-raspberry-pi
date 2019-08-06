#!/usr/bin/env python3

import RPi.GPIO as GPIO
import time
import threading

#define the pins connect to 74HC595
SDI   = 18      #serial data input(DS)
RCLK  = 16      #memory clock input(STCP)
SRCLK = 12       #shift register clock input(SHCP)
number = (0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90)
# A segment code array from 0 to 9 in Hexadecimal (Common anode) 

placePin = (11,13,15,19)    # Define 4 digit's common pin
counter = 0         # Variable counter, the number will be displayed
t = 0               # define the Timer object

def setup():
    GPIO.setmode(GPIO.BOARD)    # Number GPIOs by its physical location
    GPIO.setup(SDI, GPIO.OUT)       # Set pin mode to output
    GPIO.setup(RCLK, GPIO.OUT)
    GPIO.setup(SRCLK, GPIO.OUT)
    for pin in placePin:
        GPIO.setup(pin,GPIO.OUT)
    
            
def hc595_shift(dat):      #shift the data to 74HC595
	for bit in range(0, 8):	
		GPIO.output(SDI, 0x80 & (dat << bit))
		GPIO.output(SRCLK, GPIO.HIGH)
		GPIO.output(SRCLK, GPIO.LOW)
	GPIO.output(RCLK, GPIO.HIGH)
	GPIO.output(RCLK, GPIO.LOW)

# select the place of the value, this is only one place that will be enable each time.
# the parameter digit is optional for 0001,0010,0100,1000    
def selectPlace(digit): 
    GPIO.output(placePin[0],GPIO.LOW if (digit&0x08) else GPIO.HIGH)
    GPIO.output(placePin[1],GPIO.LOW if (digit&0x04) else GPIO.HIGH)
    GPIO.output(placePin[2],GPIO.LOW if (digit&0x02) else GPIO.HIGH)
    GPIO.output(placePin[3],GPIO.LOW if (digit&0x01) else GPIO.HIGH)

def display(counter):   #display the number
    hc595_shift(0xff)   #clean up the display
    selectPlace(0x01)   #Select place
    hc595_shift(number[counter%10]) #Display the number on the single digit of the value  
    time.sleep(0.003)   
    hc595_shift(0xff)
    selectPlace(0x02) 
    hc595_shift(number[counter%100//10])
    time.sleep(0.003)
    hc595_shift(0xff)
    selectPlace(0x04)  
    hc595_shift(number[counter%1000//100])
    time.sleep(0.003)
    hc595_shift(0xff)
    selectPlace(0x08) 
    hc595_shift(number[counter%10000//1000])
    time.sleep(0.003)

def timer():        #timer function
    global counter
    global t
    t = threading.Timer(1.0,timer)      #set the time again
    t.start()                           #Start timing
    counter+=1                          
    print ("counter : %d"%counter)
    
def loop():
    global t
    global counter
    t = threading.Timer(1.0,timer)      #set the timer
    t.start()                           # Start timing
    while True:
        display(counter)                # display the number counter
        
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
 
