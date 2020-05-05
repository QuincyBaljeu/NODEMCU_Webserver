#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

#define DHT11_PIN D1

#define SSID "Haagdijk 43938C 2.4GHz"
#define PASSWORD "vier rode fietsende olifanten"

DHT dht11(DHT11_PIN, DHT11);
 
void setup() {
  Serial.begin(115200);

  //Setup for DHT11 Temp/Humi sensor
  pinMode(DHT11_PIN, INPUT);
  dht11.begin();

  //Setup for WiFi connection
  Serial.print("Conecting to ssid: ");
  Serial.print(SSID);

  WiFi.begin(SSID, PASSWORD);

  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("WiFi Connected!");
}


void loop() {
}
