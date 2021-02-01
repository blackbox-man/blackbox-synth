void setupAudio() {
  AudioMemory(160);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.6);
  
  waveform1.begin(0, NOTE_C2, DEF_WAVESYNTH); //start waveform synth; hardcoded default frequency
  for (int i=0; i<4; i++) {       //start string synth
    mixerStrings.gain(i, 0.8);
  }

  setEnvelope(400, 10, 1, 700);   //TODO: better envelope implementation

  selectSynth(activeSynthMode);
//  wavetable1.setInstrument(); // TODO: wavetable instruments
  mixerSubOsc.gain(0, 1);
  mixerSubOsc.gain(1, 0);
  mixerSubOsc.gain(2, 0);

//playWaveform(NOTE_C1, true);
  
  mixerEffects.gain(0, 1-DEF_REVERB_MIX);    //Reverb mix
  mixerEffects.gain(1, DEF_REVERB_MIX);
  filter1.frequency(DEF_FILTER_FREQ);
  filter1.resonance(DEF_FILTER_RES);
  freeverb1.damping(DEF_REVERB_DAMP);
  freeverb1.roomsize(DEF_REVERB_SIZE);
}

void setEnvelope(float atk, float dec, float sus, float rel) {
  envelope1.attack(atk);
  envelope1.decay(dec);
  envelope1.sustain(sus);
  envelope1.release(rel);
}

void setFilterCutoff(float cutoff) {
  filter1.frequency(cutoff);
}

void selectSynth (int module) {
  if(module < 4 && module > -1) {
    for (int i=0; i<4; i++) {
      mixerSynthBank1.gain(i, i == module ? 1 : 0);
    }
    mixerBankSelect.gain(0, 1);
  }
  else {
    for (int i=4; i<8; i++) {
      mixerSynthBank2.gain(i, i == module ? 1 : 0);
    }
    mixerBankSelect.gain(1, 1);
  }
  Serial.print("synth module loaded: ");
  Serial.println(module);
}

float noteToFreq(char note[]) {  
  float freq = 0;
  switch (note[0]) {
    case 'C':
      freq = note[1] ? NOTE_Cs1 : NOTE_C1;
      break;    
    case 'D':
      freq = note[1] ? NOTE_Ds1 : NOTE_D1;
      break;
    case 'E':
      freq = NOTE_E1;
      break;
    case 'F':
      freq = note[1] ? NOTE_Fs1 : NOTE_F1;
      break;
    case 'G':
      freq = note[1] ? NOTE_Gs1 : NOTE_G1;
      break;
    case 'A':
      freq = note[1] ? NOTE_As1 : NOTE_A1;
      break;
    case 'B':
      freq = NOTE_B1;
      break;
    default:
      break;
  }
  
  if (note[2]) {
    int oct = note[2] - 48;
    freq = freq * pow(2,(oct-1));
  }
//  Serial.println(freq);
  return freq;
}


// handles note on and off events; does not handle velocity, polyphony index, synth selection.
void playMidiNote(int midiNote, bool onOff) {
//  envelope1.noteOn();
  float freq = NoteFreqMap[midiNote][1];
  float ampl = (float)sqrTouchLocY / 1792.0;
  int nidx = activePolyLength - 1;

  playFreqNote(freq, ampl, onOff);
}

void playFreqNote (float freq, float ampl, bool onOff) {
  int nidx = activePolyLength - 1;
  switch(activeSynthMode) {
    case STRING:
      playString(freq, nidx);
      break;
    case WAVETABLE:
      playString(freq, nidx);
      break;
    case WAVEFORM:
      playWaveform(freq, ampl, onOff);
      break;
    case DRUM:
      playString(freq, nidx);
      break;
    case SINEFM:
      playString(freq, nidx);
      break;
    case PWM:
      playString(freq, nidx);
      break;
    case WAVEFM:
      playString(freq, nidx);
      break;
  }
}

void updateMappedParams() {
  
}


void playFluidSynth () {
  bool onOff = bar1NumTouches > 0 ? true : false;
  float normLocation = (float)bar1TouchLoc / 3195.0;
  float freq = barLocToFreq(normLocation);
  float normAmpl = (float)sqrTouchLocY / 1792.0;
  playFreqNote(freq, normAmpl, onOff);
//    playWaveform(freq, normAmpl, onOff);
//    updateWaveform(freq, normAmpl);
//    Serial.print(normLocation);
//    Serial.print(" - ");
//    Serial.println(freq);
//    delay(10);
}
