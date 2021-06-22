#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <Wire.h>
# include <header.h>

void sleepModeSetup()
{
  EICRA |= (1 << ISC21) | (1 << ISC20); // interrupt on rising edge of INT0
}

void GoToSleep()
{

  for (int i = 0; i < 2; i++)
  {
    MCUSR = 0; // reset various flags
    WDTCSR |= (1 << WDCE) | (1 << WDE);
    WDTCSR = (1 << WDIE) | (0 << WDE) | (1 << WDP3) | (1 << WDP0); // 8s / interrupt, no system reset
    wdt_reset();

    // EIMSK |= (1 << INT2); // external interrupt enable on INT2

    SMCR |= (1 << SM1); // power down sleep mode
    cli();
    SMCR |= (1 << SE); // sleep_enable();

    // power_adc_disable();
    // power_usart0_disable();
    // power_spi_disable();
    // power_timer0_disable();
    // power_timer1_disable();
    // power_timer2_disable();
    // power_twi_disable();

    sei();
    sleep_cpu();        // sleep_cpu();
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
  while (timeNow + 2 > millis())
    ;
  timeNow = millis();
  Uart1SendString("AT+SLEEP");
  while (timeNow + 500 > millis())
    ;
}