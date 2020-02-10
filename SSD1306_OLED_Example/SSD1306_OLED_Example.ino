#include <Wire.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    0  // Reset pin for display (0 or -1 if no reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  Serial.begin(9600);
  while (!Serial);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println("Display setup failed");
    while (true);
  }
  Serial.println("Display is good to go");
}

void loop() {
  int sensorReading = analogRead(A0);

  /* you get 10 charcters across at this size using the default font
    so make your text accordingly. If you want to try other fonts,
    check out fonts from http://oleddisplay.squix.ch/#/home
  */
  // clear the display:
  display.clearDisplay();
  // set the text size to 2:
  display.setTextSize(2);
  // set the text color to white:
  display.setTextColor(SSD1306_WHITE);
  
  // move the cursor to 0,0:
  display.setCursor(0, 0);
  // print the seconds:
  display.print("secs:");
  display.print(millis() / 1000);
  
  // move the cursor down 20 pixels:
  display.setCursor(0, 20);
  // print a sensor reading:
  display.print("sensor:");
  display.print(sensorReading);
  // push everything out to the screen:
  display.display();
}
