/**********************************************************************
* Filename    : 2.2.6_MPU6050.cpp
* Description : Read the Raw data of MPU6050
* Author      : Robot
* E-mail      : support@sunfounder.com
* website     : www.sunfounder.com
* Update      : Daisy    2019/08/01
**********************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 mpu;      //instantiate a MPU6050 class object

int16_t ax, ay, az;     //store acceleration data
int16_t gx, gy, gz;     //store gyroscope data

void loop() {
    // read raw accel/gyro measurements from device
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    // display accel/gyro x/y/z values
    printf("Acceleration:\n");
    printf("X:%.2f g  Y:%.2f g  Z:%.2f g\n",(float)ax/16384,(float)ay/16384,(float)az/16384);
    printf("Angular velocity:\n");
    printf("X:%.2f d/s Y:%.2f d/s Z:%.2f d/s\n",(float)gx/131,(float)gy/131,(float)gz/131);
}

int main()
{
    mpu.initialize();     //initialize MPU6050
    // verify connection
    printf(mpu.testConnection() ? "" : "initialize failed\n");
    while(1){
        loop();
    }
    return 0;
}

