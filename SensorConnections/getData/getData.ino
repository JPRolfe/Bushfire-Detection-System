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
int pinTemp = A0;
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
  
  int VoltTemp = analogRead(pinTemp);    //Read the analog pin
  int RealTemp = ((10.888 - sqrt((10.888)*(10.888) + 4*0.00347*(1777.3-VoltTemp)))/2*(-0.00347)) + 30;   // convert output (mv) to readable celcius
  int Temps = dht20.getTemperature();
  if(Temps >= 25.00){
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }
  //Serial.print("temperature:"); Serial.print(dht20.getTemperature());Serial.print("C");
  //Get relative humidity
  Serial.print("  humidity:"); Serial.print(dht20.getHumidity()*100);Serial.println(" %RH");
  Serial.print("Temperature: ");
  Serial.print(RealTemp);
  Serial.println("C");  //print the temperature status
  delay(1000);   delay(1000);

}
