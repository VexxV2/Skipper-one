#include <OneButton.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Encoder.h>
#include <OneButton.h>
#include <Wire.h>

Encoder Enc(4,3);

Adafruit_SSD1306 display(128, 64, &Wire, -1);
OneButton EncClick;

int lastRead = -99;
int encRead = 0;

void onClick() {
  
}

void setup() {
  Serial.begin(115200);
    delay(3000);
    Wire.begin(7,6);
    if (display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
      Serial.println("OLED OK");
    } 
    else {
      Serial.println("OLED failed");
    }
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
   display.clearDisplay();
   display.setCursor(0, 0);
   display.print(encRead);
   display.display();
   lastRead = encRead; 
  }
}
