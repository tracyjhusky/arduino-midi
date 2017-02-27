#include <Adafruit_NeoPixel.h>


const int PIXELS = 150;
const int PIN = 8;

byte command;
byte note;
byte velocity;

int count = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, PIN);

void lights() {

}

void setup() {
  Serial.begin(38400);

  strip.begin();
  for(int i = 0; i < PIXELS; i++) {
    strip.setPixelColor(i, 63, 0, 0);
  }
  strip.show();
}

void loop() {
  if(Serial.available() > 2) {
    command = Serial.read();
    note = Serial.read();
    velocity = Serial.read();

    if(command == 128 && count < PIXELS) {
      strip.setPixelColor(count, note, 0, 0);
      strip.show();
      count++;
    }
  }
}
