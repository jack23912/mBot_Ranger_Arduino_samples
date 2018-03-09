#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

/*
 * En el siguiente ejemplo, realizamos la integración de la señal de la velocidad del giroscopio para obtener 
 * la orientación del MPU-6050, como vimos en la entrada Cómo usar un giroscopio con Arduino.
 * https://www.luisllamas.es/como-usar-un-giroscopio-arduino/
 */
 
const int mpuAddress = 0x69;
MPU6050 mpu(mpuAddress);
 
int ax, ay, az;
int gx, gy, gz;
 
long tiempo_prev, dt;
float girosc_ang_x, girosc_ang_y;
float girosc_ang_x_prev, girosc_ang_y_prev;
 
void updateGiro()
{
   dt = millis() - tiempo_prev;
   tiempo_prev = millis();
 
   girosc_ang_x = (gx / 131)*dt / 1000.0 + girosc_ang_x_prev;
   girosc_ang_y = (gy / 131)*dt / 1000.0 + girosc_ang_y_prev;
 
   girosc_ang_x_prev = girosc_ang_x;
   girosc_ang_y_prev = girosc_ang_y;
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
   // Leer las velocidades angulares 
   mpu.getRotation(&gx, &gy, &gz);
 
   updateGiro();
 
   // Mostrar resultados
   Serial.print(F("Rotacion en X:  "));
   Serial.print(girosc_ang_x);
   Serial.print(F("\tRotacion en Y: "));
   Serial.println(girosc_ang_y);
 
   delay(10);
}
