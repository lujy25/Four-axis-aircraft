#include"Sensor.h"
#include "Structure.h"
//MPU control status
bool dmpReady = false;
uint8_t mpuIntStatus; //actual interrupt status byte from MPU
uint8_t devStatus; //return status after each device operation(0 for success, !0 as error)
uint16_t packetSize; //DMP packet size(default is 42 bytes)
uint16_t fifoCount; //bytes count in FIFO
uint8_t fifoBuffer[64]; //FIFO storage buffer
Quaternion q; //[w,x, y, z] quaternion container, for orientation and motion
VectorFloat gravity; // [x, y, z], gravity vector
float ypr[3]; // [yaw, pitch, roll]
volatile bool mpuInterrupt = false;
void dmpDataReady() {
  mpuInterrupt = true;
}
void Sensor_Setup(MPU6050& mpu) {
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
    //initialize device
    mpu.initialize();
    //load and configure the DMP
    devStatus = mpu.dmpInitialize();
    //make sure it work
    if (devStatus == 0) {
      mpu.setDMPEnabled(true);
      //enable Arduino interrupt detection
      attachInterrupt(0, dmpDataReady, RISING);
      // set our DMP Ready flag so the main loop() function knows it's okay to use it
      dmpReady = true;
      //get MDP packet size for later comparision
      packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
      Serial.print("MDP Initialization failed!");
    }
}

void Sensor_Read(MPU6050& mpu) {
  if(!dmpReady) return;
  //wait for MPU interrupt or extra packet(s) available
  while(!mpuInterrupt && fifoCount < packetSize) {
    ;
  }
  //reset interrupt flag and get INT_STATUS byte
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();
  fifoCount = mpu.getFIFOCount();
  //check for overflow
  if ((mpuIntStatus & 0x10) || fifoCount >= 1024) {
    mpu.resetFIFO();
  } else if (mpuIntStatus & 0x02) {//check DMP data ready interrupt
  //wait for correct avilable data length
  while(fifoCount < packetSize) fifoCount = mpu.getFIFOCount();  
  //read packet from FIFO
  mpu.getFIFOBytes(fifoBuffer, packetSize);
  fifoCount -= packetSize;
  mpu.dmpGetQuaternion(&q, fifoBuffer);
  mpu.dmpGetGravity(&gravity, &q);
  mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
  }
  //917 = [360 / ( 2 * Pi )] << 4
  Rpy.ROLL = ypr[2] * 917;
  Rpy.PITCH = ypr[1] * 917;
  Rpy.YAW = ypr[0] * 917;
  
}
