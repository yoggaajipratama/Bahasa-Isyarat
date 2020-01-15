#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>

HTTPClient http;
ESP8266WebServer server(80);

const int flexPin = A0;
int value;
const String url = "http://192.168.43.53/Tuli/html/sensor.php?id=";
const char* ssid = "xyz";
const char* password = "098765432100";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  Serial.println("");
  while(WiFi.status() !=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Connected to :");
  Serial.println(WiFi.localIP());
  
  // server.on("/",[](){
  //   server.send(200, "text/html",homePage);
  // });

  // server.on("/url", handleRoot);

  
  server.begin();

}

void loop() {
  value = analogRead(flexPin);
  Serial.println(value);
  
  server.handleClient();
  delay(150);
  if(value<1000){
    http.begin(url + "2");
    int httpCode = http.GET();
    String payload = http.getString();
    Serial.println(payload);
    http.end();
    Serial.println("Running");
    delay(500);
  }else{
    http.begin(url + "0");
    int httpCode = http.GET();
    String payload = http.getString();
    Serial.println(payload);
    http.end();
    Serial.println("Stop");
  }
}
