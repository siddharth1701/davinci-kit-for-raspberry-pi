/**********************************************************************
* Filename    : 2.2.7_RFID.c
* Description : Use MFRC522 Read and Write Mifare Card.
* Author      : Robot
* E-mail      : support@sunfounder.com
* website     : www.sunfounder.com
* Update      : Daisy    2019/08/01
**********************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include "mfrc522.h"

int scan_loop(uint8_t *CardID);
int tag_select(uint8_t *CardID);

int main(int argc, char **argv) {
	MFRC522_Status_t ret;
	uint8_t CardID[5] = { 0x00, };
	uint8_t tagType[16] = {0x00,};
	static char command_buffer[1024];

	ret = MFRC522_Init('B');
	if (ret < 0) {
		perror("Failed to initialize");
		exit(-1);
	}

	while (1) {
		puts("Scanning Card... ");
		while (1) {
			ret = MFRC522_Request(PICC_REQIDL, tagType);
			if (ret == MI_OK) {
				ret = MFRC522_Anticoll(CardID);	
				if(ret == MI_OK){
					ret = tag_select(CardID);
					if (ret == MI_OK) {
						ret = scan_loop(CardID);
						if (ret < 0) {
							printf("Error...\r\n");
							break;
						} 
					}
				}
				else{
					printf("Get Card ID failed!\r\n");
				}								
			}
			MFRC522_Halt();
		}
		MFRC522_Halt();
		MFRC522_Init('B');
	}
}
int scan_loop(uint8_t *CardID) {
	while (1) {
		char input[32];
		int block_start=2;
		printf("Reading card %02X%02X%02X%02X \n", CardID[0], CardID[1], CardID[2], CardID[3]);
		MFRC522_Debug_DumpSector(CardID, block_start);
		printf("Input 'write' or 'clean' to modify the data\n >");
		scanf("%s", input);
		printf("\n");
		if(strcmp(input, "clean") == 0){
			getchar();
			if (MFRC522_Debug_Clean(CardID, block_start)) {
				return -1;
			}
			
		} else if (strcmp(input, "write") == 0) {
			char write_buffer[256];
			size_t len = 0;
			getchar();
			printf("Input the Data (less than 16 character)\n>");
			scanf("%s",write_buffer);
			if (MFRC522_Debug_Write(CardID, block_start, write_buffer,
					strlen(write_buffer)) < 0) {
				return -1;
			}
		} 
	}
	return 0;
}
int tag_select(uint8_t *CardID) {
	int ret_int;
	ret_int = MFRC522_SelectTag(CardID);
	if (ret_int == 0) {
		printf("Card Select Failed\r\n");
		return -1;
	} 
	ret_int = 0;
	return ret_int;
}