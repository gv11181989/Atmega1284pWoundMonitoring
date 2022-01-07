#include <avr/io.h>
#include <avr/sleep.h>
#include <Wire.h>

void Uart0Setup(unsigned int baud)
{
  UCSR0A |= (1 << U2X0);
  UBRR0H = (baud >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
  UBRR0L = baud;        // Load lower 8-bits of the baud rate value into the low byte of the UBRR register
  // Enable RXD and TXD pins
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  // Set frame format: 8-bit, no parity, 1 stop bit.
  UCSR0C = (3 << UCSZ00);
}

void Uart1Setup(unsigned int baud)
{
  UCSR1A |= (1 << U2X1);
  UBRR1H = (baud >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
  UBRR1L = baud;        // Load lower 8-bits of the baud rate value into the low byte of the UBRR register
  // Enable RXD and TXD pins
  UCSR1B = (1 << RXEN1) | (1 << TXEN1);
  // Set frame format: 8-bit, no parity, 1 stop bit.
  UCSR1C = (3 << UCSZ10);
}

void USART0_Transmit(unsigned char data)
{
  /* Wait for empty transmit buffer */
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  /* Put data into buffer, sends the data */
  delay(1);
  UDR0 = data;
}

unsigned char USART0_Receive(void)
{
  /* Wait for data to be received */
  while (!(UCSR0A & (1 << RXC0)))
    ;
  /* Get and return received data from buffer */
  return UDR0;
}

void USART1_Transmit(unsigned char data)
{
  /* Wait for empty transmit buffer */
  while (!(UCSR1A & (1 << UDRE1)))
    ;
  /* Put data into buffer, sends the data */
  // delay(1);
  UDR1 = data;
}
unsigned char USART1_Receive(void)
{
  /* Wait for data to be received */
  while (!(UCSR1A & (1 << RXC1)))
    ;
  /* Get and return received data from buffer */
  delay(1);
  return UDR1;
}

void USART1_Flush(void)
{
  unsigned char dummy;
  while (UCSR1A & (1 << RXC1))
    dummy = UDR1;
}

void Uart0SendFloat(float data)
{
  byte *b = (byte *)&data;
  USART0_Transmit(b[0]);
  USART0_Transmit(b[1]);
  USART0_Transmit(b[2]);
  USART0_Transmit(b[3]);
}

void Uart1SendFloat(float data)
{
  byte *b = (byte *)&data;
  USART1_Transmit(b[0]);
  USART1_Transmit(b[1]);
  USART1_Transmit(b[2]);
  USART1_Transmit(b[3]);
}

void Uart0SendString(String data)
{
  int i = 0;
  while (data[i] != 0x00)
  {
    USART0_Transmit(data[i]);
    i++;
  }
}

void Uart1SendString(String data)
{
  int i = 0;
  while (data[i] != 0x00)
  {
    USART1_Transmit(data[i]);
    i++;
  }
}

void ArduinoToBle()
{
  while (1)
  {

    /* Wait for data to be received */
    while (!(UCSR0A & (1 << RXC0)))
    {
    }
    /* Get and return received data from buffer */
    char rx = UDR0;
    if (rx == '\n')
      break;
    if (rx == '\r')
      break;
    /* Wait for empty transmit buffer */
    while (!(UCSR1A & (1 << UDRE1)))
      ;
    /* Put data into buffer, sends the data */
    UDR1 = rx;
  }
}

void BleToArduino()
{
  char rx;
  int i = 0;
  PORTB ^= (1 << PB5);
  /* Wait for data to be received */
  while ((UCSR1A & (1 << RXC1)) == (1 << RXC1))
  {
    /* Get and return received data from buffer */
    rx = UDR1;
    USART0_Transmit(rx);
  }
}

void BleConfigMode()
{
  while ((PINA & (1 << PA0)) == (1 << PA0))
  {
    String data("\nBLE configure mode,Waiting for commands!!\n");
    Uart0SendString(data);
    delay(12);
    ArduinoToBle();
    delay(12);
    BleToArduino();
  }
}