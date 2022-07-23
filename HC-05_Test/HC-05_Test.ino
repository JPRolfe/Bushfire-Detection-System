#include <SoftwareSerial.h>

SoftwareSerial HC05(8, 7); // HC-05 TX Pin, HC-05 RX Pin

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  HC05.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  HC05.write('J');
  //delay(1000);
}
