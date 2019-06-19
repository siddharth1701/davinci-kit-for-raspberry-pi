#!/usr/bin/env python3

import RPi.GPIO as GPIO
import MFRC522
import sys
import os

# Create an object of the class MFRC522
mfrc = MFRC522.MFRC522()

def setup():
	print ("Program is starting ... "	)
	print ("Press Ctrl-C to exit.\n")
	pass
	
def loop():
	global mfrc
	while(True):
		print ("Scanning Card... ")
		mfrc = MFRC522.MFRC522()
		isScan = True
		while isScan:
			# Scan for cards   
			(status,TagType) = mfrc.MFRC522_Request(mfrc.PICC_REQIDL)
			# Get the UID of the card
			(status,uid) = mfrc.MFRC522_Anticoll()
			# If we have the UID, continue
			if status == mfrc.MI_OK:
				# Select the scanned tag
				if mfrc.MFRC522_SelectTag(uid) == 0:
					print ("MFRC522_SelectTag Failed!")
				if cmdloop(uid) < 1 :
					isScan = False

				
def cmdloop(cardID):
	blockAddr = 2
	while(True):
		print ("Reading card %2X%2X%2X%2X%2X > \n"%(cardID[0],cardID[1],cardID[2],cardID[3],cardID[4]))
		key = [0xFF,0xFF,0xFF,0xFF,0xFF,0xFF]
		# Authenticate
		status = mfrc.MFRC522_Auth(mfrc.PICC_AUTHENT1A, blockAddr, key, cardID)
		# Check if authenticated
		if status == mfrc.MI_OK:
			mfrc.MFRC522_Read(blockAddr)
			print(" ")
		else:
			print ("Authentication error")
			return 0
		print ("\nInput'write' or 'clean' to modify the data\n>",end="")
		inCmd = input()
		cmd = inCmd.split(" ")

		if cmd[0] == "write":
			print ("\nInput the Data (less than 16 character)\n>",end="")
			inCmd = input()
			cmd = inCmd.split(" ")			
			data = [0]*16
			data = cmd[0][0:17]
			data = map(ord,data)
			data = list(data)
			lenData = len(list(data))
			if lenData<16:
				data+=[0]*(16-lenData)
			# This is the default key for authentication
			key = [0xFF,0xFF,0xFF,0xFF,0xFF,0xFF]			
			# Authenticate
			status = mfrc.MFRC522_Auth(mfrc.PICC_AUTHENT1A, blockAddr, key, cardID)
			# Check if authenticated
			if status == mfrc.MI_OK:
				mfrc.MFRC522_Write(blockAddr, data)
			else:
				print ("Authentication error")
				return 0
			
		elif cmd[0] == "clean":
			data = [0]*16
			# This is the default key for authentication
			key = [0xFF,0xFF,0xFF,0xFF,0xFF,0xFF]			
			# Authenticate
			status = mfrc.MFRC522_Auth(mfrc.PICC_AUTHENT1A, blockAddr, key, cardID)
			# Check if authenticated
			if status == mfrc.MI_OK:
				mfrc.MFRC522_Write(blockAddr, data)
			else:
				print ("Authentication error")
				return 0
		else :
			return 0
				
def destroy():
	GPIO.cleanup()

if __name__ == "__main__":
	setup()
	try:
		loop()
	except KeyboardInterrupt:  # Ctrl+C captured, exit
		destroy()
