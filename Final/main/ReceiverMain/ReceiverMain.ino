#include <SoftwareSerial.h>

SoftwareSerial HC12(8, 7); // HC-12 TX Pin, HC-12 RX Pin

char tempChar;
String LMT86Temperature;
String DHTHumidity;
String SoilMoist;
int switcher = 0;

void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  while (HC12.available()) {        // If HC-12 has data (Receiving) 
    
     tempChar = HC12.read();                  // tempChar is collecting each character that has been received

     if(tempChar == 'L'){                     // Switching a variable to identify which sensor information is being read
      Serial.println(LMT86Temperature);
      switcher = 1;
      LMT86Temperature = "";
     }
     else if(tempChar == 'D'){
      Serial.println(DHTHumidity);
      switcher = 2;
      DHTHumidity = "";
     }
     else if(tempChar == 'H'){
      Serial.println(SoilMoist);
      switcher = 3;
      SoilMoist = "";
     }

     
     if(switcher == 1 && tempChar != 'L'){          // Records the sensor information being received into a variable.
       LMT86Temperature += tempChar;
     } 
     else  if(switcher == 2 && tempChar != 'D') {
      DHTHumidity += tempChar;
     }
     else if(switcher == 3 && tempChar != 'H'){
       SoilMoist += tempChar;
     }


     if(LMT86Temperature.toInt() >= 25){       // Turn on LED if temperature is above 25 degrees
      digitalWrite(13, HIGH);
     } else {
      digitalWrite(13, LOW);
     }
     
     if(DHTHumidity.toInt() >= 70){           // Turn on LED if relative humidity is above 70%
      digitalWrite(12, HIGH);
     } else {
      digitalWrite(12, LOW);
     }

  }
  while (Serial.available()) {      // If Serial monitor has data (Transmitting)
    HC12.write(Serial.read());      // Send that data to HC-12
  }

 }
