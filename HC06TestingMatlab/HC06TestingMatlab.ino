#include <SoftwareSerial.h>

SoftwareSerial BTSerial (8,7);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Enter AT Commands");
  BTSerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(BTSerial.available()){
    Serial.write(BTSerial.read());
  }
  
  BTSerial.write("Hello");
  
}
