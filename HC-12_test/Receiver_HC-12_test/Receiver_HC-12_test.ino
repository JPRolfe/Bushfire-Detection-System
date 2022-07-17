#include <SoftwareSerial.h>

SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin
char tempChar;
String LMT86Temperature;
String NewLMT86Temperature;

void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12
  pinMode(13, OUTPUT);
}

void loop() {
  while (HC12.available()) {        // If HC-12 has data
    //Serial.write(HC12.read());      // Send the data to Serial monitor
    tempChar = HC12.read();
    if(LMT86Temperature.length() < 2){
    LMT86Temperature += tempChar;
    } else {
      NewLMT86Temperature += tempChar;
      if(NewLMT86Temperature != LMT86Temperature){
        LMT86Temperature = NewLMT86Temperature;
        NewLMT86Temperature = "";
      }
    }
    if(LMT86Temperature.length() == 2){
      Serial.println(LMT86Temperature);
      Serial.print("data: "); Serial.println(LMT86Temperature.toInt());
      if(LMT86Temperature.toInt() >= 25){
      digitalWrite(13, HIGH);
      } else {
      digitalWrite(13, LOW);
      }
    }
  }
  while (Serial.available()) {      // If Serial monitor has data
    HC12.write(Serial.read());      // Send that data to HC-12
  }

 }
