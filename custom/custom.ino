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
    if(command == 128) {
      for(int i = 0; i < PIXELS; i++) {
        setHSV(i, velocity * 2, .5, .5);
      }
    }
  }
}

void setHSV(int i, int h, double s, double v) {
  double c = v * s;
  double x = c * (1 - Math.fabs((h / 60) % 2 - 1));
  double m = v - c;
  double r;
  double g;
  double b;

  if(h < 60) {
    r = c;
    g = x;
    b = 0;
  }
  else if(h < 120) {
    r = x;
    g = c;
    b = 0;
  }
  else if(h < 180) {
    r = 0;
    g = c;
    b = x;
  }
  else if(h < 240) {
    r = 0;
    g = x;
    b = c;
  }
  else if(h < 300) {
    r = x;
    g = 0;
    b = c;
  }
  else {
    r = c;
    g = 0;
    b = x;
  }

  int red = (r + m) * 255;
  int green = (g + m) * 255;
  int blue = (b + m) * 255;

  strip.setPixelColor(i, red, green, blue);
}
