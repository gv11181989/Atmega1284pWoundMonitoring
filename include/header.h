#pragma once

void tempSensorSetup(int i2cAddr);
float tempReading(int i2cAddr,int cmd);

void Uart0Setup (unsigned int baud);
void Uart1Setup (unsigned int baud);
void USART0_Transmit( unsigned char data );
unsigned char USART0_Receive( void );
void USART1_Transmit( unsigned char data );
unsigned char USART1_Receive( void );
void Uart0SendFloat(float data);
void Uart0SendString(String data);
void ArduinoToBle();
void BleToArduino();
void BleConfigMode();

void sleepModeSetup();
void GoToSleep();
void BleConfigurIntSetup();