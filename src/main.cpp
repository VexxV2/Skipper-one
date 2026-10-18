#include <Arduino.h>
#include <OneButton.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Encoder.h>
#include <OneButton.h>
#include <Wire.h>

Encoder Enc(4,3);

Adafruit_SSD1306 display(128, 64, &Wire, -1);
OneButton EncClick(2);

int lastRead = -99;
int encRead = 0;

enum ScreenState {
  MainMenu,
  GamesMenu,
  WiFiMenu,
  SettingsMenu
};

enum MenuSelection {
  Games,
  WiFi,
  Settings
};

ScreenState screenState = MainMenu;
MenuSelection menuSelection = Games;

void onClick() {
  switch (screenState) {
    case ScreenState::MainMenu:
      switch (menuSelection) {
        case Games:  
      } 
  }
}

void updateDisplay() {
  switch (screenState) {
    case MainMenu:
      display.clearDisplay();
      display.setCursor(50, 0);
      display.print("Main Menu");
      display.setCursor(0, 20);
      display.print("Games");
      display.setCursor(0, 40);
      display.print("WiFi");
      display.setCursor(0, 60);
      display.print("Settings");
      break;
    case GamesMenu:
      display.clearDisplay();
      display.setCursor(50, 0);
      display.print("Games Menu");
      break;
    case WiFiMenu:
      display.clearDisplay();
      display.setCursor(50, 0);
      display.print("WiFi Menu");
      break;
    case SettingsMenu:
      display.clearDisplay();
      display.setCursor(50, 0);
      display.print("Settings Menu");
      break;
  }
}
  

void setup() {
  Wire.begin(7,6);
  delay(2000);
  display.clearDisplay(); 
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.display();
  Enc.write(0);
}

void loop() {
  encRead = Enc.read() /4;

  if (encRead != lastRead) {
    updateDisplay();
    lastRead = encRead; 
  }
}
