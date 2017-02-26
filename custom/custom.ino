#include <Adafruit_Neopixel.h>
#include <MIDI.h>

const int BAUD = 38400;

const int PIXELS = 60;
const int PIN = 6;


Adafruit_Neopixel strip = Adafruit_Neopixel(PIXELS, PIN);

MIDI_CREATE_DEFAULT_INSTANCE();

void consumeNote(byte channel, byte pitch, byte velocity) {
  strip.setPixelColor(4, 0, 255, 255);
  strip.show();
}

void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(consumeNote);

  Serial.begin(BAUD);
  Serial.print('Started...');

  strip.begin();
  strip.setPixelColor(4, 255, 0, 0);
  strip.show();
}

void loop() {
  MIDI.read();
}
