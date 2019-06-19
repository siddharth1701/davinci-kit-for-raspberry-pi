#!/usr/bin/env python3

import RPi.GPIO as GPIO
import time

ledPins = [11, 12, 13, 15, 16, 18, 22, 3, 5, 24]

def print_msg():
	print ("========================================")
	print ("|             LED Bargraph             |")
	print ("|    ------------------------------    |")
	print ("|  Pin connect to #17 #18 #27 #22 #23  |")
	print ("|      #24 #25 #SDA #SCL #CE0          |")
	print ("|                                      |")
	print ("|  Use LED bargraph for loop iteration |")
	print ("|                                      |")
	print ("|                            SunFounder|")
	print ("========================================\n")
	print ('Program is running...')
	print ('Please press Ctrl+C to end the program...')
	input ("Press Enter to begin\n")

def setup():
	print_msg()
	GPIO.setmode(GPIO.BOARD)        # Numbers GPIOs by physical location
	for pin in ledPins:
		GPIO.setup(pin, GPIO.OUT)   # Set all ledPins' mode is output
		GPIO.output(pin, GPIO.HIGH) # Set all ledPins to high(+3.3V) to off led

def loop():
	while True:
		for pin in ledPins:		#make led on from left to right
			GPIO.output(pin, GPIO.LOW)	
			time.sleep(0.1)
			GPIO.output(pin, GPIO.HIGH)
		for pin in ledPins[10:0:-1]:		#make led on from right to left
			GPIO.output(pin, GPIO.LOW)	
			time.sleep(0.1)
			GPIO.output(pin, GPIO.HIGH)

def destroy():
	for pin in ledPins:
		GPIO.output(pin, GPIO.HIGH)    # turn off all leds
	GPIO.cleanup()                     # Release resource

if __name__ == '__main__':     # Program start from here
	setup()
	try:
		loop()
	except KeyboardInterrupt:  # When 'Ctrl+C' is pressed, the program destroy() will be  executed.
		destroy()

