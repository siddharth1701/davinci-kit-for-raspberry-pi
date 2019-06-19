#!/usr/bin/env python3
#When the system detects this, it will search the installation path of python in the env setting, then call the corresponding interpreter to complete the operation. It is to prevent the user not installing the python onto the /usr/bin default path. 

import RPi.GPIO as GPIO # import RPI.GPIO package, thus python code control GPIO easily with it. 
import time  # import time package, for time delay function in the following program. 

# Set #17 as LED pin
LedPin = 17
# LED connects to the BCM17(#17) of the T-shape extension board, namely, the GPIO 0 of the Raspberry Pi. 
# Define a setup function for some setup


# Define a function to print message at the beginning
def print_message():
	print ("========================================")
	print ("|              Blinking LED            |")
	print ("|    ------------------------------    |")
	print ("|         LED connect to #17           |")
	print ("|                                      |")
	print ("|        LED will Blink at 500ms       |")
	print ("|                                      |")
	print ("|                            SunFounder|")
	print ("========================================\n")
	print ('Program is running...')
	print ('Please press Ctrl+C to end the program...')
	input ("Press Enter to begin\n")

# Define a setup function for some setup
def setup():
	# Set the GPIO modes to BCM Numbering
	GPIO.setmode(GPIO.BCM)
	# Set LedPin's mode to output, 
	# and initial level to High(3.3v)
	GPIO.setup(LedPin, GPIO.OUT, initial=GPIO.HIGH)

# Define a main function for main process
def main():
	# Print messages
	print_message()
	while True:
		print ('...LED ON')
		# Turn on LED
		GPIO.output(LedPin, GPIO.LOW)
		time.sleep(0.5)
		# delay 0.5 second, which is equals to the delay in C language, using second as the unit,

		print ('LED OFF...')
		# Turn off LED
		GPIO.output(LedPin, GPIO.HIGH) 
		time.sleep(0.5)

# Define a destroy function for clean up everything after the script finished 
def destroy():
	# Turn off LED
	GPIO.output(LedPin, GPIO.HIGH)
	# Release resource
	GPIO.cleanup()                    

# If run this script directly, do:
if __name__ == '__main__':
	setup()
	try:
		main()
	# When 'Ctrl+C' is pressed, the program destroy() will be executed.
	except KeyboardInterrupt:
		destroy()
