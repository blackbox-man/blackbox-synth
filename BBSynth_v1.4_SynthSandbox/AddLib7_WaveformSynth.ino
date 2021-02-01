void playWaveform (float freq, float ampl, bool onOff) {
  if (onOff) {
//    Serial.println(F("Waveform triggered"));    
    waveform1.frequency(freq);
    waveform1.amplitude(ampl);
  }
  else {
    waveform1.amplitude(0);
  }
//  Serial.println(F("Waveform triggered"));    
//  waveform1.begin(1, NOTE_C1, DEF_WAVESYNTH);
//  waveform1.frequency(bar1TouchLoc/1793);
//  waveform1.amplitude(sqrTouchLocY);
}

void updateWaveform (float freq, float ampl) {
  waveform1.frequency(freq);
  waveform1.amplitude(ampl);
}
