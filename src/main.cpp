#include <avr/io.h>
#include <avr/sleep.h>
#include <Wire.h>
#include <header.h>

// SI7021 I2C address is 0x40(64)
#define si7021Addr 0x40
#define Baud 51

void setup()
{
  DDRB |= (1 << PB5);
  i2cSetup(si7021Addr);
  Uart0Setup(Baud);
  Uart1Setup(Baud);
  sleepModeSetup();
}

void loop()
{
  PORTB |= (1 << PB5);
  delay(500);
  PORTB &= ~(1 << PB5);
  delay(500);
  PORTB |= (1 << PB5);
  delay(500);
  PORTB &= ~(1 << PB5);

  // float tempSensor = i2cReading(si7021Addr, 0xF3);
  // float celsTemp = ((175.72 * tempSensor) / 65536.0) - 46.85;
  /*
    byte * b = (byte *) &celsTemp;
    mcuTx (b[0]);
    mcuTx (b[1]);
    mcuTx (b[2]);
    mcuTx (b[3]);
    delay(1000);
  */
  //ATcommandBLE();

  GoToSleep();
}
