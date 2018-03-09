#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"
/* 
 *  En este ejemplo empleamos el DMP integrado en el MPU-6050 para realizar la combinación
 *  de la medición del acelerómetro y el giroscopio, lo que proporciona mejor resultados
 *  que emplear un filtro complementario, y además libera a Arduino del proceso de cálculo.
 * CON RANGER DA ERROR AL INICIAR EL DMP
 */
const int mpuAddress = 0x68;  // Puede ser 0x68 o 0x69
MPU6050 mpu(mpuAddress);
 
bool dmpReady = false; 
uint8_t mpuIntStatus;  
uint8_t devStatus;     
uint16_t packetSize;   
uint16_t fifoCount;    
uint8_t fifoBuffer[64];
 
Quaternion q;           // [w, x, y, z]         quaternion
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
 
volatile bool mpuInterrupt = false;
void dmpDataReady() 
{
   mpuInterrupt = true;
}
 
void setup()
{
   Wire.begin();
   TWBR = 24; 
 
   Serial.begin(115200);
   mpu.initialize();
   Serial.println(mpu.testConnection() ? F("IMU iniciado correctamente") : F("Error al iniciar IMU"));
 
   devStatus = mpu.dmpInitialize();
 
   // Valores de calibración
   mpu.setXGyroOffset(220);
   mpu.setYGyroOffset(76);
   mpu.setZGyroOffset(-85);
   mpu.setZAccelOffset(1788);
 
   if (devStatus == 0)
   {
      Serial.println(F("Activando DMP..."));
      mpu.setDMPEnabled(true);
 
      attachInterrupt(0, dmpDataReady, RISING);
      mpuIntStatus = mpu.getIntStatus();
      dmpReady = true;
      packetSize = mpu.dmpGetFIFOPacketSize();
   }
   else 
   {
      Serial.print(F("Fallo inicialización DMP"));
   }
 
}
 
void loop() 
{
   
   if (!dmpReady) return;
 
   // Esperar a la interrupción, o mientras queden datos por leer
   while (!mpuInterrupt && fifoCount < packetSize)
   {
      // AQUI EL RESTO DE ACCIONES DE TU PROGRAMA
   }
 
   mpuInterrupt = false;
   mpuIntStatus = mpu.getIntStatus();
   fifoCount = mpu.getFIFOCount();
 
   // Comprobar overflow
   if ((mpuIntStatus & 0x10) || fifoCount == 1024)
   {
      // Reset FIFO
      mpu.resetFIFO();
      Serial.println(F("FIFO overflow!"));
   }
   else if (mpuIntStatus & 0x02) 
   {
      // Esperar datos
      while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
 
      // Leer paquete de FIFO
      mpu.getFIFOBytes(fifoBuffer, packetSize);
      fifoCount -= packetSize;
 
      // Mostrar angulos euler
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
 
      Serial.print("ypr\t");
      Serial.print(ypr[0] * 180 / M_PI);
      Serial.print("\t");
      Serial.print(ypr[1] * 180 / M_PI);
      Serial.print("\t");
      Serial.println(ypr[2] * 180 / M_PI);
 
      // Mostar las aceleracinones corregidas
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetAccel(&aa, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
      mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
 
      Serial.print("aworld\t");
      Serial.print(aaWorld.x);
      Serial.print("\t");
      Serial.print(aaWorld.y);
      Serial.print("\t");
      Serial.println(aaWorld.z);
   }
}
