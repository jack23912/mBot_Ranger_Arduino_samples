#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
/* 
 *  Este ejemplo empleamos un filtro complementario para combinar la señal del acelerómetro y giroscopio
 *  para obtener una mejor medición de la orientación del MPU-6050, como vimos en la entrada
 *  Medir la inclinación de un IMU con Arduino y filtro complementario:
 *  https://www.luisllamas.es/medir-la-inclinacion-imu-arduino-filtro-complementario/
 */
const int mpuAddress = 0x69;
MPU6050 mpu(mpuAddress);
 
int ax, ay, az;
int gx, gy, gz;
 
long tiempo_prev;
float dt;
float ang_x, ang_y;
float ang_x_prev, ang_y_prev;
 
void updateFiltered()
{
   dt = (millis() - tiempo_prev) / 1000.0;
   tiempo_prev = millis();
 
   //Calcular los ángulos con acelerometro
   float accel_ang_x = atan(ay / sqrt(pow(ax, 2) + pow(az, 2)))*(180.0 / 3.14);
   float accel_ang_y = atan(-ax / sqrt(pow(ay, 2) + pow(az, 2)))*(180.0 / 3.14);
 
   //Calcular angulo de rotación con giroscopio y filtro complementario
   ang_x = 0.98*(ang_x_prev + (gx / 131)*dt) + 0.02*accel_ang_x;
   ang_y = 0.98*(ang_y_prev + (gy / 131)*dt) + 0.02*accel_ang_y;
 
   ang_x_prev = ang_x;
   ang_y_prev = ang_y;
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
 
   updateFiltered();
 
   Serial.print(F("Rotacion en X:  "));
   Serial.print(ang_x);
   Serial.print(F("\t Rotacion en Y: "));
   Serial.println(ang_y);
 
   delay(10);
}
