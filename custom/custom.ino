#include <MIDI.h>

int baud = 31250; // Make this higher if shit looks laggy.

// Creates and binds the MIDI interface to the default hardware Serial port
MIDI_CREATE_DEFAULT_INSTANCE();

void consumeNote(byte channel, byte pitch, byte velocity) {
  Serial.print(channel);
  Serial.print(pitch);
  Serial.print(velocity);
}

void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(consumeNote);
  Serial.begin(baud);
}

void loop() {
  MIDI.read();
}
