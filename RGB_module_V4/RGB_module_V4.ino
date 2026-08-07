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

void setColor(bool red, bool green, bool blue)
{
  digitalWrite(RED_PIN, red);
  digitalWrite(GREEN_PIN, green);
  digitalWrite(BLUE_PIN, blue);
}

const int frequency(5000);
const int resolution(8);

void updateDisplay(String colorName, int percentage)
{
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(22, 0);
  display.println("RGB CONTROLLER");

  display.drawLine(0, 11, 127, 11, SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 18);
  display.print("Color:");

  // Display selected color
  display.setTextSize(2);
  display.setCursor(0, 29);
  display.println(colorName);

  // Percentage
  display.setTextSize(1);
  display.setCursor(90, 20);
  display.print(percentage);
  display.print("%");

  // Progress bar outline
  display.drawRect(9, 51, 110, 11, SSD1306_WHITE);

  // Convert percentage to progress bar width
  int barWidth = map(percentage, 0, 100, 0, 106);

  // Fill progress bar
  display.fillRect(11, 53, barWidth, 7, SSD1306_WHITE);

  display.display();
}

void setup() {
  pinMode(POT_PIN, INPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  
  setColor(LOW, LOW, LOW);

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

  String colorName;

  if(potValue<=819)
  {
    setColor(HIGH, LOW, LOW);
    colorName="RED";
  }

  else if(potValue<=1638)
  {
    setColor(HIGH, HIGH, LOW);
    colorName="YELLOW";
  }

  else if(potValue<2457)
  {
    setColor(LOW, HIGH, LOW);
    colorName="GREEN";
  }

  else if(potValue<=3276)
  {
    setColor(LOW, HIGH, HIGH);
    colorName="CYAN";
  }

  else
  {
    setColor(LOW, LOW, HIGH);

    colorName="BLUE";
  }

  updateDisplay(colorName, percentage);

  delay(100);
}

