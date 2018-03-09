/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * @file    GyroRotation.ino
 * @author  MakeBlock
 * @version V1.0.0
 * @date    2015/09/09
 * @brief   Description: this file is sample code for MeGyro device.
 *
 * Function List:
 * 1. void MeGyro::begin(void)
 * 2. void MeGyro::update(void) 
 * 3. double MeGyro::angleX(void)
 * 4. double MeGyro::angleY(void)
 * 5. double MeGyro::angleZ(void)
 *
 * \par History:
 * <pre>
 * <Author>     <Time>        <Version>      <Descr>
 * Mark Yan     2015/09/09    1.0.0          rebuild the old lib
 * </pre>
 *
 */
#include "MeAuriga.h"
#include <Wire.h>

// Test the IMU 
MeGyro gyro_0(0, 0x69); //PORT0, Address 0x69


void setup()
{
  Serial.begin(115200);
  gyro_0.begin();       //Comunicacion I2C con gyro
}

void loop()
{
  gyro_0.update();
  Serial.read();

  // Serial.print("  X (getAngle(1)):");
  // Serial.print(gyro_0.getAngle(1)); //X: 1, Y:2, Z:3

  Serial.print("X:");
  Serial.print(gyro_0.getAngleX() );
  Serial.print("\tY:");
  Serial.print(gyro_0.getAngleY() );
  Serial.print("\tZ:");
  Serial.print(gyro_0.getAngleZ() );
  Serial.print("\t\tX acceleration:");
  Serial.print(gyro_0.getGyroX() );
  Serial.print("\tY acceleration:");
  Serial.println(gyro_0.getGyroY() );
  delay(100);
}

