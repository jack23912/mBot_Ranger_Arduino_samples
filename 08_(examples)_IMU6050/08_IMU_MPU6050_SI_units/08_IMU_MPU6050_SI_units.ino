//GND - GND
//VCC - VCC
// ARDUINO UNO  SDA-Pin A4    SCL-Pin A5
// ARDUINO MEGA SDA-Pin 20    SCL-Pin 21

// These two libraries at https://github.com/AritroMukherjee/MPU5060sensor
#include "I2Cdev.h"
#include "MPU6050.h"

#include "Wire.h"
 
const int mpuAddress = 0x69;  // Puede ser 0x68 o 0x69
MPU6050 mpu(mpuAddress);
 
int ax, ay, az;
int gx, gy, gz;
 
 
// Factores de conversion
const float accScale = 2.0 * 9.81 / 32768.0; // For units m/s2
const float gyroScale = 250.0 / 32768.0; // For units deg/s2
const float gScale = 2.0 / 32768.0; // For units 'g'
 
void printTab()
{
   Serial.print(F("\t"));
}
 
// Mostrar medidas en Sistema Internacional
void printRAW()
{
   //Serial.print(F("a[x y z](m/s2):\t"));
   //Serial.print(ax * accScale); printTab();
   //Serial.print(ay * accScale); printTab();
   //Serial.print(az * accScale); printTab();

   Serial.print(F("a[x y z](g's):\t"));
   Serial.print(ax * gScale); printTab();
   Serial.print(ay * gScale); printTab();
   Serial.print(az * gScale + 1.2); printTab();  // Substract gravity force
   
   Serial.print(F("\t g[x y z](deg/s2):\t"));
   Serial.print(gx * gyroScale);  printTab();
   Serial.print(gy * gyroScale);  printTab();
   Serial.println(gz * accScale);
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
