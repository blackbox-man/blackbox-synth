void startDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  dispRefresh();
}

void startLED() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  ledPin_state = digitalRead(ledPin);
  delay(100);
  digitalWrite(ledPin, LOW);
}

void updateLedBlink() {
  if (blink) {
    digitalWrite(ledPin, !digitalRead(ledPin));   // Change the ledPin from Hi2Lo or Lo2Hi.
    delay(100);
  }
}

void resetDispTimer() {
  displayTimerTemp = displayTimer;
  displayTimer = millis();
}

long getDispTimer() {
  long timeElapsed = displayTimer-displayTimer;
  return timeElapsed;
}

void dispRefresh() {
  if(getDispTimer() > 750) {
    display.clearDisplay();
    display.display();
    resetDispTimer();
  }  
  if (startupAnim) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.cp437(true);
    display.write("velcm 2 kipadsinth");
    display.display();
    startupAnim = 0;
    delay(2000);
    display.clearDisplay();
    display.display();
    return;
  }
}

void dispActiveKeys() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.cp437(true);
  for (int i = 0; i < getActiveKeysLength(); i++) {
    display.write(keypad.key[i].kchar);
    if (i < getActiveKeysLength() - 1)
      display.write(' ');
  }
  display.display();
}

void dispActiveNotes() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.cp437(true);
  for (int i = 0; i < activeNotesLength; i++) {
    display.write(activeNotes[i][0]);
    if (activeNotes[i][1])
      display.write(activeNotes[i][1]);
    display.write(activeNotes[i][2]);
    if (i < activeNotesLength - 1)
      display.write('-');
  }
  display.display();
}

void displayActiveSynthMode() {  
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
