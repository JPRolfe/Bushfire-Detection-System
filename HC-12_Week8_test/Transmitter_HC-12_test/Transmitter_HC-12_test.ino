

#include <SoftwareSerial.h>
#include <DFRobot_DHT20.h>

int LMT86 = A3;
double A3_Read = 0;
float voltage = 0;
float Temperature = 0;


DFRobot_DHT20 dht20;

SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12
  while(dht20.begin()){
    Serial.println("Initialize sensor failed");
    delay(1000);
    }
  pinMode(13, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  while (HC12.available()) {        // If HC-12 has data
    Serial.write(HC12.read());      // Send the data to Serial monitor
  }

   A3_Read = analogRead(LMT86);
   voltage = A3_Read*5.2/(1024);


  float Temperature = (10.888 - sqrt(143.217468-13.88*voltage))/(-0.00694) + 30;
  String StrTemp = String(Temperature, 2);
  String StrDHT20T = String(dht20.getTemperature(), 2);
  Serial.write("LMT86T: "); Serial.write(StrTemp[0]); Serial.write(StrTemp[1]); Serial.write("\n");
  Serial.write("DHT20T: "); Serial.write(StrDHT20T[0]); Serial.write(StrDHT20T[1]); Serial.write("\n");
    if(Temperature >= 25){
      digitalWrite(13, HIGH);
  } else {
      digitalWrite(13, LOW);
  }
  HC12.write(StrTemp[0]);      // Send that data to HC-12
  HC12.write(StrTemp[1]);
  delay(1000); 
  }
