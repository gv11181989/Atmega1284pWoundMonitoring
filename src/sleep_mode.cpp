#include <avr/io.h>
#include <avr/sleep.h>
#include <Wire.h>



void sleepModeSetup()
{
  EICRA |= (1 << ISC21) | (1 << ISC20); // interrupt on rising edge of INT0
}
void GoToSleep()
{

  EIMSK |= (1 << INT2); // external interrupt enable on INT2

  SMCR |= (1 << SM1); // power down sleep mode
  cli();
  SMCR |= (1 << SE); // sleep_enable();
  sei();
  asm("SLEEP");       // sleep_cpu();
  SMCR &= ~(1 << SE); // sleep_disable();
  // INT0 interrupt service routine
}
ISR(INT2_vect)
{
  //  EIMSK &= ~(1<<INT2); // external interrupt disable (INT0)
}
