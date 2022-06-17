/*|----------------------------------------------------------|*/
/*|Experimental example for eduroam connection 2021+ sketch  |*/
/*|Sketch wasn't tested, I am not more student, can't try    |*/
/*|Changes from @debsahu (Github) and  esp_wpa2 library ref. |*/
/*|Edited by: Martin Chlebovec (martinius96) and later modified by Zayyan|*/
/*|----------------------------------------------------------|*/

#include <WiFi.h> //Wifi library
#include "esp_wpa2.h" //wpa2 library for connections to Enterprise networks

#include "HTTPClient.h"
#include "base64.h"
#include "DHT.h"

//Identity for user with password related to his realm (organization)
//Available option of anonymous identity for federation of RADIUS servers or 1st Domain RADIUS servers
//This is credential for connecting to a WPA-Enterprise Wifi
#define EAP_PASSWORD  ""
#define EAP_ANONYMOUS_IDENTITY "bt19080@qmul.ac.uk" //anonymous@example.com, or you can use also nickname@example.com
#define EAP_IDENTITY "bt19080@qmul.ac.uk" //nickname@example.com, at some organizations should work nickname only without realm, but it is not recommended


#define DHTTYPE DHT22//The type of the DHT sensor that is used
#define DHTPIN 4// Defination of the GPIO Pin Associated to the ESP32

//SSID NAME
const char* ssid = "eduroam"; // eduroam SSID

//
String authUsername = "QMUL";
String authPassword = "";

float tempData() {
  // Initialize DHT22 Sensor
  DHT dht(DHTPIN, DHTTYPE);
  pinMode(DHTPIN, INPUT);
  dht.begin();  
  
  // Get the Temperature
  float temperature = dht.readTemperature();
  Serial.println(temperature);
  
  return temperature;
}

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.print(F("Connecting to network: "));
  Serial.println(ssid);
  WiFi.disconnect(true);  //disconnect form wifi to set new wifi connection
  WiFi.mode(WIFI_STA); //init wifi mode
  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_ANONYMOUS_IDENTITY, strlen(EAP_ANONYMOUS_IDENTITY));
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));
  esp_wifi_sta_wpa2_ent_enable();
  WiFi.begin(ssid); //connect to wifi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println("");
  Serial.println(F("WiFi is connected!"));
  Serial.println(F("IP address set: "));
  Serial.println(WiFi.localIP()); //print LAN IP
}
//main looping function that runs throughout
void loop() {
  //This 'if block' checks if wifi is connected, if not the function runs again after 30seconds
  if ((WiFi.status() == WL_CONNECTED)) { 
 
    HTTPClient http;
    //This is the URL for the temperature sensor API and needs to be set to the URL of the API. 
    //Only 'http://192.168.0.6:8000' needs to be changed to the temperature sensor API URL

    http.begin("http://192.168.0.6:8000");
    //Authorization Headers sent to the URL needs to converted to base64 format, thus the encoding. Not to be tinkered with
    //Unless authorization type from the API is changed
    String auth = base64::encode(authUsername + ":" + authPassword);
    http.addHeader("Authorization", "Basic " + auth);
    http.addHeader("Content-Type", "application/json");
    
    //This is the body of the actual post request. Whatever is returned from the sendPOST method is sent
    int httpCode = http.POST(sendPOST()); 
    //If there response from the API, it is printed and can be checked via the serial monitor on the Arduino IDE (Tools -> Serial Monitor)
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
    }
    //Else an error message is printed
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end();
  }
  //The program is run again after a short 30 seconds delay. 
  delay(30000);
 
}
//The function takes in output returned from tempData() and then encodes it in the string that is send to the API
String sendPOST(){
  float t = tempData();
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  //The Freeze ID needs to be changed from 1 to anything that it will display on the UI in the frontend
  String ptr = "{\"freeze_id\":\"1\", \"temperature\":\"";
  ptr += (int)t;
  ptr += "\"}";
  return ptr;
}
