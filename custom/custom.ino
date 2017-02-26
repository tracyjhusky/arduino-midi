#include <Adafruit_NeoPixel.h>
#include <MIDI.h>


const int PIXELS = 60;
const int PIN = 8;

int count = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, PIN);

MIDI_CREATE_DEFAULT_INSTANCE();

void consumeNote(byte channel, byte pitch, byte velocity) {
  if(count < PIXELS) {
    strip.setPixelColor(count, 0, 255, 255);
    strip.show();
    count++;
  }
}

void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(consumeNote);

  Serial.begin(115200));

  strip.begin();
  for(int i = 0; i < PIXELS; i++) {
    strip.setPixelColor(i, 255, 0, 0);
  }
  strip.show();
}

void loop() {
  delay(1000);
  MIDI.read();
}
