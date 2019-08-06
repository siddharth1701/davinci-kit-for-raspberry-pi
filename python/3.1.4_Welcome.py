#!/usr/bin/env python3

import RPi.GPIO as GPIO
import time

ledPin = 18    # define the ledPin
pirPin = 17    # define the sensorPin
servoPin = 22  # define the servoPin
buzPin = 27    # define the buzzerpin


CL = [0, 131, 147, 165, 175, 196, 211, 248]        # Frequency of Low C notes

CM = [0, 262, 294, 330, 350, 393, 441, 495]        # Frequency of Middle C notes

CH = [0, 525, 589, 661, 700, 786, 882, 990]        # Frequency of High C notes

song = [    CH[5],CH[2],CM[6],CH[2],CH[3],CH[6],CH[3],CH[5],CH[3],CM[6],CH[2]    ]

beat = [    1,1,1,1,1,2,1,1,1,1,1,]


def setup():
    global p
    global Buzz                        # Assign a global variable to replace GPIO.PWM 
    GPIO.setmode(GPIO.BCM)       # Numbers GPIOs by physical location
    GPIO.setup(ledPin, GPIO.OUT)   # Set ledPin's mode is output
    GPIO.setup(pirPin, GPIO.IN)    # Set sensorPin's mode is input
    GPIO.setup(servoPin, GPIO.OUT)   # Set servoPin's mode is output
    GPIO.output(servoPin, GPIO.LOW)  # Set servoPin to low
    GPIO.setup(buzPin, GPIO.OUT)    # Set pins' mode is output

    Buzz = GPIO.PWM(buzPin, 440)    # 440 is initial frequency.
    Buzz.start(50)                    # Start Buzzer pin with 50% duty ration

    p = GPIO.PWM(servoPin, 50)     # set Frequece to 50Hz
    p.start(0)                     # Duty Cycle = 0

def map( value, fromLow, fromHigh, toLow, toHigh):
    return (toHigh-toLow)*(value-fromLow) / (fromHigh-fromLow) + toLow

    
def servoWrite(angle):      # make the servo rotate to specific angle (0-180 degrees) 
    if(angle<0):
        angle = 0
    elif(angle > 180):
        angle = 180
    p.ChangeDutyCycle(map(angle,0,180,2.5,12.5))#map the angle to duty cycle and output it
    
def doorbell():
    for i in range(1, len(song)):        # Play song 1
        Buzz.ChangeFrequency(song[i])    # Change the frequency along the song note
        time.sleep(beat[i] * 0.25)        # delay a note for beat * 0.25s
    time.sleep(1)                        # Wait a second for next song.

def closedoor():
    GPIO.output(ledPin, GPIO.LOW)
    Buzz.ChangeFrequency(1)
    for i in range(180, -1, -1): #make servo rotate from 180 to 0 deg
        servoWrite(i)
        time.sleep(0.001)

def opendoor():
    GPIO.output(ledPin, GPIO.HIGH)
    for i in range(0, 181, 1):   #make servo rotate from 0 to 180 deg
        servoWrite(i)     # Write to servo
        time.sleep(0.001)
    doorbell()
    closedoor()

def loop():
    while True:
        print ('Sensor Value: %d' % GPIO.input(pirPin))
        if GPIO.input(pirPin)==GPIO.HIGH:
            opendoor()


def destroy():
    GPIO.cleanup()                     # Release resource
    p.stop()
    Buzz.stop()

if __name__ == '__main__':     # Program start from here
    setup()
    try:
        loop()
    except KeyboardInterrupt:  # When 'Ctrl+C' is pressed, the program destroy() will be  executed.
        destroy()