

#include <SoftwareSerial.h>
#include <DFRobot_DHT20.h>

const int AirValue = 616;   //replace the value with value when placed in air using calibration code 
const int WaterValue = 335; //replace the value with value when placed in water using calibration code 

double A3_Read = 0;
double A2_Read =0;

float LMTvoltage = 0;
float LMTTemperature = 0;
char humidVal[2];
char soilVal[2];

DFRobot_DHT20 dht20;

SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600 );               // Serial port to HC12
  while(dht20.begin()){
    Serial.println("Initialize sensor failed");
    delay(1000);
    }
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (HC12.available()) {        // If HC-12 has data
    Serial.write(HC12.read());      // Send the data to Serial monitor
  }

   A3_Read = analogRead(A3);
   A2_Read = analogRead(A2);
   delay(10);
   //soilMoistureValue = analogRead(A2);
   
   LMTvoltage = (A3_Read*5)/1023;    // ( Analog_Reading * Power Supply Voltage ) / (ADC resolution)  --- Analog to Digital Conversion (10 bit ADC)
  
  float LMTTemperature = (10.888 - sqrt(143.217468-13.88*LMTvoltage))/(-0.00694) + 30;    // Equation to transform into Degrees Celsius from datasheet
  
<<<<<<< Updated upstream
  Serial.print("DHTHumidity: "); Serial.print(charVal[0]); Serial.println(charVal[1]);
  Serial.print("LMT86T: "); Serial.print(StrTemp[0]); Serial.println(StrTemp[1]); 
  Serial.print("DHTTemp: "); Serial.println(dht20.getTemperature());
  if(Temperature >= 25){        // If Temperature is > 25 Degrees Celsius, then turn on LED
=======
  String StrTemp = String(LMTTemperature, 2);
  itoa(round(dht20.getHumidity()*100), humidVal, 10);        // Int to String (Int, char Array, Base of the number so Decimal = 10 ).
  
  Serial.print("DHTHumidity: "); Serial.println(humidVal);
  Serial.print("LMT86T: "); Serial.println(StrTemp); 
  Serial.print("Soil: "); Serial.println(A2_Read);

  
  if(LMTTemperature >= 25){        // If Temperature is > 25 Degrees Celsius, then turn on LED
>>>>>>> Stashed changes
      digitalWrite(13, HIGH);
  } else {
      digitalWrite(13, LOW);
  }
  if(round(dht20.getHumidity()*100) >= 70){   // if Humidity is above 70% then turn on LED
      digitalWrite(12, HIGH);
  } else {
      digitalWrite(12, LOW);
  }
  
  HC12.write("L");
  HC12.write(StrTemp[0]); HC12.write(StrTemp[1]);      // Transmit the LMT Temperature Readings
  HC12.write("D");    
  HC12.write(humidVal[0]); HC12.write(humidVal[1]);      // Transmit the DHT20 Humidity Readings
  HC12.write("H");
  HC12.write(soilVal);
  
  delay(1000); 
  }
