#include <Adafruit_NeoPixel.h>


const int PIXELS = 60;
const int PIN = 8;

int count = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, PIN);

void lights() {

}

void setup() {
  strip.begin();
  for(int i = 0; i < PIXELS; i++) {
    strip.setPixelColor(i, 255, 0, 0);
  }
  strip.show();
}

void loop() {
  delay(1000);
  if(count < PIXELS) {
    strip.setPixelColor(count, 0, 255, 255);
    strip.show();
    count++;
  }
}
