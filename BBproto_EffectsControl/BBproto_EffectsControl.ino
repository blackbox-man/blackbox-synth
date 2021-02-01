#include <Trill.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=223,353
AudioEffectDelay         delay1;         //xy=595,397
AudioMixer4              mixer1;         //xy=599,206
AudioEffectFreeverb      freeverb1;      //xy=771,409
AudioMixer4              mixer2;         //xy=942,370
AudioOutputI2S           i2s1;           //xy=1167,318
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playSdWav1, 1, mixer1, 1);
AudioConnection          patchCord3(delay1, 0, mixer1, 2);
AudioConnection          patchCord4(delay1, 0, mixer2, 0);
AudioConnection          patchCord5(delay1, 0, freeverb1, 0);
AudioConnection          patchCord6(mixer1, delay1);
AudioConnection          patchCord7(freeverb1, 0, mixer2, 1);
AudioConnection          patchCord8(mixer2, 0, i2s1, 0);
AudioConnection          patchCord9(mixer2, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=626.7677307128906,589.5151977539062
// GUItool: end automatically generated code


#include <Bounce.h>
Bounce button0 = Bounce(0, 5);

Trill trillSensor;
boolean touchActive = false;

void setup() {
  Serial.begin(115200);
  int ret = trillSensor.begin(Trill::TRILL_SQUARE);
  if(ret != 0) {
    Serial.println("failed to initialise trillSensor");
    Serial.print("Error code: ");
    Serial.println(ret);
  }
  
//  Serial.begin(9600);
  pinMode(0, INPUT_PULLUP);
  AudioMemory(160);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.55);
//  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
//  sgtl5000_1.micGain(36);
  mixer1.gain(0, 0.5);
  mixer1.gain(1, 0.5);
  mixer1.gain(2, 0);
  delay1.delay(0, 300);
  
  mixer2.gain(0, 1);
  mixer2.gain(1, 0);
  freeverb1.damping(0.5);
  freeverb1.roomsize(0);
  delay(1000);
}

void playFile(const char *filename)
{
  Serial.print("Playing file: ");
  Serial.println(filename);

  // Start playing the file.  This sketch continues to
  // run while the file plays.
  playSdWav1.play(filename);

  // A brief delay for the library read WAV info
  delay(5);

  // Simply wait for the file to finish playing.
  while (playSdWav1.isPlaying()) {  
    setDelayMix();
    setReverbMix();
//    setDelayTime();
    delay(50);
    // uncomment these lines if you audio shield
    // has the optional volume pot soldered
//    float vol = analogRead(A12);
//    vol = vol / 1024;
//     sgtl5000_1.volume(vol);
  }
}

void setDelayMix() {
//  Serial.print("setting delay mix...");
//  // uncomment for A3 knob to control the feedback level
//  int knob = analogRead(A12);
////  Serial.print("Delay mix: ");
////  Serial.print(knob);
////  Serial.print("=");
//  float feedback = (float)knob / 1050.0;
////  Serial.println(feedback);
//  mixer1.gain(0, 0.5-(feedback/4));
//  mixer1.gain(1, 0.5-(feedback/4));
//  mixer1.gain(2, 0.2+feedback/2);


  if(trillSensor.getNumTouches() > 0) {
    float feedback = 0;
    for(int i = 0; i < trillSensor.getNumTouches(); i++) {        
        int touchLocy = trillSensor.touchHorizontalLocation(i);
        int touchSiz = trillSensor.touchSize(i);
        Serial.print(touchLocy);
        Serial.print(" ");
        Serial.print(touchSiz);
        Serial.print(" ");
        if (touchLocy < 1793)
          feedback = (float)touchLocy / 1792;        
        mixer1.gain(0, 0.5-(feedback/4));
        mixer1.gain(1, 0.5-(feedback/4));
        mixer1.gain(2, feedback/2);
    }
    Serial.println("");
    touchActive = true;
  }
  else if(touchActive) {
    // Print a single line when touch goes off
    Serial.println("0 0");
    touchActive = false;
  }
}

void setReverbMix() {
//  Serial.print("setting reverb mix...");
//  // uncomment for A3 knob to control the feedback level
//  int knob = analogRead(A12);
////  Serial.print("Reverb mix: ");
////  Serial.print(knob);
////  Serial.print("=");
//  float feedback = (float)knob / 2100.0;
////  Serial.println(feedback);
//  mixer2.gain(0, 1-feedback);
//  mixer2.gain(1, feedback);


  trillSensor.read();
  if(trillSensor.getNumTouches() > 0) {
    float feedback = 0;
    for(int i = 0; i < trillSensor.getNumTouches(); i++) {        
        int touchLocx = trillSensor.touchLocation(i);
        int touchSiz = trillSensor.touchSize(i);
        Serial.print(touchLocx);
        Serial.print(" ");
        Serial.print(touchSiz);
        Serial.print(" ");        
        if (touchLocx < 1793)
          feedback = (float)touchLocx / 1792;
        mixer2.gain(0, 1-(feedback));
        mixer2.gain(1, feedback);
    }
    Serial.println("");
    touchActive = true;
  }
  else if(touchActive) {
    // Print a single line when touch goes off
    Serial.println("0 0");
    touchActive = false;
  }
}

void setDelayTime() {
  Serial.print("setting delay time...");
  int knob = analogRead(A12);
  Serial.print("Delay time: ");
  Serial.print(knob);
  Serial.print("=");
  float delayTime = map(knob, 20, 997, 0, 600);
//  float delayTime = (float)knob / 1050.0;
  Serial.println(delayTime );
  delay1.delay(0, delayTime);
}

void loop() {
  playFile("SDTEST1.WAV");  // filenames are always uppercase 8.3 format
  delay(500);
  playFile("SDTEST2.WAV");
  delay(500);
  playFile("SDTEST3.WAV");
  delay(500);
  playFile("SDTEST4.WAV");
  delay(1500);
//  Serial.print("knob is ");
//  // uncomment for A3 knob to control the feedback level
//  int knob = analogRead(26);
//  Serial.print(knob);
//  Serial.print("=");
//  float feedback = (float)knob / 1050.0;
//  Serial.println(feedback);
//  mixer1.gain(2, feedback);

  // uncomment for pin 0 button to double the feedback (allowing unstable)
  /*
  button0.update();
  if (button0.read() == LOW) {
    mixer1.gain(3, feedback * 2.0);
  }
  */
}
