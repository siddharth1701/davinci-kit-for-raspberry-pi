#!/usr/bin/env python3

import PCF8591 as ADC
import RPi.GPIO as GPIO
import time

ledPin = 17
GPIO.setmode(GPIO.BCM)

def print_message():
	print ("========================================")
	print ("|              Photoresistor           |")
	print ("|    ------------------------------    |")
	print ("|           SDA,SCL connect to         |")
	print ("|   the corresponding pin of PCF8591   |")
	print ("|           #17 connect to LED         |")
	print ("|                                      |")	
	print ("| Make Photoresistor to contral a led  |")
	print ("|                                      |")
	print ("|                            SunFounder|")
	print ("========================================\n")
	print ('Program is running...')
	print ('Please press Ctrl+C to end the program...')
	input ("Press Enter to begin\n")

def setup():
	ADC.setup(0x48)
	GPIO.setup(ledPin, GPIO.OUT)
	GPIO.output(ledPin,GPIO.LOW)
	global p	
	p = GPIO.PWM(ledPin,1000)
	p.start(0)

def loop():
	while True:
		analogVal = ADC.read(0)
		p.ChangeDutyCycle(analogVal*100/255)
		print ('Value: ', analogVal)
		
		time.sleep(0.2)

if __name__ == '__main__':
	print_message()
	try:
		setup()
		loop()
	except KeyboardInterrupt: 
		pass	

	
