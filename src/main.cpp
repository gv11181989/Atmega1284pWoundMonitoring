#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <Wire.h>
#include <header.h>
#include <CircularBuffer.h>
#include "Sensors.cpp"
#include "model.h"

Eloquent::ML::Port::RVC clf;

// SI7021 I2C address is 0x40(64)
#define si7021 0x40
// ADXL345 I2C address is 0x53(64)
#define ADXL345 0x53

accelerometer Accelerometer;
temperatureSensor Temp;

#define Baud 103
unsigned long timeNow = 0;

CircularBuffer<float, 4> tempData;
CircularBuffer<float, 45> motionData;
CircularBuffer<float, 5> Xnorm;
CircularBuffer<float, 5> Ynorm;
CircularBuffer<float, 5> Znorm;

void setup()
{
  // CLKPR &= ~(1 << CLKPS0);
  // delay(10);
  // CLKPR |= (1 << CLKPCE);

  // DDRA &= ~(1 << PA0);
  DDRB = 0;
  DDRA = 0;
  DDRC = 0;
  // DDRD = 0;

  PINA = 0xFF;
  PINC = 0xFF;
  PINB = 0xFF;
  // PIND = 0xFF;

  // disable ADC
  ADCSRA = 0;

  PRR0 = 0xFF;
  PRR0 &= ~(1 << PRTIM0);
  PRR0 &= ~(1 << PRUSART1);
  PRR0 &= ~(1 << PRTWI);
  PRR1 |= (1 << PRTIM3);
  MCUCR |= (1 << JTD);

  Temp.Setup(si7021);
  Accelerometer.Setup(ADXL345);

  // Uart0Setup(Baud);
  Uart1Setup(Baud);

  sleepModeSetup();
  // Put BLE to Sleep
  // BleSleep();
}

void loop()
{
  while ((PINA & (1 << PA0)) == (1 << PA0))
  {
    BleConfigMode();
  }

  // Temp sensor reading
  float tempSensor = Temp.Read(0xF3);
  tempData.push(tempSensor);

  // Calculation normalisation factor
  for (int i = 0; i < 5; i++)
  {
    Accelerometer.Read(0x32);
    float X = Accelerometer.X();
    Xnorm.push(X);

    float Y = Accelerometer.Y();
    Ynorm.push(Y);

    float Z = Accelerometer.Z();
    Znorm.push(Z);
    delay(50);
  }
  float avgx = 0;
  float avgy = 0;
  float avgz = 0;
  using index_t = decltype(Xnorm)::index_t;
  for (index_t i = 0; i < Xnorm.size(); i++)
  {
    avgx += Xnorm[i] / Xnorm.size();
    avgy += Ynorm[i] / Ynorm.size();
    avgz += Znorm[i] / Znorm.size();
  }

  // Storing normalized Motion sensor data in a buffer of size 45.
  for (int i = 0; i < 5; i++)
  {
    // Motion sensor readings
    Accelerometer.Read(0x32);

    float X = Accelerometer.X() - avgx;
    motionData.push(X);

    float Y = Accelerometer.Y() - avgy;
    motionData.push(Y);

    float Z = Accelerometer.Z() - avgz;
    motionData.push(Z);
    delay(500);
  }

  // calculating average temp of temperature buffer
  float avg_temp = 0;
  using index_t = decltype(tempData)::index_t;
  for (index_t i = 0; i < tempData.size(); i++)
  {
    avg_temp += tempData[i] / tempData.size();
  }

  // trigerring ML inference if Temp rises above a threshhold
  if (avg_temp >= 37.4)
  {
    int test = clf.predict(motionData);
    Uart1SendString("AT");
    delay(100);
    if (test == 0)
    {
      Uart1SendString("motion \n");
    }
    else
    {
      Uart1SendString("rest \n");
    }
  }
  delay(10);
  // Put MCU to Sleep
  BleSleep();
  GoToSleep();
}
