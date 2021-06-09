//Arduino Mega
//Multiple Serial
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);
//SoftwareSerial mySerial1(4, 5);


void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  mySerial.begin(9600);
//  mySerial1.begin(9600);
}

void loop() {


  String output = "";
  while (Serial.available() > 0) {
    delay(2);
    char serialByte = Serial.read();
//  if (serialByte != '\n' && serialByte != '\r')
//   {
      output += serialByte;
//    }
  }
  char bytes[output.length() + 1];
  output.toCharArray(bytes, output.length() + 1);
  for (int i = 0; i < (output.length()); i++) {
    delay(2);
    mySerial.write(bytes[i]);
  }

  while (mySerial.available()) {
    char reply = mySerial.read();
    Serial.print(reply);
  }
  


}
