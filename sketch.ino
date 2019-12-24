#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display{-1};//SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1};

static const uint8_t qr_image_data[16] {
    0xff, 0x00, 0x00, 0xff,
    0x00, 0xff, 0xff, 0x00,
    0x00, 0xff, 0xff, 0x00,
    0xff, 0x00, 0x00, 0xff
    };

ESP8266WebServer server{80};

String header;

void handleRoot()
{
    server.send(200, "text/html", "<h1>God Jul</h1>");
}

void setup()
{
    Serial.begin(115200);

    bool result {WiFi.softAP("JulIoT")};
    if (!result)
    {
        Serial.println("Failed to setup WiFi");
    }

    // config server
    server.on("/", handleRoot);
    
    Serial.print("IP: ");
    Serial.println(WiFi.softAPIP());
    
    server.begin();
}

void loop()
{
  server.handleClient();
}
