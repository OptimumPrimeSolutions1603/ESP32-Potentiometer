#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define POT_PIN 34

void updateDisplay(int adcValue)
{
  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(24, 0);
  display.println("POTENTIOMETER");

  display.drawLine(0, 11, 127, 11, SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(36, 20);
  display.println("ADC VALUE");

  display.setTextSize(3);
  display.setCursor(25, 35);
  display.println(adcValue);

  display.display();
}

void setup() {
  pinMode(POT_PIN, INPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    while(true)
    {

    }
  }

  display.clearDisplay();
  display.display();
  
}

void loop() {
  int potValue=analogRead(POT_PIN);

  updateDisplay(potValue);

  delay(100);
}
