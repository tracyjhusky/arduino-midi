#include <Adafruit_NeoPixel.h>
#include <MIDI.h>

const int BAUD = 38400;

const int PIXELS = 60;
const int PIN = 6;


Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, PIN);

MIDI_CREATE_DEFAULT_INSTANCE();

void consumeNote(byte channel, byte pitch, byte velocity) {
  for(int i = 0; i < PIXELS; i++) {
    strip.setPixelColor(i, 0, 255, 255);
  }
  strip.show();
}

void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(consumeNote);

  Serial.begin(BAUD);
  Serial.print('Started...');

  strip.begin();
  for(int i = 0; i < PIXELS; i++) {
    strip.setPixelColor(i, 255, 0, 0);
  }
  strip.show();
}

void loop() {
  MIDI.read();
}
