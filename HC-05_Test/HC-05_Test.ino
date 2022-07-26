#include <SoftwareSerial.h>

SoftwareSerial HC06(8, 7); // HC-05 TX Pin, HC-05 RX Pin

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  HC06.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    // Keep reading from HC-06 and send to Arduino Serial Monitor
    if (HC06.available())
    {  
        Serial.write(HC06.read());
    }
 
    // Keep reading from Arduino Serial Monitor and send to HC-06
    if (Serial.available())
    {
        HC06.write(Serial.read());
    }
}
