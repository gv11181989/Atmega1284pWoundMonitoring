#pragma once

void i2cSetup(int i2cAddr);
float i2cReading(int i2cAddr,int cmd);

void Uart0Setup (unsigned int baud);
void Uart1Setup (unsigned int baud);

void sleepModeSetup();
void GoToSleep();
