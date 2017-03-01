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

void firework() {
  double val = .33;
  for (int i = 0; i < 500; i++) {
    uint32_t color = toRGB(0, 0, val);
    colorAll(color);
    val -= .33/500;
    delay(10);
  }
  flash(toRGB(0, 0, .33), 7);
  sparkFade(50);
}

void flash(uint32_t color, int n) {
  for (int i = 0; i < n; i++) {
    colorAll(color);
    delay(10);
    colorAll(toRGB(0, 0, 0));
  }
}

void sparkFade(int n) {
  double val = .33;
  for(int i = 0; i < n; i++) {
    uint32_t color = toRGB(0, 0, val);
    long r = random(10);
    if (r === 0) {
      strip.setPixelColor(i, color);
    }
    else {
      strip.setPixelColor(i, 0, 0, 0);
    }
    delay(10);
  }
}

void colorAll(uint32_t color) {
  for(int i = 0; i < PIXELS; i++) {
    strip.setPixelColor(i, color);
  }
}

void loop() {
  fade();
  if(Serial.available() > 2) {
    command = Serial.read();
    note = Serial.read();
    velocity = Serial.read();

    light();

    strip.show();
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

uint32_t toRGB(double h, double s, double v) {
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
