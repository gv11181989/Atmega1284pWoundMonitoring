#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <Wire.h>
#include <header.h>
#include <SPI.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h> // not used in this demo but required!

// i2c Motion sensor
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0(1000);

// SI7021 I2C address is 0x40(64)
#define si7021Addr 0x40
#define Baud 6

void setup()
{
  DDRB |= (1 << PB5);
  DDRA &= ~(1 << PA0);
  tempSensorSetup(si7021Addr);
  Uart0Setup(Baud);
  Uart1Setup(Baud);
  sleepModeSetup();

  lsm.begin();
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);
}

void loop()
{
  while ((PINA & (1 << PA0)) == (1 << PA0))
  {
    BleConfigMode();
  }

  for (int i = 0; i < 10; i++)
  {
    PORTB ^= (1 << PB5);
    delay(100);
    PORTB ^= (1 << PB5);
    delay(100);
  }
  // USART1_Transmit('A');
  // Temp sensor reading
  float tempSensor = tempReading(si7021Addr, 0xF3);

  // Motion sensor readings
  sensors_event_t accel, mag, gyro, temp;
  lsm.getEvent(&accel, &mag, &gyro, &temp);
  float X = (float(accel.acceleration.x));
  float Y = (float(accel.acceleration.y));
  float Z = (float(accel.acceleration.z));

  Uart0SendFloat(X);
  // delay(2);
  // Uart0SendFloat(Z);
  // delay(2);

  GoToSleep();
}
