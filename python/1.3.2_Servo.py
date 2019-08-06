#!/usr/bin/env python3

import RPi.GPIO as GPIO
import time

servoPin = 12

def map( value, fromLow, fromHigh, toLow, toHigh):
    return (toHigh-toLow)*(value-fromLow) / (fromHigh-fromLow) + toLow

def setup():
    global p
    GPIO.setmode(GPIO.BOARD)       # Numbers GPIOs by physical location
    GPIO.setup(servoPin, GPIO.OUT)   # Set servoPin's mode is output
    GPIO.output(servoPin, GPIO.LOW)  # Set servoPin to low

    p = GPIO.PWM(servoPin, 50)     # set Frequecy to 50Hz
    p.start(0)                     # Duty Cycle = 0
    
def servoWrite(angle):      # make the servo rotate to specific angle (0-180 degrees) 
    if(angle<0):
        angle = 0
    elif(angle > 180):
        angle = 180
    p.ChangeDutyCycle(map(angle,0,180,2.5,12.5))#map the angle to duty cycle and output it
    
def loop():
    while True:
        for i in range(0, 181, 1):   #make servo rotate from 0 to 180 deg
            servoWrite(i)     # Write to servo
            time.sleep(0.001)
        time.sleep(0.5)
        for i in range(180, -1, -1): #make servo rotate from 180 to 0 deg
            servoWrite(i)
            time.sleep(0.001)
        time.sleep(0.5)

def destroy():
    p.stop()
    GPIO.cleanup()

if __name__ == '__main__':     #Program start from here
    setup()
    try:
        loop()
    except KeyboardInterrupt:  # When 'Ctrl+C' is pressed, the program destroy() will be  executed.
        destroy()
