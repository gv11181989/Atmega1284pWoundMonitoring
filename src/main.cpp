#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <Wire.h>
#include <header.h>
#include <CircularBuffer.h>
#include "Sensors.cpp"

// SI7021 I2C address is 0x40(64)
#define si7021 0x40
// ADXL345 I2C address is 0x53(64)
#define ADXL345 0x53

accelerometer Accelerometer;
temperatureSensor Temp;

#define Baud 12
unsigned long timeNow = 0;

CircularBuffer<float, 4> tempData;
CircularBuffer<float, 45> motionData;
// unsigned long timeNow = 0;

void setup()
{
  DDRA &= ~(1 << PA0);

  Temp.Setup(si7021);
  Accelerometer.Setup(ADXL345);

  Uart0Setup(Baud);
  Uart1Setup(Baud);

  sleepModeSetup();
  // Put BLE to Sleep
  // BleSleep();
}

void loop()
{
  // while ((PINA & (1 << PA0)) == (1 << PA0))
  // {
  //   BleConfigMode();
  // }

  // Temp sensor reading
  for (int i=0;i<5;i++){
  float tempSensor = Temp.Read(0xF3);
  tempData.push(tempSensor);

  // Motion sensor readings
  Accelerometer.Read(0x32);
  
  float X = Accelerometer.X();
  motionData.push(X);

  float Y = Accelerometer.Y();
  motionData.push(Y);

  float Z = Accelerometer.Z();
  motionData.push(Z);
  delay(100);
  }
  for (int i = 0; i < 45; i++)
  {
    Uart1SendFloat(motionData[i]);
    delay(5);
  }
  // Put MCU to Sleep
  GoToSleep();
}
