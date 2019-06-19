#!/usr/bin/env python3

import PCF8591 as ADC
import time
import RPi.GPIO as GPIO

def print_message():
    print ("========================================")
    print ("|             Potentiometer            |")
    print ("|    ------------------------------    |")
    print ("|           SDA,SCL connect to         |")
    print ("|   the corresponding pin of PCF8591   |")
    print ("|                                      |")
    print ("| Make potentiometer to contral a led  |")
    print ("|                                      |")
    print ("|                            SunFounder|")
    print ("========================================\n")
    print ('Program is running...')
    print ('Please press Ctrl+C to end the program...')
    input ("Press Enter to begin\n")

def setup():
    ADC.setup(0x48)

def loop():
    status = 1
    while True:
        print ('Value:', ADC.read(0))
        Value = ADC.read(0)
        outvalue = map(Value,0,255,120,255)
        ADC.write(outvalue)
        time.sleep(0.2)
def destroy():
    ADC.write(0)

def map(x, in_min, in_max, out_min, out_max):
        '''To map the value from arange to another'''
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

if __name__ == '__main__':
    print_message()
    try:
        setup()
        loop()
    except KeyboardInterrupt: 
        destroy()

        
    
