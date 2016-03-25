// I2C device class (I2Cdev) demonstration Arduino sketch for MPU6050 class
// 10/7/2011 by Jeff Rowberg <jeff@rowberg.net>
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
//     2011-10-07 - initial release

/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2011 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include "Wire.h"

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Sensor.h"
#include <Servo.h> 
#include<math.h>
// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
Attitude Rpy;
Servo myservo;  // create servo object to control a servo 
int16_t ax, ay, az;
int16_t gx, gy, gz;

#define LED_PIN 13
bool blinkState = false;
void setup() {
  Serial.begin(38400);
  Sensor_Setup(accelgyro);
}
void loop() {
 Sensor_Read(accelgyro);
 Serial.print("ROLL: ");
  Serial.print(Rpy.ROLL); Serial.print("\tPITCH: ");
  Serial.print(Rpy.PITCH); Serial.print("\tYAW: ");
  Serial.println(Rpy.YAW);
}
/*
#define Kp 2.0f
#define Ki 0.002f
#define halfT 0.001f
float q0 = 1, q1 = 0, q2 = 0, q3 = 0;
float exInt = 0, eyInt = 0, ezInt = 0;
float angle_yaw, angle_pitch, angle_roll;
void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az) {
  float norm;
  float vx, vy, vz;
  float ex, ey, ez;
  norm = sqrt(ax * ax + ay * ay + az * az);
  ax = ax / norm;
  ay = ay / norm;
  az = az / norm;
  //把四元数换算成“方向余弦矩阵”中的第三列的三个元素
  vx = 2 * (q1 * q3 - q0 * q2);
  vy = 2 * (q0 * q1 + q2 * q3);
  vz = q0 * q0 - q1 * q1 - q2 * q2 + q3 * q3;
  //叉乘
  ex = ay * vz - az * vy;
  ey = az * vx - ax * vz;
  ez = ax * vy - ay * vx;
  //将叉乘误差进行积分
  exInt = exInt + ex * Ki;
  eyInt = eyInt + ey * Ki;
  ezInt = ezInt + ez * Ki;
  //用叉乘误差来做PI修正陀螺零偏
  gx = gx + Kp * ex + exInt;
  gy = gy + Kp * ey + eyInt;
  gz = gz + Kp * ez + ezInt;
  //得到相应的四元数
  q0 = q0 + (-q1 * gx - q2 * gy - q3 * gz) * halfT;
  q1 = q1 + (q0 * gx + q2 * gz - q3 * gy) * halfT;
  q2 = q2 + (q0 * gy - q1 * gz + q3 * gx) * halfT;
  q3 = q3 + (q0 * gz + q1 * gy - q2 * gx) * halfT;
  //四元数单位化
  norm = sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
  q0 = q0 / norm;
  q1 = q1 / norm;
  q2 = q2 / norm;
  q3 = q3 / norm;
}
/*
void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();

    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(38400);

    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    // configure Arduino LED for
    pinMode(LED_PIN, OUTPUT);
     myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
}

void loop() {
    // read raw accel/gyro measurements from device
   accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
   IMUupdate(gx, gy, gz, ax, ay, az);
   angle_yaw = atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2*q2 - 2 * q3* q3 + 1)* 57.3; // yaw
   angle_pitch  = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3; // pitch
   angle_roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; // roll
   Serial.print("Yaw: "); Serial.print(angle_yaw);
   Serial.print(" Pitch: "); Serial.print(angle_pitch);
   Serial.print(" Roll: "); Serial.print(angle_roll);
   Serial.println();

  
}*/
