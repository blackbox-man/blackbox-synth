int getActiveKeysLength() {
  int len = 0;
  if (keypad.key[0].kchar != NO_KEY) {
    while (keypad.key[len].kchar != NO_KEY) {
      len++;
    }
  }
  return len;
}


void updateOctave(bool upDown) {  
  if (currentOctave < octUpLimit && currentOctave > octLowLimit)    
    currentOctave += upDown ? 1 : -1;  
  else if ((currentOctave == octUpLimit && upDown) || (currentOctave == octLowLimit && !upDown)) {
//    Serial.print("oct limit reached");    //TODO: indicate octave limite reached
  }
  else if (currentOctave == octLowLimit && upDown)
    currentOctave++;
  else if (currentOctave == octUpLimit && !upDown)
    currentOctave--;
}


int updateActiveNotes() {
  int nidx = 0; //TODO: polyphony length is hardcodedq
  for (int kidx = 0; kidx < getActiveKeysLength() && nidx < 4; kidx++) {
    //    TODO: simplify this if condition
    if ((keypad.key[kidx].kstate == 1 || keypad.key[kidx].kstate == 2) && keypad.key[kidx].kchar != keys[3][1] && keypad.key[kidx].kchar != keys[3][2] && keypad.key[kidx].kchar != keys[3][3]) {
      int foundRow = -1;
      for (int ridx=0; ridx<13; ridx++) {
        if (noteMap[ridx][0] == keypad.key[kidx].kchar) {
//        if (strchr(noteMap[ridx], keypad.key[kidx].kchar))
          foundRow = ridx;
        }
      }
      activeNotes[nidx][0] = noteMap[foundRow][1];
      activeNotes[nidx][1] = noteMap[foundRow][2];
      activeNotes[nidx][2] = (keypad.key[kidx].kchar == '*') ? ('0' + currentOctave + 1) : ('0' + currentOctave);
      nidx++;
    }
  }
  activeNotesLength = nidx;
  return nidx;
}

void cycleSynthMode(bool upDown) {
  if (activeSynthMode < 5 && activeSynthMode > 0)    
    activeSynthMode = upDown ? (activeSynthMode + 1) : (activeSynthMode - 1);  
  else if (activeSynthMode == 5 && upDown)
      activeSynthMode = 0;
  else if (activeSynthMode == 0 && !upDown)
      activeSynthMode = 5;
//    Serial.print("oct limit reached");    //TODO: indicate octave limite reached
  else if (activeSynthMode == 0 && upDown)
    activeSynthMode = activeSynthMode + 1;
  else if (activeSynthMode == 5 && !upDown)
    activeSynthMode = activeSynthMode - 1;
  
  selectSynth(activeSynthMode);
  displayActiveSynthMode();
}

void keypadEvent(KeypadEvent key) {   //TODO: only play new key, not all in list
  if(key) {
    updateActiveNotes();
    dispActiveNotes();
    
  //  MONITOR
  //  Serial.print(key);
  //  Serial.print(' ');
  //  Serial.println(keypad.key[keypad.findInList(key)].kstate);
  
    switch (keypad.key[keypad.findInList(key)].kstate) { //replace getState with getStateOfLastTrigerredKey
      case PRESSED:      
        if (key == octDnKey)
          updateOctave(0);                
        else if (key == octUpKey)
            updateOctave(1);
        else if (key == splFnKey) {
            cycleSynthMode(1);
            digitalWrite(ledPin, !digitalRead(ledPin));
            ledPin_state = digitalRead(ledPin);        // Remember LED state, lit or unlit.
        }
        else playNotes();      
        break;
  
      case RELEASED:      
        if (key == splFnKey) {
          digitalWrite(ledPin, ledPin_state);   // Restore LED state from before it started blinking.
          blink = false;
        }
        break;
  
      case HOLD:
        if (key == splFnKey) {
          blink = true;    // Blink the LED when holding the * key.
        }
        break;
      default:      
        break;
    }
  }
}
