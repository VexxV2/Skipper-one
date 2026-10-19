#include <Arduino.h>
#include <OneButton.h>

OneButton btn(5, true, true);   // pin 5, active LOW, internal pull-up

void onClick() {
  Serial.println("CLICK");
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  btn.attachClick(onClick);
  btn.attachPress([]() { Serial.println("press"); });
  Serial.println("OneButton test started");
}

void loop() {
  btn.tick();
}