#!/usr/bin/env python3

import RPi.GPIO as GPIO

ledPin = 18    # define the ledPin
sensorPin = 17    # define the sensorPin

def print_message():
	print ("========================================")
	print ("|           PIR control LED            |")
	print ("|    ------------------------------    |")
	print ("|         PIR connect to #17           |")
	print ("|         LED connect to #18           |")
	print ("|                                      |")
	print ("|       User PIR to control LED        |")
	print ("|                                      |")
	print ("|                            SunFounder|")
	print ("========================================\n")
	print ('Program is running...')
	print ('Please press Ctrl+C to end the program...')
	input ("Press Enter to begin\n")

def setup():
	GPIO.setmode(GPIO.BCM)       # Numbers GPIOs by physical location
	GPIO.setup(ledPin, GPIO.OUT)   # Set ledPin's mode is output
	GPIO.setup(sensorPin, GPIO.IN)    # Set sensorPin's mode is input

def loop():
	while True:
		if GPIO.input(sensorPin)==GPIO.HIGH:
			GPIO.output(ledPin,GPIO.HIGH)
			print ('led on ...')
		else :
			GPIO.output(ledPin,GPIO.LOW)
			print ('led off ...')

def destroy():
	GPIO.cleanup()                     # Release resource

if __name__ == '__main__':     # Program start from here
	print_message()
	setup()
	try:
		loop()
	except KeyboardInterrupt:  # When 'Ctrl+C' is pressed, the child program destroy() will be  executed.
		destroy()

