#include <Arduino.h>
#include <DNSServer.h>
#include <esp_wifi.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"


//Pre reading on the fundamentals of captive portals https://textslashplain.com/2022/06/24/captive-portals/

DNSServer dnsServer;
AsyncWebServer server(80);

void setup(){ //the order of the code is really important and it is critical the the android workaround is after the dns and sofAP setup
  Serial.begin(460800);
  Serial.print("\n");

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(IPAddress(4, 3, 2, 1), IPAddress(4, 3, 2, 1), IPAddress(255, 255, 255, 0)); //samusung requires the IP to be in public space
  WiFi.softAP("captive", "12345678", 6, 0, 4); //2.4ghz channel 6, broadcast ssid (0), 4 max clients, FYI The SSID in SoftAP can't have a space in it.
  
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError); //not sure if this is neccacary
  dnsServer.setTTL(300); //set 5min client side cache for DNS
  dnsServer.start(53, "*", WiFi.softAPIP());


  //ampdu_rx_disable android workaround see https://github.com/espressif/arduino-esp32/issues/4423
  esp_wifi_stop();
  esp_wifi_deinit();

  wifi_init_config_t my_config = WIFI_INIT_CONFIG_DEFAULT();   //We use the default config ...
  my_config.ampdu_rx_enable = false;                           //... and modify only what we want.

  esp_wifi_init(&my_config); //set the new config
  esp_wifi_start(); //Restart WiFi
  delay(100); //this seems to be necessary don't ask me why

  //Required
  server.on("/connecttest.txt",[](AsyncWebServerRequest *request){request->redirect("http://logout.net/");}); //windows 11 captive portal workaround

  //Probabilly not Required, but might speed things up?
  server.on("/canonical.html",[](AsyncWebServerRequest *request){request->redirect("http://4.3.2.1/");}); //firefox captive portal call home
  server.on("/chrome-variations/seed",[](AsyncWebServerRequest *request){request->send(200);}); //chrome captive portal call home
  server.on("/redirect",[](AsyncWebServerRequest *request){request->redirect("http://4.3.2.1/");}); //microsoft redirect
  server.on("/success.txt",[](AsyncWebServerRequest *request){request->send(200);}); //firefox captive portal call home
  server.on("/wpad.dat",[](AsyncWebServerRequest *request){request->send(404);}); //Honestly don't understand what this is but a 404 stops win 10 keep calling this repetededly and panicing the esp32 :)
  server.on("/generate_204",[](AsyncWebServerRequest *request){request->redirect("http://4.3.2.1/");}); //chromium? android? captive portal redirect
  server.on("/service/update2/json",[](AsyncWebServerRequest *request){request->send(200);}); //firefox?
  server.on("/chat",[](AsyncWebServerRequest *request){request->send(404);}); //No stop asking Whatsapp, there is no internet connection

  //return 404 to webpage icon
  server.on("/favicon.ico",[](AsyncWebServerRequest *request){request->send(404);}); //webpage icon

  //Serve Basic HTML Page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "<!DOCTYPE html><html><head><title>Success</title></head><body><p>Hooray</p></body>");
    Serial.println("Served Basic HTML Page");
  });

  server.onNotFound([](AsyncWebServerRequest *request){
    request->redirect("http://4.3.2.1/");
    Serial.print("server.onnotfound ");
    Serial.print(request->host());       //This gives some insight into whatever was being requested
    Serial.print(request->url());
    Serial.print(" sent redirect to http://4.3.2.1/\n");
  });

  server.begin();


  Serial.print("\n");
  Serial.print("Startup Time:"); //should be somewhere between 300-350 for ESP32 D0WDQ6 chip
  Serial.println(millis());
  Serial.print("\n");
}

void loop(){
  dnsServer.processNextRequest();
}