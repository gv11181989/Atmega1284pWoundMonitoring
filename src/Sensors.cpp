#include <avr/io.h>
#include <avr/sleep.h>
#include <Wire.h>



void tempSensorSetup(int i2cAddr){
    
  Wire.begin();
  Wire.beginTransmission(i2cAddr);
  Wire.endTransmission();
  delay(300);
}


float tempReading(int i2cAddr,int cmd) {
  unsigned int data[2];

  Wire.beginTransmission(i2cAddr);
  // Send measurement command
  Wire.write(cmd);
  Wire.endTransmission();
  delay(500);

  // Request 2 bytes of data
  Wire.requestFrom(i2cAddr, 2);

  // Read 2 bytes of data
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }
    // Convert the data
  float outPut  = ((data[0] * 256.0) + data[1]);
  float celsTemp = ((175.72 * outPut) / 65536.0) - 46.85;
  return celsTemp;
  }

