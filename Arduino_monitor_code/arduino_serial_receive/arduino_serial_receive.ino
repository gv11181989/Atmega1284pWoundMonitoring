#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

}

void loop() {
  unsigned int  dataX[4];
  unsigned int  dataY[4];
  unsigned int  dataZ[4];
  if (mySerial.available() == 12) {
    dataX[0] = mySerial.read();
    dataX[1] = mySerial.read();
    dataX[2] = mySerial.read();
    dataX[3] = mySerial.read();
    dataY[0] = mySerial.read();
    dataY[1] = mySerial.read();
    dataY[2] = mySerial.read();
    dataY[3] = mySerial.read();
    dataZ[0] = mySerial.read();
    dataZ[1] = mySerial.read();
    dataZ[2] = mySerial.read();
    dataZ[3] = mySerial.read();
    union u_tagx {
      byte bx[4];
      float fval;
      int ival;
    } u;
        union u_tagy {
      byte by[4];
      float fval;
      int ival;
    } v;
        union u_tagz {
      byte bz[4];
      float fval;
      int ival;
    } w;

    u.bx[0] = dataX[0];
    u.bx[1] = dataX[1];
    u.bx[2] = dataX[2];
    u.bx[3] = dataX[3];

    
    v.by[0] = dataY[0];
    v.by[1] = dataY[1];
    v.by[2] = dataY[2];
    v.by[3] = dataY[3];

    
    w.bz[0] = dataZ[0];
    w.bz[1] = dataZ[1];
    w.bz[2] = dataZ[2];
    w.bz[3] = dataZ[3];

    float outputX = u.fval;
    float outputY = v.fval;
    float outputZ = w.fval;
    Serial.print(outputX);
    Serial.print('\t');
    Serial.print(outputY);
    Serial.print('\t');
    Serial.print(outputZ);
    Serial.println('\n');
  }



}
