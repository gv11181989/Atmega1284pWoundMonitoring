#include <avr/io.h>
#include <avr/sleep.h>
#include <Wire.h>

class temperatureSensor
{

  int i2cAddr;
  int cmd;
  float celsTemp;

public:
  void Setup(int Addr)
  {
    i2cAddr = Addr;
    Wire.begin();
    Wire.beginTransmission(i2cAddr);
    Wire.endTransmission();
    delay(8);
  }

  float Read(int command)
  {
    cmd = command;
    unsigned int data[2];

    Wire.beginTransmission(i2cAddr);
    // Send measurement command
    Wire.write(cmd);
    Wire.endTransmission();
    delay(32);

    // Request 2 bytes of data
    Wire.requestFrom(i2cAddr, 2);

    // Read 2 bytes of data
    if (Wire.available() == 2)
    {
      data[0] = Wire.read();
      data[1] = Wire.read();
    }
    // Convert the data
    float outPut = ((data[0] * 256.0) + data[1]);
    float celsTemp = ((175.72 * outPut) / 65536.0) - 46.85;
    return celsTemp;
  }
};

class accelerometer
{
  int i2cAddr;
  int cmd;
  float X_out, Y_out, Z_out;

public:
  void Setup(int Addr)
  {
    i2cAddr = Addr;
    Wire.begin(); // Initiate the Wire library
    // Set ADXL345 in measuring mode
    Wire.beginTransmission(i2cAddr); // Start communicating with the device
    Wire.write(0x2D);                // Access/ talk to POWER_CTL Register - 0x2D
    // Enable measurement
    Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable
    Wire.endTransmission();
    delay(10);
    Wire.beginTransmission(i2cAddr); // Start communicating with the device
    Wire.write(0x31);                //range
    Wire.write(1);                   // range +-8g
    Wire.endTransmission();
    delay(10);
    // This code goes in the SETUP section
    // Off-set Calibration
    //X-axis
    Wire.beginTransmission(i2cAddr);
    Wire.write(0x1E); // X-axis offset register
    Wire.write(4);
    Wire.endTransmission();
    delay(10);
    //Y-axis
    Wire.beginTransmission(i2cAddr);
    Wire.write(0x1F); // Y-axis offset register
    Wire.write(-3);
    Wire.endTransmission();
    delay(10);

    //Z-axis
    Wire.beginTransmission(i2cAddr);
    Wire.write(0x20); // Z-axis offset register
    Wire.write(2);
    Wire.endTransmission();
    delay(10);
  }

  void Read(int command)
  {
    cmd = command;
    // === Read accelerometer data === //
    Wire.beginTransmission(i2cAddr);
    Wire.write(cmd); // Start with register 0x32 (ACCEL_XOUT_H)
    Wire.endTransmission();
    Wire.requestFrom(i2cAddr, 6, true);       // Read 6 registers total, each axis value is stored in 2 registers
    X_out = (Wire.read() | Wire.read() << 8); // X-axis value
    X_out = X_out / 128;                      //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
    Y_out = (Wire.read() | Wire.read() << 8); // Y-axis value
    Y_out = Y_out / 128;
    Z_out = (Wire.read() | Wire.read() << 8); // Z-axis value
    Z_out = Z_out / 128;
  }
  float X()
  {
    return X_out;
  }
  float Y()
  {
    return Y_out;
  }
  float Z()
  {
    return Z_out;
  }
};