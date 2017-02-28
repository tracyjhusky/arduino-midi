#include <Adafruit_NeoPixel.h>


const int PIXELS = 150;
const int PIN = 8;

byte command;
byte note;
byte velocity;

int count = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, PIN);

void rainbow() {
  for(int i = 0; i < 360; i++) {
    uint32_t color = toHSV(i, 1, .5);
    for(int j = 0; j < PIXELS; j++) {
      strip.setPixelColor(j, color);
    }
    strip.show();
  }
}

void line() {
  for(int i = 0; i < PIXELS; i++) {
    uint32_t color = toHSV(i * 360 / PIXELS, 1, .5);
    for(int j = 0; j < PIXELS; j++) {
      if(i == j) {
        strip.setPixelColor(j, color);
      }
      else {
        strip.setPixelColor(j, 0, 0, 0);
      }
      strip.show();
    }
  }
}

void setup() {
  Serial.begin(38400);

  strip.begin();
  for(int i = 0; i < PIXELS; i++) {
    strip.setPixelColor(i, 63, 0, 0);
  }
  strip.show();
  delay(1000);
  line();
  rainbow();
}

void loop() {
  if(Serial.available() > 2) {
    command = Serial.read();
    note = Serial.read();
    velocity = Serial.read();
    if(command == 144) {
      uint32_t color = toHSV(velocity * 2.5, 1, .5);
      for(int i = 0; i < PIXELS; i++) {
        strip.setPixelColor(i, color);
      }
    }
    else {
      uint32_t color = toHSV(velocity * 2.5, 1, .5);
      for(int i = 0; i < PIXELS; i++) {
        strip.setPixelColor(i, color);
      }
    }
    strip.show();
  }
}

double rem(double q, int d) {
  if(q < d) {
      return q;
  }
  else {
      rem(q - d, d);
  }
}

double absv(double n) {
  if (n > 0) {
    return n;
  }
  else {
    return n * -1;
  }
}

uint32_t toHSV(double h, double s, double v) {
  double c = v * s;
  double x = c * (1 - absv(rem(h / 60, 2) - 1));
   // std::cout << x;
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

  return strip.Color(red, green, blue);
}
