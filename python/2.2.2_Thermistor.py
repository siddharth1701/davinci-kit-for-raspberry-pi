#!/usr/bin/env python3

import PCF8591 as ADC
import RPi.GPIO as GPIO
import time
import math

GPIO.setmode(GPIO.BCM)

def print_message():
	print ("========================================")
	print ("|               Thermistor             |")
	print ("|    ------------------------------    |")
	print ("|           SDA,SCL connect to         |")
	print ("|   the corresponding pin of PCF8591   |")
	print ("|                                      |")	
	print ("| Use thermistor to detect temperature |")
	print ("|                                      |")
	print ("|                            SunFounder|")
	print ("========================================\n")
	print ('Program is running...')
	print ('Please press Ctrl+C to end the program...')
	input ("Press Enter to begin\n")

def setup():
	ADC.setup(0x48)

def loop():
	while True:
		analogVal = ADC.read(0)
		Vr = 5 * float(analogVal) / 255
		Rt = 10000 * Vr / (5 - Vr)
		temp = 1/(((math.log(Rt / 10000)) / 3950) + (1 / (273.15+25)))
		temp = temp - 273.15
		print ('temperature = ', temp, 'C')
		time.sleep(0.2)

if __name__ == '__main__':
	print_message()
	try:
		setup()
		loop()
	except KeyboardInterrupt: 
		pass	
		
	
