void playWavetable (float freq, float ampl, bool onOff) {  
  static bool isPlaying;
  int midiAmp = 127.0 * ampl;  
  
  wavetable1.playFrequency(freq, midiAmp);
//  if (onOff) {
//    if (!isPlaying) {
//      wavetable1.playFrequency(freq, midiAmp);
//      isPlaying = true;
////      Serial.print("playing wavetable: ");
////      Serial.println(freq);
////      delay(10);
//    }
//    else {
//      updateWavetable(freq, midiAmp);
////      isPlaying = true;
//    }
//  }
//  else if(isPlaying) {
//    Serial.println("stopped now");
//    delay(10);
//    wavetable1.stop();
//    isPlaying = false;
//  }
}

void updateWavetable (float freq, float ampl) {
  int midiAmp = 127.0 * ampl;
  Serial.println(freq);
  delay(10);
//  wavetable1.setFrequency(freq);
  wavetable1.playFrequency(freq, midiAmp);
}
