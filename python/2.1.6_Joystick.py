#!/usr/bin/env python3

import PCF8591 as ADC 
import time
import RPi.GPIO as GPIO




def print_message():
	print ("========================================")
	print ("|               Joystick               |")
	print ("|    ------------------------------    |")
	print ("|           SDA,SCL connect to         |")
	print ("|   the corresponding pin of PCF8591   |")
	print ("|                                      |")
	print ("|            Use Joystick input        |")
	print ("|                                      |")
	print ("|                            SunFounder|")
	print ("========================================\n")
	print ('Program is running...')
	print ('Please press Ctrl+C to end the program...')
	input ("Press Enter to begin\n")

def setup():
	GPIO.setmode(GPIO.BCM)
	GPIO.setup(17, GPIO.IN, pull_up_down=GPIO.PUD_UP)	
	ADC.setup(0x48)					# Setup PCF8591
	global state

def direction():	#get joystick result
	state = ['home', 'up', 'down', 'left', 'right', 'pressed']
	i = 0

	if ADC.read(0) <= 5:
		i = 1		#up
	if ADC.read(0) >= 250:
		i = 2		#down

	if ADC.read(1) >= 250:
		i = 3		#left
	if ADC.read(1) <= 5:
		i = 4		#right

	if GPIO.input(17) == 0:
		i = 5		# Button pressed

	if ADC.read(0) - 125 < 15 and ADC.read(0) - 125 > -15	and ADC.read(1) - 125 < 15 and ADC.read(1) - 125 > -15 and GPIO.input(17) == 1:
		i = 0
	#print("%d %d %d \n"%)
	return state[i]

def loop():
	status = ''
	while True:
		tmp = direction()
		if tmp != None and tmp != status:
			print (tmp)
			status = tmp

def destroy():
	pass

if __name__ == '__main__':		# Program start from here
	print_message()
	setup()
	try:
		loop()
	except KeyboardInterrupt:  	# When 'Ctrl+C' is pressed, the program destroy() will be  executed.
		destroy()
		
	
