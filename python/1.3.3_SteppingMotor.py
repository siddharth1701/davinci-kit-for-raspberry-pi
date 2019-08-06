#!/usr/bin/env python3

import RPi.GPIO as GPIO
import time 

motorPins = (12, 16, 18, 22)    #pins connected to four phase
antiClk = (0x01,0x02,0x04,0x08) 
clk = (0x08,0x04,0x02,0x01)

def setup():
    GPIO.setmode(GPIO.BOARD)       # Numbers GPIOs by physical location
    for pin in motorPins:
        GPIO.setup(pin,GPIO.OUT)

  
def moveSteps(direction, steps):
    for step in range(steps):
        for j in range(0,4,1):  #cycle according to power supply order 
            for i in range(0,4,1):  #assign to each pin
                if (direction == 1):#clockwise
                    GPIO.output(motorPins[i],((antiClk[j] == 1<<i) and GPIO.HIGH or GPIO.LOW))
                else :              #anticlockwise
                    GPIO.output(motorPins[i],((clk[j] == 1<<i) and GPIO.HIGH or GPIO.LOW))
            time.sleep(0.003)    #the delay can not be less than 3ms

#function used to stop rotating
def motorStop():
    for i in range(0,4,1):
        GPIO.output(motorPins[i],GPIO.LOW)
            
def loop():
    while True:
        moveSteps(1,512)
        time.sleep(1)
        moveSteps(0,512) 
        time.sleep(1)

def destroy():
    GPIO.cleanup()             # Release resource

if __name__ == '__main__':     # Program start from here
    setup()
    try:
        loop()
    except KeyboardInterrupt:  # When 'Ctrl+C' is pressed, the program destroy() will be  executed.
        destroy()


