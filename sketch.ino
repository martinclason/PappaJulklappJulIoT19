#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <LOLIN_I2C_BUTTON.h>

/* Adafruit_SSD1306 display(0); */

#if (SSD1306_LCDHEIGHT != 48)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define QR_CODE_HEIGHT 25
#define QR_CODE_WIDTH  25
#define PADDING 5

static const unsigned char PROGMEM qr_code_bmp[] =
{
    B11111110, B01110100, B10111111, B10000000,
    B10000010, B00011000, B00100000, B10000000,
    B10111010, B01110010, B10101110, B10000000,
    B10111010, B10110011, B10101110, B10000000,
    B10111010, B10101100, B00101110, B10000000,
    B10000010, B01100110, B00100000, B10000000,
    B11111110, B10101010, B10111111, B10000000,
    B00000000, B01001100, B10000000, B00000000,
    B11000111, B01101011, B10001100, B00000000,
    B00100001, B10100011, B11001111, B00000000,
    B01000110, B11011001, B00110101, B10000000,
    B01101000, B10110011, B10001100, B10000000,
    B11100110, B01100110, B11100000, B10000000,
    B10100000, B00101111, B00000001, B00000000,
    B10011110, B01100111, B01010101, B10000000,
    B10011101, B10001110, B10001010, B10000000,
    B10101111, B00101010, B11111010, B00000000,
    B00000000, B11100001, B10001010, B00000000,
    B11111110, B11101110, B10101100, B10000000,
    B10000010, B11110010, B10001000, B00000000,
    B10111010, B01010001, B11111110, B10000000,
    B10111010, B00101100, B00110101, B10000000,
    B10111010, B00100110, B01000010, B10000000,
    B10000010, B10101101, B10111000, B10000000,
    B11111110, B10011101, B10100100, B10000000,
};

Adafruit_SSD1306 display{-1};//SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1};
I2C_BUTTON button(DEFAULT_I2C_BUTTON_ADDRESS); //I2C Address 0x31
ESP8266WebServer server{80};

bool is_displaying {false};
long start_displaying_time;
const long display_time {15*1000};
const long poll_button_interval {20};
long last_poll_time;
long current_time;
String header;

void displayQRCode(uint8_t x, uint8_t y)
{
    display.drawBitmap(x, y, qr_code_bmp, QR_CODE_WIDTH, QR_CODE_HEIGHT, BLACK);
}

void displayWiFiName(uint8_t x, uint8_t y)
{
    display.setTextColor(BLACK);
    display.setTextSize(1);
    display.setCursor(PADDING + QR_CODE_WIDTH + PADDING - 1, PADDING + QR_CODE_HEIGHT - 6);
    display.print("WiFi:");
    display.setCursor(PADDING + QR_CODE_WIDTH - 6, PADDING + QR_CODE_HEIGHT + PADDING);
    display.print("JulIoT");
}

void displayInfo(long t)
{
    display.clearDisplay();

    display.fillScreen(WHITE);
    //displayQRCode(8, (SSD1306_LCDHEIGHT - QR_CODE_HEIGHT) / 2);
    displayQRCode(PADDING, PADDING);
    displayWiFiName(5, QR_CODE_HEIGHT + 5);
    //display.drawBitmap(8,8,qr_code_bmp, QR_CODE_WIDTH, QR_CODE_HEIGHT, BLACK);

    display.display();
    start_displaying_time = t;
    is_displaying = true;
}

void clearDisplay()
{
    display.clearDisplay();
    display.display();
    is_displaying = false;
}

bool shouldDisplay(long t)
{
    return t < start_displaying_time + display_time;
}

void handleRoot()
{
    
    server.send(200, "text/html", "<meta charset='UTF-8'><h1>God jul Pappa önskar Martin!</h1><br><br>Källkoden för det här projektet får bli en julklapp till dig. Finns att hitta på github på <a href='https://github.com/martinclason/PappaJulklappJulIoT19'>martinclason/PappaJulklappJulIoT19</a><br><br>Du är bäst!");
}

void setup()
{
    // init serial port for debugging
    Serial.begin(115200);

    // config server
    WiFi.mode(WIFI_AP); // Q: Does this fix the issues with trouble connecting to the esp? A: Yes! It seems to work a lot faster now!
    bool result {WiFi.softAP("JulIoT")};
    if (!result)
    {
        Serial.println("Failed to setup WiFi");
    }

    server.on("/", handleRoot);

    Serial.print("IP: ");
    Serial.println(WiFi.softAPIP());

    server.begin();

    // init time
    last_poll_time = millis();

    // init display
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)    
    clearDisplay();
}

void loop()
{
    server.handleClient();
    current_time = millis();
    if (is_displaying)
    {
        if (!shouldDisplay(current_time))
        {
            clearDisplay();
        }
    }

    if (current_time > last_poll_time + poll_button_interval)
    {
        if (button.get() == 0) // button press
        {
            if (button.BUTTON_A)
            {
                displayInfo(current_time);
            }
            
            if (button.BUTTON_B)
            {
                displayInfo(current_time);
            }
        }
    }
}
