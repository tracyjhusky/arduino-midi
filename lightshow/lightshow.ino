#include <Adafruit_NeoPixel.h>


const int PIXELS = 150;
const int PIN = 6;

class Color {
    int red, green, blue;
    double hue, sat, lite;
  public:
    void fromHSL(double, double, double);
    uint32_t color() {return strip.Color(r, g, b);}
    double getHue() {return hue;}
    double getSat() {return sat;}
    double getLite() {return lite;}
    void setHue(double h) {hue = h;}
    void setSat(double s) {sat = s;}
    void setLite(double l) {lite = l;}
};


void Color::fromHSL(double h, double s, double l) {
  hue = h;
  sat = s;
  lite = l;

  double c = v * s;
  double x = c * (1 - absv(rem(h / 60, 2) - 1));
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

  red = (r + m) * 255;
  green = (g + m) * 255;
  blue = (b + m) * 255;
}


Color colors[PIXELS];

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, PIN);

void spectrum(int p) {
  for(int i = 0; i < PIXELS; i++) {
    Color newColor = newColor.fromHSL((i * p * 360 / PIXELS) % 360, 1, .25);
    colors[i] = newColor;
  }
}

void render() {
  for(int i = 0; i < PIXELS; i++) {
    strip.setPixelColor(i, colors[i].color());
  }
  strip.show();
}

void colorAll(Color color) {
  for(int i = 0; i < PIXELS; i++) {
    colors[i] = color;
  }
}

void hueShift(int h) {
  for(int i = 0; i < PIXELS; i++) {
    Color newColor;
    Color oldColor = colors[i];
    colors[i] = newColor.fromHSL(oldColor.getHue() + h, oldColor.getSat(), oldColor.getLite());
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

void setup() {
  strip.begin();
  spectrum(2);
  render();
}

void loop() {
  delay(10);
  hueShift(1);
  render();
}
