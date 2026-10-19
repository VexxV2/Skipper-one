#include <Arduino.h>
#include <Wire.h>
#include <OneButton.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Encoder.h>


Encoder Enc(4,3);

Adafruit_SSD1306 display(128, 64, &Wire, -1);
OneButton EncClick(5, true, true);

int lastRead = 0;
int encRead = 0;

enum ScreenState {
  MainMenu,
  GamesMenu,
  WiFiMenu,
  SettingsMenu
};

ScreenState screenState = MainMenu;

const char* menuItems[] = {"Games", "WiFi", "Settings"};
const int menuCount = sizeof(menuItems) / sizeof(menuItems[0]);
int menuIndex = 0;

const int textX = 9;

void updateDisplay() {
  display.clearDisplay();

  switch (screenState) {
    case MainMenu:
      display.setCursor(0, 0);
      display.print("Main Menu");
      display.drawFastHLine(0, 11, 64, WHITE);

      for (int i = 0; i < menuCount; i++) {
        int y = 16 + i * 16;

        if (i == menuIndex) {
          display.setCursor(0, y);
          display.print(">");
        }

        display.setCursor(textX, y);
        display.print(menuItems[i]);
      }
      break;

    case GamesMenu:
      display.setCursor(0, 0);
      display.print("Games Menu");
      display.drawFastHLine(0, 11, 64, WHITE);
      break;

    case WiFiMenu:
      display.setCursor(0, 0);
      display.print("WiFi Menu");
      display.drawFastHLine(0, 11, 64, WHITE);
      break;

    case SettingsMenu:
      display.setCursor(0, 0);
      display.print("Settings Menu");
      display.drawFastHLine(0, 11, 64, WHITE);
      break;
  }

  display.display();
}

void onClick() {
  if (screenState == MainMenu) {
    switch (menuIndex) {
      case 0: screenState = GamesMenu;    break;
      case 1: screenState = WiFiMenu;     break;
      case 2: screenState = SettingsMenu; break;
    }
  } else {
    screenState = MainMenu;
  }

  updateDisplay();
}
  

void setup() {
  Wire.begin(7,6);
  pinMode(5, INPUT_PULLUP);
  delay(2000);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay(); 
  display.setTextColor(WHITE);
  display.setTextSize(1);
 
  updateDisplay();  

  display.display();
  EncClick.attachClick(onClick);
  Enc.write(0);
}

void loop() {
  EncClick.tick();

  encRead = Enc.read() / 4;

  if (encRead != lastRead) {
    int change = encRead - lastRead;
    lastRead = encRead;

    if (screenState == MainMenu) {
      menuIndex += change;
      menuIndex = constrain(menuIndex, 0, menuCount - 1);
    }

    updateDisplay();
  }
}
