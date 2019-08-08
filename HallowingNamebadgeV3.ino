#include "Adafruit_FreeTouch.h"

Adafruit_FreeTouch qt_1 = Adafruit_FreeTouch(A2, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_2 = Adafruit_FreeTouch(A3, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_3 = Adafruit_FreeTouch(A4, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_4 = Adafruit_FreeTouch(A5, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>

int backgroundColor = (0x6666);
int borderColor = (0x1234);
int textColor = (0x7FFF);
int textBackground = (0x0000);

#define TFT_CS     39
#define TFT_RST    37
#define TFT_DC     38
#define TFT_BACKLIGHT 7
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

void setup(void) {
  Serial.begin(115200);
  pinMode(A2, INPUT);
  randomSeed(analogRead(A2));
  tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab
  tft.setRotation(2);
  pinMode(TFT_BACKLIGHT, OUTPUT);
  analogWrite(TFT_BACKLIGHT, 255);
  drawScreen();
  roundRects();
  Serial.println("FreeTouch test");
  
  if (! qt_1.begin())  
    Serial.println("Failed to begin qt on pin A2");
  if (! qt_2.begin())  
    Serial.println("Failed to begin qt on pin A3");
  if (! qt_3.begin())  
    Serial.println("Failed to begin qt on pin A4");
  if (! qt_4.begin())  
    Serial.println("Failed to begin qt on pin A5");
}



void loop() {
  int counter, result = 0;

  // DIY
  Serial.println("\n*************************************");

  counter = millis();
  result = qt_1.measure(); 
  Serial.print("QT 1: "); Serial.print(result);
  Serial.print(" (");  Serial.print(millis() - counter); Serial.println(" ms)");
  if (result > 650) {
     roundRects();
  }
  
  counter = millis();
  result = qt_2.measure(); 
  Serial.print("QT 2: "); Serial.print(result);
  Serial.print(" (");  Serial.print(millis() - counter); Serial.println(" ms)");
  if (result > 650) {
    textColor = (random(0x0000,0xFFFF));
    drawScreen();
    delay(1000);
  }
  
  counter = millis();
  result = qt_3.measure(); 
  Serial.print("QT 3: "); Serial.print(result);
  Serial.print(" (");  Serial.print(millis() - counter); Serial.println(" ms)");
  if (result > 650) {
     borderColor = (random(0x0000,0xFFFF));
     drawScreen();
     delay(1000);
  }
  
  counter = millis();
  result = qt_4.measure(); 
  Serial.print("QT 4: "); Serial.print(result);
  Serial.print(" (");  Serial.print(millis() - counter); Serial.println(" ms)");
  if (result > 650) {
     backgroundColor = (random(0x0000,0xFFFF));
     drawScreen();
     delay(300);
  }
  delay(200);
}

void drawScreen() {
  tft.fillScreen(backgroundColor);
  tft.fillRoundRect(10, 26, 110, 45, 7, borderColor);
  tft.fillRoundRect(14, 30, 102, 37, 14, textBackground);
  tft.setCursor(30, 42);
  tft.setTextColor(textColor);
  tft.setTextSize(2);
  tft.println("Wesley");
  delay(500);
}

void roundRects() {
  tft.fillScreen(backgroundColor);
    int color = random(100,1100);
    int i;
    int t;
    for(t = 0 ; t <= 4; t+=1) {
      int x = random(0,14);
      int y = random(0,14);
      int w = 4;
      int h = 4;
      for(i = 0 ; i <= 15; i+=1) {
        tft.drawRoundRect(x, y, w, h, random(2,6), color);
        x = random(0,70);
        y = random(0,70);
        w+=random(1,8);
        h+=random(1,5);
        color+=random(-2200,2700);
        delay(100);
      }
  }
  tft.fillRoundRect(10, 26, 110, 45, 7, borderColor);
  tft.fillRoundRect(14, 30, 102, 37, 14, textBackground);
  tft.setCursor(30, 42);
  tft.setTextColor(textColor);
  tft.setTextSize(2);
  tft.println("Wesley");
  delay(1000);
}
