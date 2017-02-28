#include <Adafruit_NeoPixel.h>


const int PIXELS = 150;
const int PIN = 8;

byte command;
byte note;
byte velocity;

int count = 0;
double brightness[PIXELS] = {};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, PIN);

void setup() {
  Serial.begin(38400);

  strip.begin();
  for(int i = 0; i < PIXELS; i++) {
    strip.setPixelColor(i, 0, 24, 0);
  }
  strip.show();
}

void loop() {
  if(Serial.available() > 2) {
    command = Serial.read();
    note = Serial.read();
    velocity = Serial.read();

    autoShow();

    strip.show();
  }
}

void autoShow() {
  for(int i = 0; i < PIXELS; i ++) {
    brightness[i] -= .01;
  }
  int offset = note % 12;
  if(command == 144) { 
    for(int i = offset; i < PIXELS; i += 12) {
      brightness[i] = .5;
    }
  }
  else {
    for(int i = offset; i < PIXELS; i += 12) {
      brightness[i] = 0;
    }
  }

  for(int i = 0; i < PIXELS; i ++) {
    uint32_t color = toHSV((i % 12) * 30, 1, brightness[i]);
    strip.setPixelColor(i, color);
  }
}

void customShow() {
  if(command == 144) {
    uint32_t color = toHSV(velocity * 2.5, 1, .5);
    for(int i = 0; i < PIXELS; i++) {
      strip.setPixelColor(i, color);
    }
  }
  else {
    for(int i = 0; i < PIXELS; i++) {
      strip.setPixelColor(i, 0, 0, 0);
    }
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
