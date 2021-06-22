#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <Wire.h>
#include <header.h>
#include <SPI.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>
#include <CircularBuffer.h>

// i2c Motion sensor
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0(1000);

// SI7021 I2C address is 0x40(64)
#define si7021Addr 0x40
#define Baud 12
unsigned long timeNow = 0;

CircularBuffer<float, 4> tempData;
CircularBuffer<float, 90> motionData;
// unsigned long timeNow = 0;

void setup()
{
  DDRA &= ~(1 << PA0);
  tempSensorSetup(si7021Addr);
  Uart0Setup(Baud);
  Uart1Setup(Baud);

  sleepModeSetup();

  lsm.begin();
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);

  // Put BLE to Sleep
  BleSleep();
}

void loop()
{
  // while ((PINA & (1 << PA0)) == (1 << PA0))
  // {
  //   BleConfigMode();
  // }

  

  // Temp sensor reading
  float tempSensor = tempReading(si7021Addr, 0xF3);
  tempData.push(tempSensor);

  // Motion sensor readings
  sensors_event_t accel, mag, gyro, temp;
  lsm.getEvent(&accel, &mag, &gyro, &temp);
  float X = (float(accel.acceleration.x));
  motionData.push(X);
  float Y = (float(accel.acceleration.y));
  motionData.push(Y);
  float Z = (float(accel.acceleration.z));
  motionData.push(Z);

  // Put MCU to Sleep
  // GoToSleep();
}
