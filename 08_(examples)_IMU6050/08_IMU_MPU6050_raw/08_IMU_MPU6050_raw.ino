//GND - GND
//VCC - VCC
// ARDUINO UNO  SDA-Pin A4    SCL-Pin A5
// ARDUINO MEGA SDA-Pin 20    SCL-Pin 21

// These two libraries at https://github.com/AritroMukherjee/MPU5060sensor
#include "I2Cdev.h"
#include "MPU6050.h"

#include "Wire.h"
 
const int mpuAddress = 0x69;  //Puede ser 0x68 o 0x69 (PORT_0)
MPU6050 mpu(mpuAddress);
 
int ax, ay, az;
int gx, gy, gz;
 
void printTab()
{
   Serial.print(F("\t"));
}
 
void printRAW()
{
   Serial.print(F("a[x y z] g[x y z]:\t"));
   Serial.print(ax); printTab();
   Serial.print(ay); printTab();
   Serial.print(az); printTab(); printTab();
   Serial.print(gx); printTab();
   Serial.print(gy); printTab();
   Serial.println(gz);
}
 
void setup()
{
   Serial.begin(115200);
   Wire.begin();
   mpu.initialize();
   Serial.println(mpu.testConnection() ? F("IMU iniciado correctamente") : F("Error al iniciar IMU"));
}
 
void loop()
{
   // Leer las aceleraciones y velocidades angulares
   mpu.getAcceleration(&ax, &ay, &az);
   mpu.getRotation(&gx, &gy, &gz);
 
   printRAW();
   
   delay(100);
}
