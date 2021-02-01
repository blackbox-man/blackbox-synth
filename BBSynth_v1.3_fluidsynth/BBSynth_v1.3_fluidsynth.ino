/*
16-10-2020:
  - 1 trill bar controlling pitch, square-x controlling volume
  - structured for modularity, to allow control by both trill bar and keys
  - only waveform osc working

11-10-2020: 
  - cleaning up code
  - implementing clean polyphony on input side (synth side remaining)
  - use midi note numbers instead of custom
  - key-press latency issue (288 ms between press & release)

*/


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>
#include <vector>
#include <string.h>
#include <Audio.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Trill.h>
#include <Math.h>
#include "chords.h"

#define DEF_SYNTHMODULE   WAVEFORM
#define DEF_WAVEFORM      WAVEFORM_SAWTOOTH
#define DEF_FILTER_TYPE   LOWPASS
#define DEF_FILTER_FREQ   16000
#define DEF_FILTER_RES    2
#define DEF_REVERB_MIX    0
#define DEF_REVERB_DAMP   0.5
#define DEF_REVERB_SIZE   0
#define DEF_WAVESYNTH     WAVEFORM_SAWTOOTH
#define NUM_SYNTH_MODULES 7


// GUItool: begin automatically generated code
AudioSynthWaveform       waveformModulator;      //xy=91.5,566
AudioSynthSimpleDrum     drum1;          //xy=127,417
AudioSynthKarplusStrong  string3;        //xy=130,193
AudioSynthKarplusStrong  string4;        //xy=130,241
AudioSynthKarplusStrong  string2;        //xy=132,143
AudioSynthKarplusStrong  string1;        //xy=133,97
AudioSynthWaveform       waveform1;      //xy=138,358
AudioSynthWavetable      wavetable1;     //xy=140,304
AudioSynthWaveformPWM    pwm1;           //xy=270,566
AudioSynthWaveformSineModulated sine_fm1;       //xy=276,526
AudioSynthWaveformModulated waveformMod1;   //xy=297,619
AudioSynthWaveform       waveformSubOsc;      //xy=297,685
AudioMixer4              mixerStrings;         //xy=392,117
AudioMixer4              mixerSynthBank2;         //xy=498,528
AudioMixer4              mixerSynthBank1;         //xy=504,302
AudioMixer4              mixerBankSelect;         //xy=681,422
AudioMixer4              mixerSubOsc;         //xy=843,539
AudioEffectEnvelope      envelope1;      //xy=887,272
AudioFilterStateVariable filter1;        //xy=1039,272
AudioEffectFlange        flange1;        //xy=1193,436
AudioEffectChorus        chorus1;        //xy=1195,380
AudioEffectFreeverb      freeverb1;      //xy=1197,326
AudioMixer4              mixerEffects;         //xy=1359,279
AudioOutputI2S           i2s1;           //xy=1514,279
AudioConnection          patchCord1(waveformModulator, sine_fm1);
AudioConnection          patchCord2(waveformModulator, pwm1);
AudioConnection          patchCord3(waveformModulator, 0, waveformMod1, 0);
AudioConnection          patchCord4(drum1, 0, mixerSynthBank1, 3);
AudioConnection          patchCord5(string3, 0, mixerStrings, 2);
AudioConnection          patchCord6(string4, 0, mixerStrings, 3);
AudioConnection          patchCord7(string2, 0, mixerStrings, 1);
AudioConnection          patchCord8(string1, 0, mixerStrings, 0);
AudioConnection          patchCord9(waveform1, 0, mixerSynthBank1, 2);
AudioConnection          patchCord10(wavetable1, 0, mixerSynthBank1, 1);
AudioConnection          patchCord11(pwm1, 0, mixerSynthBank2, 1);
AudioConnection          patchCord12(sine_fm1, 0, mixerSynthBank2, 0);
AudioConnection          patchCord13(waveformMod1, 0, mixerSynthBank2, 2);
AudioConnection          patchCord14(waveformSubOsc, 0, mixerSubOsc, 1);
AudioConnection          patchCord15(mixerStrings, 0, mixerSynthBank1, 0);
AudioConnection          patchCord16(mixerSynthBank2, 0, mixerBankSelect, 1);
AudioConnection          patchCord17(mixerSynthBank1, 0, mixerBankSelect, 0);
AudioConnection          patchCord18(mixerBankSelect, 0, mixerSubOsc, 0);
AudioConnection          patchCord19(mixerSubOsc, envelope1);
AudioConnection          patchCord20(envelope1, 0, filter1, 0);
AudioConnection          patchCord21(envelope1, 0, filter1, 1);
AudioConnection          patchCord22(filter1, 0, mixerEffects, 0);
AudioConnection          patchCord23(filter1, 0, freeverb1, 0);
AudioConnection          patchCord24(filter1, 0, chorus1, 0);
AudioConnection          patchCord25(filter1, 0, flange1, 0);
AudioConnection          patchCord26(flange1, 0, mixerEffects, 3);
AudioConnection          patchCord27(chorus1, 0, mixerEffects, 2);
AudioConnection          patchCord28(freeverb1, 0, mixerEffects, 1);
AudioConnection          patchCord29(mixerEffects, 0, i2s1, 0);
AudioConnection          patchCord30(mixerEffects, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=845.7677001953125,656.5151977539062
// GUItool: end automatically generated code



// -------------------------------------
// TRILL STUFF      TODO: allow for multiple trill sensor
Trill trillSqr;
bool sqrPresent = false;
bool sqrTouchActive = false;
int sqrNumTouches;
int sqrNumHorizTouches;
int sqrTouchLocX;
int sqrTouchLocY;
int sqrTouchSize;
int sqrTouchHorizSize;
bool isSprungSqrX;
bool isSprungSqrY;

Trill trillBar1;
bool bar1Present = false;
boolean bar1TouchActive = false;
int bar1NumTouches;
int bar1TouchLoc;
int bar1TouchSize;
bool isSprungBar1;


// -------------------------------------
// DISPLAY STUFF
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4    // Reset pin # (or -1 if sharing Arduino reset pin) not being used
// Declaration for an SSD1306 display connected to 3rd I2C port (SDA2, SCL2 on pins 25, 24)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool startupAnim = true;
boolean globalBlink = false;
byte ledPin = 13;
boolean ledPin_state;
// -------------------------------------
// KEYPAD STUFF
const byte ROWS = 4;
const byte COLS = 4;
#define ARRAYSIZE(x)  (sizeof(x) / sizeof(x[0]))
const char upperC = 'D';
char keys[ROWS][COLS] = {
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', 'A', 'B', 'C'},
  {'D', 'E', 'F', 'G'}
};
byte rowPins[ROWS] = {0, 1, 2, 3};
byte colPins[COLS] = {7, 6, 5, 4};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
char octUpKey = 'F';
char octDnKey = 'E';
char splFnKey = 'G';

elapsedMillis keypadTimer;
// -------------------------------------
// SOUND STUFF

const int keyboardLength = 13; // 1 octave keyboad
char noteMap[keyboardLength][3] = {
  {'1', 'C', '\0'},
  {'2', 'C', '#'},
  {'3', 'D', '\0'},
  {'4', 'D', '#'},
  {'5', 'E', '\0'},
  {'6', 'F', '\0'},
  {'7', 'F', '#'},
  {'8', 'G', '\0'},
  {'9', 'G', '#'},
  {'A', 'A', '\0'},
  {'B', 'A', '#'},
  {'C', 'B', '\0'},
  {'D', 'C', '\0'}
};

const int midiA0 = 21;
const int noteRangeStart = 24;  //i.e. start from C1; this value should only be between 24 and 35 (inclusive) so as not to interfere with octave setting
const int polyLength = 8;
int activePolyLength = 0;
int polyNotes[8];
int currentOctave = 1;
const int octUpLimit = 6; //inclusive
const int octLowLimit = 2;  //inclusive   //TODO: karplus strong library only allows till E2
bool loopEmpty = true;
int activeNotesLength = 0;
char activeNotes[8][3];
enum synth_mode {
  STRING = 0,
  WAVETABLE = 1,
  WAVEFORM = 2,
  DRUM = 3,
  SINEFM = 4,
  PWM = 5,
  WAVEFM = 6
};
synth_mode activeSynthMode = DEF_SYNTHMODULE;


// -------------------------------------
// TIMERS
elapsedMillis statusTimer;
elapsedMillis displayTimer;
elapsedMillis loopTimer;
elapsedMillis trillSqrTimer;
elapsedMillis trillBar1Timer;

void setup() {
  Serial.begin(115200);
  startTrill();
//  Serial.begin(9600);
  startLED();
  keypad.addEventListener(keypadEvent);
  startDisplay();
  setupAudio();
  envelope1.noteOn();
}

void loop() {

//  scan note input
//  keypad.getKeys();

//  update LED status
//  updateLedBlink();

//  update readings from physical inputs - Trills, rot. encoders, pots
  updateInputData();
  
//  copy input data to mapped internal parameters
//  updateMappedParams();
  
  playFluidSynth();

//  clear screen if timer is not running, i.e. showing something
  if (displayTimer > 750) {
    dispRefresh();
    displayTimer = 0;
  }

//  show processor and memory usage stats every 1 second  
//  updatePerformanceStats();

//  update any other panel lights
  updateStatusLights();

//  Loop cycle length test
//    if (loopTimer > 10) {
//      Serial.print("Loop cycle: ");
//      Serial.println(loopTimer);
//      loopTimer = 0;
//    }
}
// -------------------------------------

void updatePerformanceStats() {
    if(statusTimer >= 1000) {
    statusTimer = statusTimer - 1000;
    Serial.print("Memory Peak: ");
    Serial.print(AudioMemoryUsageMax());
    AudioMemoryUsageMaxReset();
    Serial.print(" | Processor Peak: ");
    Serial.println(AudioProcessorUsageMax());
    AudioProcessorUsageMaxReset();    
  }
}

void updateInputData() {  
  getSquareData();
  getBar1Data();
  getEncsData();
  getPotsData();
}
