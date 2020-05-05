#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

//Pin definitions
#define DHT11_PIN D1

//WiFi settings
#define SSID "Haagdijk 43938C 2.4GHz"
#define PASSWORD "vier rode fietsende olifanten"

//Object creation
DHT dht11(DHT11_PIN, DHT11);
ESP8266WebServer server(80);

//Attribute initialization
float temperature;
float humidity;
 
void setup() {
  Serial.begin(115200);

  //Setup for DHT11 Temp/Humi sensor
  pinMode(DHT11_PIN, INPUT);
  dht11.begin();

  //Setup for WiFi connection
  Serial.println("Conecting to ssid: ");
  Serial.print(SSID);

  WiFi.begin(SSID, PASSWORD);

  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("WiFi Connected!");
  Serial.print("IP: ");
  Serial.print(WiFi.localIP());

  server.on("/", handleOnConnect);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void handleOnConnect(){
  temperature = dht11.readTemperature();
  humidity = dht11.readHumidity();
  server.send(200, "text/html", getHTML(temperature, humidity));
}

void handleNotFound(){
  server.send(404, "text/plain", "Not found");
}

String getHTML(float temperature, float humidity){
  String HTML = "<!DOCTYPE html> <html>\n";
  HTML +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  HTML +="<titleNODEMCU DHT11 Reading</title>\n";
  HTML +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  HTML +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  HTML +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  HTML +="</style>\n";
  
  HTML +="<script>\n";
  HTML +="setInterval(loadDoc,200);\n";
  HTML +="function loadDoc() {\n";
  HTML +="var xhttp = new XMLHttpRequest();\n";
  HTML +="xhttp.onreadystatechange = function() {\n";
  HTML +="if (this.readyState == 4 && this.status == 200) {\n";
  HTML +="document.getElementById(\"webpage\").innerHTML =this.responseText}\n";
  HTML +="};\n";
  HTML +="xhttp.open(\"GET\", \"/\", true);\n";
  HTML +="xhttp.send();\n";
  HTML +="}\n";
  HTML +="</script>\n";
  
  HTML +="</head>\n";
  HTML +="<body>\n";
  HTML +="<div id=\"webpage\">\n";
  HTML +="<h1>NodeMCU DHT11 readings:</h1>\n";
  
  HTML +="<p>Temperature: ";
  HTML +=(int)temperature;
  HTML +="°C</p>";
  HTML +="<p>Humidity: ";
  HTML +=(int)humidity;
  HTML +="%</p>";
  
  HTML +="</div>\n";
  HTML +="</body>\n";
  HTML +="</html>\n";
  return HTML;
  
}

void loop() {
  server.handleClient();
}
