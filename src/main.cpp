#include <Arduino.h>
#include <DNSServer.h>
#include <esp_wifi.h> //Used for mpdu_rx_disable android workaround
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

//Pre reading on the fundamentals of captive portals https://textslashplain.com/2022/06/24/captive-portals/

const char * ssid = "captive"; //FYI The SSID can't have a space in it.
const char * password = "12345678";

#define MAX_CLIENTS 4
#define WIFI_CHANNEL 6 //2.4ghz channel 6


const IPAddress localIP(4, 3, 2, 1); // the IP address the web server, Samsung requires the IP to be in public space
const IPAddress gatewayIP(4, 3, 2, 1); // IP address of the network
const IPAddress subnetMask(255,255,255,0);

const String localIPURL = "http://4.3.2.1";

const char index_html[] PROGMEM = R"=====(
  <!DOCTYPE html> <html>
    <head>
      <title>ESP32 Captive Portal</title>
      <style>
        body {background-color:#06cc13;}
        h1 {color: white;}
        h2 {color: white;}
      </style>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    </head>
    <body>
      <h1>Hello World!</h1>
      <h2>This is a captive portal example. All requests will be redirected here </h2>
    </body>
  </html>
)=====";

DNSServer dnsServer;
AsyncWebServer server(80);

void setup(){ //the order of the code is important and it is critical the the android workaround is after the dns and sofAP setup

  #if USE_SERIAL == true
  Serial.begin(115200);
  while (!Serial);
  Serial.println("\n\nCaptive Test, V0.3.0dev compiled " __DATE__ " " __TIME__ " by CD_FER");
  #endif

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(localIP, gatewayIP, subnetMask); //Samsung requires the IP to be in public space
  WiFi.softAP(ssid, password, WIFI_CHANNEL, 0, MAX_CLIENTS);
  
  dnsServer.setTTL(300); //set 5min client side cache for DNS
  dnsServer.start(53, "*", localIP); //if DNSServer is started with "*" for domain name, it will reply with provided IP to all DNS request

  //ampdu_rx_disable android workaround see https://github.com/espressif/arduino-esp32/issues/4423
  esp_wifi_stop();
  esp_wifi_deinit();

  wifi_init_config_t my_config = WIFI_INIT_CONFIG_DEFAULT();   //We use the default config ...
  my_config.ampdu_rx_enable = false;                           //... and modify only what we want.

  esp_wifi_init(&my_config); //set the new config
  esp_wifi_start(); //Restart WiFi
  delay(100); //this is necessary don't ask me why

  //Required
  server.on("/connecttest.txt",[](AsyncWebServerRequest *request){request->redirect("http://logout.net");}); //windows 11 captive portal workaround

  //Probably not all are Required, but some are. Others might speed things up?
  server.on("/canonical.html",[](AsyncWebServerRequest *request){request->redirect(localIPURL);}); //firefox captive portal call home
  server.on("/chrome-variations/seed",[](AsyncWebServerRequest *request){request->send(200);}); //chrome captive portal call home
  server.on("/redirect",[](AsyncWebServerRequest *request){request->redirect(localIPURL);}); //microsoft redirect
  server.on("/success.txt",[](AsyncWebServerRequest *request){request->send(200);}); //firefox captive portal call home
  server.on("/wpad.dat",[](AsyncWebServerRequest *request){request->send(404);}); //Honestly don't understand what this is but a 404 stops win 10 keep calling this repeatedly and panicking the esp32 :)
  server.on("/generate_204",[](AsyncWebServerRequest *request){request->redirect(localIPURL);}); //chromium? android? captive portal redirect
  server.on("/service/update2/json",[](AsyncWebServerRequest *request){request->send(200);}); //firefox?
  server.on("/chat",[](AsyncWebServerRequest *request){request->send(404);}); //No stop asking Whatsapp, there is no internet connection
  server.on("/startpage",[](AsyncWebServerRequest *request){request->redirect(localIPURL);});


  //return 404 to webpage icon
  server.on("/favicon.ico",[](AsyncWebServerRequest *request){request->send(404);}); //webpage icon

  //Serve Basic HTML Page WARNING IOS (and maybe macos) WILL NOT POP UP IF THIS PAGE CONTAINS THE WORD "Success" https://www.esp8266.com/viewtopic.php?f=34&t=4398
  server.on("/", HTTP_ANY, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse(200, "text/html", index_html);
    response->addHeader("Cache-Control", "public,max-age=31536000");
    request->send(response);
    DEBUG_SERIAL.println("Served Basic HTML Page");

  });

  server.onNotFound([](AsyncWebServerRequest *request){
    request->redirect(localIPURL);
    DEBUG_SERIAL.print("onnotfound ");
    DEBUG_SERIAL.print(request->host());       //This gives some insight into whatever was being requested on the serial monitor
    DEBUG_SERIAL.print(" ");
    DEBUG_SERIAL.print(request->url());
    DEBUG_SERIAL.print(" sent redirect to " + localIPURL +"\n");
  });

  server.begin();

  DEBUG_SERIAL.print("\n");
  DEBUG_SERIAL.print("Startup Time:"); //should be somewhere between 270-350 for Generic ESP32 (D0WDQ6 chip, can have a higher startup time on first boot)
  DEBUG_SERIAL.println(millis());
  DEBUG_SERIAL.print("\n");
}

void loop(){
  dnsServer.processNextRequest();
  delay(1);
}