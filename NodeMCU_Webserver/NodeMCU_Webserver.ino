#include "DHT.h"

#define DHT11_PIN D1

DHT dht11(DHT11_PIN, DHT11);
 
void setup() {
  Serial.begin(115200);

  pinMode(DHT11_PIN, INPUT);
  dht11.begin();
}


void loop() {

  Serial.print("TEMP");
  Serial.print(dht11.readTemperature());
  Serial.println();
  Serial.print("HUM");
  Serial.print(dht11.readHumidity());
  delay(1000);
}
