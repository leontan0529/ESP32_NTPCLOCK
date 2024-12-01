#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// OLED Display Dimensions
/*
I am using a 0.66", 64x48 OLED display driven by SSD1306 controller. However, setting width=64px only allow me to use half the display
*/
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 48
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// WiFi Credentials
const char* ssid="";
const char* password="";

// NTP Client Settings
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 28800, 60000);

void setup() {
  Serial.begin(115200);

  Wire.begin(4, 3); // GPIO4=SDA=D04, GPIO3=SCL=D05

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0X3C)) {
    Serial.println("OLED init failed.");
    while(true);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  WiFi.begin(ssid, password);
  display.setCursor(40, 0);
  display.println("Connecting...");
  display.display();
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("WiFi Connected!");
  Serial.println("IP Address: " + String(WiFi.localIP()));
  display.clearDisplay();
  display.setCursor(40, 0);
  display.println("Connected!");
  display.display();

  timeClient.begin();
}

void loop() {
  // Update time
  timeClient.update();

  // Get formatted time
  String currentTime = timeClient.getFormattedTime();

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(40, 0);
  display.print("Clock:");
  display.setCursor(40, 8);
  display.print(currentTime);
  display.display();

  delay(1000);
}