
#include "I2Cdev.h"
#include "Wire.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Structure.h"
#ifndef SENSOR_H
#define SENSOR_H
extern Attitude Rpy;
void Sensor_Setup(MPU6050& mpu);
void Sensor_Read(MPU6050& mpu);

#endif 
