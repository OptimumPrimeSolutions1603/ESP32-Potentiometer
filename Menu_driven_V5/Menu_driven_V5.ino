#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define POT_PIN 34

#define RED_PIN 4
#define GREEN_PIN 5
#define BLUE_PIN 18

#define LED_PIN 23

#define BUTTON_PIN 19

#define MENU_MODE 0
#define LED_MODE 1
#define RGB_MODE 2
#define ADC_MODE 3
#define ABOUT_MODE 4

int currentMode = MENU_MODE;
bool buttonCurrent=HIGH;
bool buttonPrevious=HIGH;

void setColor(int red, int green, int blue)
{ 
  ledcWrite(RED_PIN, red);
  ledcWrite(GREEN_PIN, green);
  ledcWrite(BLUE_PIN, blue);
}

void turnOutputsOff()
{
  ledcWrite(LED_PIN, 0);
  setColor(0, 0, 0);
}

const int frequency(5000);
const int resolution(8);

void showMenu(int selectedOption)
{
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  display.setCursor(46, 0);
  display.println("MENU");

  display.drawLine(0, 11, 127, 11, SSD1306_WHITE);

  display.setCursor(5, 17);
  display.print(selectedOption == 0 ? "> " : "  ");
  display.println("LED DIMMER");

  display.setCursor(5, 29);
  display.print(selectedOption == 1 ? "> " : "  ");
  display.println("RGB CONTROL");

  display.setCursor(5, 41);
  display.print(selectedOption == 2 ? "> " : "  ");
  display.println("ADC MONITOR");

  display.setCursor(5, 53);
  display.print(selectedOption == 3 ? "> " : "  ");
  display.println("ABOUT");

  display.display();
}

void showLEDDimmer(int percentage)
{
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(33, 0);
  display.println("LED DIMMER");

  display.drawLine(0, 11, 127, 11, SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 18);
  display.println("Brightness:");

  display.setTextSize(2);
  display.setCursor(40, 30);
  display.print(percentage);
  display.print("%");

  display.drawRect(9, 51, 110, 11, SSD1306_WHITE);

  int barWidth = map(percentage, 0, 100, 0, 106);

  display.fillRect(11, 53, barWidth, 7, SSD1306_WHITE);

  display.display();
}

void showRGBControl(int percentage)
{
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(28, 0);
  display.println("RGB CONTROL");

  display.drawLine(0, 11, 127, 11, SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 18);
  display.println("Color Position:");

  display.setTextSize(2);
  display.setCursor(40, 30);
  display.print(percentage);
  display.print("%");

  display.drawRect(9, 51, 110, 11, SSD1306_WHITE);

  int barWidth = map(percentage, 0, 100, 0, 106);

  display.fillRect(11, 53, barWidth, 7, SSD1306_WHITE);

  display.display();
}

void showADCMonitor(int adcValue)
{
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(28, 0);
  display.println("ADC MONITOR");

  display.drawLine(0, 11, 127, 11, SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println("ADC Value:");

  display.setTextSize(3);
  display.setCursor(25, 35);
  display.println(adcValue);

  display.display();
}

void showAbout()
{
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(45, 0);
  display.println("ABOUT");

  display.drawLine(0, 11, 127, 11, SSD1306_WHITE);

  display.setCursor(18, 20);
  display.println("Pot Controller");

  display.setCursor(36, 33);
  display.println("Version 5");

  display.setCursor(46, 46);
  display.println("ESP32");

  display.display();
}

void controlLED(int potValue)
{
  int brightness=map(potValue, 0, 4095, 0, 255);

  brightness=constrain(brightness, 0, 255);

  ledcWrite(LED_PIN, brightness);

  int percentage=map(potValue, 0, 4095, 0, 100);

  percentage=constrain(percentage, 0, 100);

  showLEDDimmer(percentage);
}

void controlRGB(int potValue)
{
  int redValue=0;
  int greenValue=0;
  int blueValue=0;

  if(potValue<1023)
  {
    greenValue=map(potValue, 0, 1023, 0, 255);
    redValue=255;
    blueValue=0;
  }

  else if(potValue<2047)
  {
    redValue=map(potValue, 1024, 2047, 255, 0);
    greenValue=255;
    blueValue=0;
  }

  else if(potValue<3071)
  {
    redValue=0;
    greenValue=255;
    blueValue=map(potValue, 2048, 3071, 0, 255);
  }

  else
  {
    redValue=0;
    greenValue=map(potValue, 3072, 4095, 255, 0);
    blueValue=255;
  }

  setColor(redValue, greenValue, blueValue);

  int percentage=map(potValue, 0, 4095, 0, 100);

  percentage=constrain(percentage, 0, 100);

  showRGBControl(percentage);
  
}

void setup() {
  pinMode(POT_PIN, INPUT);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  ledcAttach(LED_PIN, frequency, resolution);

  ledcAttach(RED_PIN, frequency, resolution);
  ledcAttach(GREEN_PIN, frequency, resolution);
  ledcAttach(BLUE_PIN, frequency, resolution);

  
  turnOutputsOff();

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

  buttonCurrent = digitalRead(BUTTON_PIN);

  // Button pressed
  if (buttonCurrent == LOW && buttonPrevious == HIGH)
  {
    delay(30);

    if (currentMode == MENU_MODE)
    {
      int menuOption = map(potValue, 0, 1024, 0, 3);

      menuOption = constrain(menuOption, 0, 3);

      switch (menuOption)
      {
        case 0:
          currentMode = LED_MODE;
          break;

        case 1:
          currentMode = RGB_MODE;
          break;

        case 2:
          currentMode = ADC_MODE;
          break;

        case 3:
          currentMode = ABOUT_MODE;
          break;
      }
    }
    else
    {
      currentMode = MENU_MODE;

      turnOutputsOff();
    }
  }

  buttonPrevious = buttonCurrent;

  switch (currentMode)
  {
    case MENU_MODE:
    {
      turnOutputsOff();

      int menuOption = map(potValue, 0, 1024, 0, 3);

      menuOption = constrain(menuOption, 0, 3);

      showMenu(menuOption);

      break;
    }

    case LED_MODE:
      setColor(0, 0, 0);

      controlLED(potValue);

      break;

    case RGB_MODE:
      ledcWrite(LED_PIN, 0);

      controlRGB(potValue);

      break;

    case ADC_MODE:
      turnOutputsOff();

      showADCMonitor(potValue);

      break;

    case ABOUT_MODE:
      turnOutputsOff();

      showAbout();

      break;
  }

  delay(50);
}


