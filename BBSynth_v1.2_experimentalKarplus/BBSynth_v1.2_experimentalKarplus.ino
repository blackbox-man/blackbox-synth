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
#include "chords.h"
#include "CKarplusStrong.h"

#define DEF_SYNTHMODULE   STRING
#define DEF_WAVEFORM      WAVEFORM_SAWTOOTH
#define DEF_FILTER_TYPE   LOWPASS
#define DEF_FILTER_FREQ   16000
#define DEF_FILTER_RES    2
#define DEF_REVERB_MIX    0
#define DEF_REVERB_DAMP   0.5
#define DEF_REVERB_SIZE   0
#define DEF_WAVESYNTH     WAVEFORM_SAWTOOTH
#define NUM_SYNTH_MODULES 7



KarplusStrongString      string1;
KarplusStrongString      string2;
KarplusStrongString      string3;
KarplusStrongString      string4;

// GUItool: begin automatically generated code
AudioSynthWaveform       waveformModulator;      //xy=91.5,566
AudioSynthSimpleDrum     drum1;          //xy=127,417
//AudioSynthKarplusStrong  string3;        //xy=130,193
//AudioSynthKarplusStrong  string4;        //xy=130,241
//AudioSynthKarplusStrong  string2;        //xy=132,143
//AudioSynthKarplusStrong  string1;        //xy=133,97
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
boolean sqrTouchActive = false;
int sqrNumTouches = 0;
int sqrNumHorizTouches = 0;
int sqrTouchLocX = 0;
int sqrTouchLocY = 0;
int sqrTouchSize = 0;
int sqrTouchHorizSize = 0;

Trill trillBar1;
boolean bar1TouchActive = false;
int bar1NumTouches = 0;
int bar1TouchLoc = 0;
int bar1TouchSize = 0;


// -------------------------------------
// DISPLAY STUFF
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

// Declaration for an SSD1306 display connected to 3rd I2C port (SDA2, SCL2 on pins 25, 24)
#define OLED_RESET 4    // Reset pin # (or -1 if sharing Arduino reset pin) not being used
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire2, OLED_RESET);
bool startupAnim = true;

// -------------------------------------
// KEYPAD STUFF
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {37, 36, 35, 34};
byte colPins[COLS] = {41, 40, 39, 38};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
byte ledPin = 13;
boolean blink = false;
boolean ledPin_state;
#define ARRAYSIZE(x)  (sizeof(x) / sizeof(x[0]))
char octUpKey = '#';
char octDnKey = '0';
char splFnKey = 'D';


// -------------------------------------
// SOUND STUFF

char noteMap[13][3] = {
  {'1', 'C', '\0'},
  {'2', 'C', '#'},
  {'3', 'D', '\0'},
  {'A', 'D', '#'},
  {'4', 'E', '\0'},
  {'5', 'F', '\0'},
  {'6', 'F', '#'},
  {'B', 'G', '\0'},
  {'7', 'G', '#'},
  {'8', 'A', '\0'},
  {'9', 'A', '#'},
  {'C', 'B', '\0'},
  {'*', 'C', '\0'}
};
int currentOctave = 3;
int octUpLimit = 6; //inclusive
int octLowLimit = 2;  //inclusive   //TODO: karplus strong library only allows till E2
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

//class Note {
//  public:
//    char chromNote[3];
//    char fullName[4];
//    int oct = 2;
//    Note() {
//      strcpy(chromNote, "");
//      strcpy(fullName, "");
//      oct = 2;
//    }
//    Note(char keyChar) {
//      oct = currentOctave;
//      switch (keyChar) {
//        case '1':
//          strcpy(chromNote, "C");
//          break;
//        case '3':
//          strcpy(chromNote, "D");
//          break;
//        case '4':
//          strcpy(chromNote, "E");
//          break;
//        case '5':
//          strcpy(chromNote, "F");
//          break;
//        case 'B':
//          strcpy(chromNote, "G");
//          break;
//        case '8':
//          strcpy(chromNote, "A");
//          break;
//        case 'C':
//          strcpy(chromNote, "B");
//          break;
//        case '*':
//          strcpy(chromNote, "C");
//          oct++;
//          break;
//        case '2':
//          strcpy(chromNote, "C#");
//          break;
//        case 'A':
//          strcpy(chromNote, "D#");
//          break;
//        case '6':
//          strcpy(chromNote, "F#");
//          break;
//        case '7':
//          strcpy(chromNote, "G#");
//          break;
//        case '9':
//          strcpy(chromNote, "A#");
//          break;
//        default:
//          break;
//      }
//      strcat(fullName, chromNote);
//      strcat(fullName, (char)oct);
//    }
//  private:
//    int num;
//};
//
//for (int i=0; i<5; i++) {
//  activeNotes[i] = new Note();
//}
//std::vector<Note> activeNotes(5, Note());
//Note newTempNote = Note();
//Note activeNotes[5] = {newTempNote, newTempNote, newTempNote, newTempNote, newTempNote};
//Note activeNotes[4] = {Note(), Note(), Note(), Note()};
//char noteList[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B", "C"};


// -------------------------------------
// TIMERS
int timer1 = 0;
int timer2 = 0;
int displayTimer = 0;
int displayTimerTemp = 0;

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
  keypad.getKeys();
//  update LED status
  updateLedBlink();  
//  scan macro controllers
  updateMacroControls();

  dispRefresh();
  timer1 = timer2;
  timer2 = millis()/1000;  
  if(timer2 - timer1 > 0) {
    Serial.print("Memory Peak: ");
    Serial.print(AudioMemoryUsageMax());
    AudioMemoryUsageMaxReset();
    Serial.print(" | Processor Peak: ");
    Serial.println(AudioProcessorUsageMax());
    AudioProcessorUsageMaxReset();    
  }
}
// -------------------------------------


void updateMacroControls() {
  getSquareData();
  getBar1Data();
}
