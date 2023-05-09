#include "BluetoothSerial.h"
#include <DHT.h>
#define AOUT_PIN 27 //soil moisture sensor - 3.3v
DHT dht(26, DHT22); //DHT22 sensor - 5v
BluetoothSerial serialBT;

void setup() {
  Serial.begin(115200);
  serialBT.begin("ESP32-BT");
  dht.begin();
  pinMode(2, OUTPUT);
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int soil = analogRead(AOUT_PIN);
  int soilMin = 1350; //when submerged in water
  int soilMax = 2825; //when dry

  if(soil > soilMax){
    soil = soilMax;
  }
  if(soil < soilMin){
    soil = soilMin;
  }
  
  int soilPercentage = map(soil, 2825, 1350, 0, 100);

  //print to Serial
  // Serial.print("Temp: ");
  // Serial.println(temp);
  // Serial.print("Hum: ");
  // Serial.println(hum);
  // Serial.print("Soil :");
  // Serial.println(soilPercentage);

  //print to serialBT
  serialBT.print("Temp: ");
  serialBT.print(temp);
  serialBT.print("°C");
  serialBT.print('\n');  
  serialBT.print("Vlaga: ");
  serialBT.print(hum);
  serialBT.print("%");
  serialBT.print('\n');  
  serialBT.print("Vlažnost: ");
  serialBT.print(soilPercentage);
  serialBT.print("%");
  serialBT.print('\n');  
  serialBT.print("---------------------------------");  
  serialBT.print('\n');  

  delay(1000);
}
