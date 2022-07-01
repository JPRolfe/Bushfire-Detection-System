#include <DFRobot_DHT20.h>

int LMT86 = A3;
double A3_Read = 0;
float voltage = 0;
float Temperature = 0;

DFRobot_DHT20 dht20;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
  while(dht20.begin()){
    Serial.println("Initialize sensor failed");
    delay(1000);
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  A3_Read = analogRead(LMT86);
  Serial.print("A3_Read: "); Serial.println(A3_Read);
  voltage = A3_Read*5.2/(1024);
  Serial.print("Voltage: "); Serial.print(voltage);
  Serial.println(" V");

  float Temperature = (10.888 - sqrt(143.217468-13.88*voltage))/(-0.00694) + 30;
  Serial.print("LMT86 Temperature: "); Serial.print(Temperature); Serial.println("C");
  Serial.print("dht20 temperature: "); Serial.print(dht20.getTemperature());Serial.print("C\n");
  delay(1000); 
  }
