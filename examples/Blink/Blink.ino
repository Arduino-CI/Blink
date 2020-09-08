// modeled on https://www.arduino.cc/en/Tutorial/Blink

#include "Blink.h"
Blink blink;

void setup() {
    blink.setup();
}

void loop() {
  blink.loop();
}
