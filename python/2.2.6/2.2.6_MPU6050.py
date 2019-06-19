#!/usr/bin/env python3

import MPU6050 
import time

mpu = MPU6050.MPU6050()     #instantiate a MPU6050 class object
ac = [0]*3               #store accelerometer data
gy = [0]*3                #store gyroscope data

def print_message():
	print ("========================================")
	print ("|                 MPU6050              |")
	print ("|    ------------------------------    |")
	print ("|           SDA,SCL connect to         |")
	print ("|   the corresponding pin of MPU6050   |")
	print ("|                                      |")	
	print ("|          Use MPU6050 to detect       |")
	print ("|   Acceleration and Angular velocity  |")
	print ("|                                      |")
	print ("|                            SunFounder|")
	print ("========================================\n")
	print ('Program is running...')
	print ('Please press Ctrl+C to end the program...')
	input ("Press Enter to begin\n")

def setup():
    mpu.dmp_initialize()    #initialize MPU6050
    
def loop():
    while(True):
        ac = mpu.get_acceleration()      #get accelerometer data
        gy = mpu.get_rotation()           #get gyroscope data
        print("Acceleration:\n")
        print("X:%.2f g  Y:%.2f g  Z:%.2f g\n"%(ac[0]/16384.0,ac[1]/16384.0,ac[2]/16384.0))
        print("Angular velocity:\n")
        print("X:%.2f d/s Y:%.2f d/s Z:%.2f d/s\n"%(gy[0]/131.0,gy[1]/131.0,gy[2]/131.0))
        time.sleep(0.1)
        
if __name__ == '__main__':     # Program start from here
    print_message()
    setup()
    try:
        loop()
    except KeyboardInterrupt:  # When 'Ctrl+C' is pressed,the program will exit.
        pass

