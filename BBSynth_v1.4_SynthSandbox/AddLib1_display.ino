//  Look for display on I2C bus; startup animation
//  TODO: Add functions for any other type of display
void startDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 not found!"));
  }
  else if (startupAnim) {
    display.setRotation(2);
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.cp437(true);
    display.write("velcm 2 kipadsinth");
    display.display();
    startupAnim = 0;
    delay(2000);
    display.clearDisplay();
    display.display();
  }
}


//  Initialise all LEDs; blink onboard LED once on startup
void startLED() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  ledPin_state = digitalRead(ledPin);
  delay(100);
  digitalWrite(ledPin, LOW);
}


//  soon to be OBSOLETE: blinks onboard LED if set to do so globally
//  TODO: use millis() instead of delay()
void updateLedBlink() {
  if (globalBlink) {
    digitalWrite(ledPin, !digitalRead(ledPin));   // Change the ledPin from Hi2Lo or Lo2Hi.
    delay(100);
  }
}


//  TODO: update all panel indicator lights
void updateStatusLights() {
  
}


//  Resets the display timer [e.g. x milliseconds completed -> clear display -> reset, or reset timer -> show sth temporary -> check for timer]
void resetDispTimer() {
//  displayTimerTemp = displayTimer;
  displayTimer = 0;
}


//  Returns milliseconds elapsed since timer was last reset [e.g. if show sth temporary -> getDispTimer() > x then do sth like clear it]
long getDispTimer() {
//  long timeElapsed = displayTimer-displayTimerTemp;
//  return timeElapsed;
  return displayTimer;
}


//  Basically clears display.
//  TODO: hard clear of display not possible
void dispRefresh() {
//  if(getDispTimer() > 750) {    
    display.clearDisplay();
    display.setCursor(0, 0);
    display.display();
//    resetDispTimer();
//  }
}


//  OBSOLETE
//void dispActiveKeys() {
//  display.clearDisplay();
//  display.setTextSize(2);
//  display.setTextColor(SSD1306_WHITE);
//  display.setCursor(0, 0);
//  display.cp437(true);
//  for (int i = 0; i < getActiveKeysLength(); i++) {
//    display.write(keypad.key[i].kchar);
//    if (i < getActiveKeysLength() - 1)
//      display.write(' ');
//  }
//  display.display();
//}


//  soon to be OBSOLETE
//void dispActiveNotes() {
//  display.clearDisplay();
//  display.setTextSize(2);
//  display.setTextColor(SSD1306_WHITE);
//  display.setCursor(0, 0);
//  display.cp437(true);
//  for (int i = 0; i < activeNotesLength; i++) {
//    display.write(activeNotes[i][0]);
//    if (activeNotes[i][1])
//      display.write(activeNotes[i][1]);
//    display.write(activeNotes[i][2]);
//    if (i < activeNotesLength - 1)
//      display.write('-');
//  }
//  display.display();
//}


//  display all notes currently being played
void dispPolyNotes() {
//  display.clearDisplay();
//  display.setCursor(0, 0);
  dispRefresh();
  for (int i = 0; i < activePolyLength; i++) {
    int noteRow = polyNotes[i] - midiA0;
    display.write(noteNameMap[noteRow][1]);
    if (noteNameMap[noteRow][2])    display.write(noteNameMap[noteRow][2]);
    display.write(noteNameMap[noteRow][3]);
    if (i < activePolyLength - 1)   display.write('-');
  }
  display.display();
}


//  displays the synth mode when it is changes
void displayActiveSynthMode() {  
//  display.clearDisplay();  
  dispRefresh();
  switch(activeSynthMode) {
    case STRING:
      display.write("String");
      display.display();
      break;
    case WAVETABLE:
      display.write("WAVETABLE");
      display.display();
      break;
    case WAVEFORM:
      display.write("WAVEFORM: ");
      display.display();
      break;
    case DRUM:
      display.write("DRUM");
      display.display();
      break;
    case SINEFM:
      display.write("SINE FM");
      display.display();
      break;
    case PWM:
      display.write("PWM");
      display.display();
      break;
    case WAVEFM:
      display.write("WAVE FM");
      display.display();
      break;
  }
  resetDispTimer();
}
