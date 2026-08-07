#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define POT_PIN 34
#define LED_PIN 4

const int frequency(5000);
const int resolution(8);

void updateDisplay(int percentage)
{
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(24, 0);
  display.println("POTENTIOMETER");

  display.drawLine(0, 11, 127, 11, SSD1306_WHITE);

  display.setTextSize(3);

  if (percentage < 10)
  {
    display.setCursor(43, 20);
  }
  else if (percentage < 100)
  {
    display.setCursor(34, 20);
  }
  else
  {
    display.setCursor(25, 20);
  }

  display.print(percentage);
  display.print("%");

  // Progress bar outline
  display.drawRect(9, 51, 110, 11, SSD1306_WHITE);

  // Convert percentage into progress bar width
  int barWidth = map(percentage, 0, 100, 0, 106);

  // Fill the progress bar
  display.fillRect(11, 53, barWidth, 7, SSD1306_WHITE);

  display.display();
}

void setup() {
  pinMode(POT_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  ledcAttach(LED_PIN, frequency, resolution);

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

  int brightness=map(potValue, 0, 4095, 0, 255);

  int percentage=map(potValue, 0, 4095, 0, 100);

  percentage=constrain(percentage, 0, 100);

  ledcWrite(LED_PIN, brightness);

  updateDisplay(percentage);

  delay(100);
}

