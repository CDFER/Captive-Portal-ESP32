#include <Arduino.h>
#include <DNSServer.h>
#include <esp_wifi.h> //Used for mpdu_rx_disable android workaround
#include <WiFi.h>
#include <AsyncTCP.h> 	//https://github.com/me-no-dev/AsyncTCP using the latest dev version from @me-no-dev
#include <ESPAsyncWebServer.h> //ESP Async WebServer using the latest stable version from @me-no-dev

#define DEBUG_SERIAL if(USE_SERIAL)Serial //don't touch, enable serial in platformio.ini


// Dependency Graph
// |-- AsyncTCP @ 1.1.1+sha.ca8ac5f
// |-- ESP Async WebServer @ 1.2.3
// |   |-- AsyncTCP @ 1.1.1+sha.ca8ac5f
// |   |-- FS @ 2.0.0
// |   |-- WiFi @ 2.0.0
// |-- DNSServer @ 2.0.0
// |   |-- WiFi @ 2.0.0
// |-- WiFi @ 2.0.0

//Pre reading on the fundamentals of captive portals https://textslashplain.com/2022/06/24/captive-portals/

DNSServer dnsServer;
AsyncWebServer server(80);

void setup(){ //the order of the code is really important and it is critical the the android workaround is after the dns and sofAP setup

  #if USE_SERIAL == true
  Serial.begin(115200);
  while (!Serial);
  Serial.println("\n\nCaptive Test, compiled " __DATE__ " " __TIME__ "by CD_FER");
  #endif

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(IPAddress(4, 3, 2, 1), IPAddress(4, 3, 2, 1), IPAddress(255, 255, 255, 0)); //Samsung requires the IP to be in public space
  WiFi.softAP("captive", "12345678", 6, 0, 4); //2.4ghz channel 6, do broadcast SSID (0), 4 max clients, FYI The SSID in SoftAP can't have a space in it.
  
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError); //not sure if this is necessary
  dnsServer.setTTL(300); //set 5min client side cache for DNS
  // if DNSServer is started with "*" for domain name, it will reply with provided IP to all DNS request
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

  //Probably not Required, but might speed things up?
  server.on("/canonical.html",[](AsyncWebServerRequest *request){request->redirect("http://4.3.2.1/");}); //firefox captive portal call home
  server.on("/chrome-variations/seed",[](AsyncWebServerRequest *request){request->send(200);}); //chrome captive portal call home
  server.on("/redirect",[](AsyncWebServerRequest *request){request->redirect("http://4.3.2.1/");}); //microsoft redirect
  server.on("/success.txt",[](AsyncWebServerRequest *request){request->send(200);}); //firefox captive portal call home
  server.on("/wpad.dat",[](AsyncWebServerRequest *request){request->send(404);}); //Honestly don't understand what this is but a 404 stops win 10 keep calling this repeatedly and panicking the esp32 :)
  server.on("/generate_204",[](AsyncWebServerRequest *request){request->redirect("http://4.3.2.1/");}); //chromium? android? captive portal redirect
  server.on("/service/update2/json",[](AsyncWebServerRequest *request){request->send(200);}); //firefox?
  server.on("/chat",[](AsyncWebServerRequest *request){request->send(404);}); //No stop asking Whatsapp, there is no internet connection

  //return 404 to webpage icon
  server.on("/favicon.ico",[](AsyncWebServerRequest *request){request->send(404);}); //webpage icon

  //Serve Basic HTML Page WARNING IOS (and maybe macos) WILL NOT POP UP IF THIS PAGE CONTAINS THE WORD "Success" https://www.esp8266.com/viewtopic.php?f=34&t=4398
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse(200, "text/html", "<!DOCTYPE html><html><head><title>ESP32 Captive Portal</title></head><body><p>This is a captive portal example. All requests will "
  "be redirected here.</p></body>");
    response->addHeader("Cache-Control", "public,max-age=31536000");
    request->send(response);
    DEBUG_SERIAL.println("Served Basic HTML Page with 1 year Cache header");
  });

  server.onNotFound([](AsyncWebServerRequest *request){
    request->redirect("http://4.3.2.1/");
    DEBUG_SERIAL.print("server.onnotfound ");
    DEBUG_SERIAL.print(request->host());       //This gives some insight into whatever was being requested on the serial monitor
    DEBUG_SERIAL.print(request->url());
    DEBUG_SERIAL.print(" sent redirect to http://4.3.2.1/\n");
  });

  server.begin();

  DEBUG_SERIAL.print("\n");
  DEBUG_SERIAL.print("Startup Time:"); //should be somewhere between 270-350 for Generic ESP32 (D0WDQ6 chip, can have a higher startup time on first boot)
  DEBUG_SERIAL.println(millis());
  DEBUG_SERIAL.print("\n");
}

void loop(){
  dnsServer.processNextRequest();
}