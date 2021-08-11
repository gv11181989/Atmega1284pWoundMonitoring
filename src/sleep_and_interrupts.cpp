#include <avr/io.h>
// #include <avr/sleep.h>
#include <avr/wdt.h>
#include <Wire.h>
# include <header.h>

void sleepModeSetup()
{
  EICRA |= (1 << ISC21) | (1 << ISC20); // interrupt on rising edge of INT0
}

void GoToSleep()
{

  for (int i = 0; i < 1; i++)
  {
    
    MCUSR = 0; // reset various flags
    WDTCSR |= (1 << WDCE) | (1 << WDE);
    WDTCSR = (1 << WDIE) | (0 << WDE) | (1 << WDP3) | (1 << WDP0); // 8s / interrupt, no system reset
    wdt_reset();

    // EIMSK |= (1 << INT2); // external interrupt enable on INT2

    SMCR |= (1 << SM1); // power down sleep mode
    cli(); 

    // PRR0 = 0xFF;
    // PRR0 &= ~(1<<PRTIM0);
    // PRR1 |= (1<<PRTIM3);

    SMCR |= (1 << SE); // sleep_enable();
    sei();
    asm("SLEEP");        // sleep_cpu();
    SMCR &= ~(1 << SE); // sleep_disable();

    // power_all_enable();
  }
}

// INT2 interrupt service routine
ISR(INT2_vect)
{
  //  EIMSK &= ~(1<<INT2); // external interrupt disable (INT0)
}

// watchdog interrupt
ISR(WDT_vect)
{
  // wdt_disable(); // disable watchdog
}

void BleSleep()
{
  unsigned long timeNow = millis();
  Uart1SendString("AT");
  while (timeNow + 10 > millis())
    ;
  timeNow = millis();
  Uart1SendString("AT+SLEEP");
  while (timeNow + 500 > millis())
    ;
}