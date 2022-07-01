/*!
 *@file getData.ino
 *@brief Read ambient temperature and relative humidity and print them to serial port.
 *@copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 *@licence     The MIT License (MIT)
 *@author [fengli](li.feng@dfrobot.com)
 *@version  V1.0
 *@date  2021-6-24
 *@get from https://www.dfrobot.com
 *@https://github.com/DFRobot/DFRobot_DHT20
*/

#include <DFRobot_DHT20.h>
/*!
 * @brief Construct the function
 * @param pWire IC bus pointer object and construction device, can both pass or not pass parameters, Wire in default.
 * @param address Chip IIC address, 0x38 in default.
 */
int LMT86 = A3;
double A3_Read = 0;
float LMT86_Voltage = 0;
float LMT86_Temperature = 0;

DFRobot_DHT20 dht20;

void setup(){
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  //Initialize sensor
  while(dht20.begin()){
    Serial.println("Initialize sensor failed");
    delay(1000);
  }
}

void loop(){
  //Get ambient temperature
  A3_Read = analogRead(LMT86);
  LMT86_Voltage = A3_Read*5.2/(1024);
  
  int DHT20_Temperature = dht20.getTemperature();
  float LMT86_Temperature = (10.888 - sqrt(143.217468-13.88*LMT86_Voltage))/(-0.00694) + 30;

  if(LMT86_Temperature >= 25.00){
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }

  //Print relative humidity
  Serial.print("humidity: "); Serial.print(dht20.getHumidity()*100);Serial.println(" %RH");
  //Print DHT20 Temperature
  Serial.print("dht20 temperature: "); Serial.print(dht20.getTemperature());Serial.print("C\n");
  //Print LMT86 Temperature
  Serial.print("LMT86 Temperature: "); Serial.print(LMT86_Temperature); Serial.println("C");
  
  delay(1000); 
    
}
