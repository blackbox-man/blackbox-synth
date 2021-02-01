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

//  trigger notes pressed or released, i.e. adds/removes them from current list; will also trigger note on/off if asked to, otherwise you must do it separately after this function
void noteOnOff(int note, bool onOff, bool triggerPlay) {
//  handling multiple keys pressed and released
  for (int i=0; i<polyLength; i++) {
    if (!polyNotes[i] && onOff) {
      polyNotes[i] = note;
      activePolyLength++;  // = i;
      break;
    }
    else if (polyNotes[i] && !onOff) {
      if (polyNotes[i] == note) {
        for (int j=i; j<activePolyLength; j++) {
          polyNotes[j] = (j == activePolyLength-1) ? 0 : polyNotes[j+1];
        }
        activePolyLength--;
        break;
      }
    }
  }
//  actual triggering of the current note
  if (triggerPlay) {
    playMidiNote(note, onOff);      //common function for note on and off
//    if (onOff)  noteOn(note);
//    else        noteOff(note);
  }
}


//int updateActiveNotes() {
//  int nidx = 0; //TODO: polyphony length is hardcodedq
//  for (int kidx = 0; kidx < getActiveKeysLength() && nidx < 4; kidx++) {
//    //    TODO: simplify this if condition
//    if ((keypad.key[kidx].kstate == 1 || keypad.key[kidx].kstate == 2) && keypad.key[kidx].kchar != keys[3][1] && keypad.key[kidx].kchar != keys[3][2] && keypad.key[kidx].kchar != keys[3][3]) {
//      int foundRow = -1;
//      for (int ridx=0; ridx<13; ridx++) {
//        if (noteMap[ridx][0] == keypad.key[kidx].kchar) {
////        if (strchr(noteMap[ridx], keypad.key[kidx].kchar))
//          foundRow = ridx;
//        }
//      }
//      activeNotes[nidx][0] = noteMap[foundRow][1];
//      activeNotes[nidx][1] = noteMap[foundRow][2];
//      activeNotes[nidx][2] = (keypad.key[kidx].kchar == upperC) ? ('0' + currentOctave + 1) : ('0' + currentOctave);
//      nidx++;
//    }
//  }
//  activeNotesLength = nidx;
//  return nidx;
//}


void cycleSynthMode(bool upDown) {
  if (activeSynthMode < 5 && activeSynthMode > 0)    
    activeSynthMode = upDown ? (activeSynthMode + 1) : (activeSynthMode - 1);  
  else if (activeSynthMode == 5 && upDown)
      activeSynthMode = 0;
  else if (activeSynthMode == 0 && !upDown)
      activeSynthMode = 5;
  else if (activeSynthMode == 0 && upDown)
    activeSynthMode = activeSynthMode + 1;
  else if (activeSynthMode == 5 && !upDown)
    activeSynthMode = activeSynthMode - 1;
  
  selectSynth(activeSynthMode);
  displayActiveSynthMode();
}

int keyToNote (char key) {
  int note = 0;
  for (int i=0; i<keyboardLength; i++) {
    if (noteMap[i][0] == key) {
      note = noteRangeStart + i;        //specifying the first note of the keyboard
      note = note + (currentOctave-1)*12;   //accounting for which octave is currently selected
      break;
    }
  }
  return note;
}

void keypadEvent (KeypadEvent key) {
  if(key) {
//    updateActiveNotes();
//    dispActiveKeys();
//    dispActiveNotes();
//    playNotes();

  //  MONITOR
  //  Serial.print(key);
  //  Serial.print(' ');
  //  Serial.println(keypad.key[keypad.findInList(key)].kstate);

    int keyState = keypad.key[keypad.findInList(key)].kstate;
    int keyNote = 0;
//    if (keyState == PRESSED)
    switch (keyState) {
      case PRESSED:      
        if (key == octDnKey)      updateOctave(0);
        else if (key == octUpKey) updateOctave(1);
        else if (key == splFnKey) {
            cycleSynthMode(1);
            digitalWrite(ledPin, !digitalRead(ledPin));
            ledPin_state = digitalRead(ledPin);
        }
        else {
          keyNote = keyToNote(key);
          noteOnOff(keyNote, true, true);
          dispPolyNotes();
        }
//        Serial.print("2nd keypress after: ");
//        Serial.println(keypadTimer);
//        Serial.println("Key pressed...");
//        keypadTimer = 0;
        break;
  
      case RELEASED:      
//        Serial.print("Released after: ");
//        Serial.println(keypadTimer);
        if (key == splFnKey) {
          digitalWrite(ledPin, ledPin_state);   // Restore LED state from before it started blinking.
          globalBlink = false;
        }
        else if (key != octDnKey && key != octUpKey) {
          keyNote = keyToNote(key);          
          noteOnOff(keyNote, false, true);
          dispPolyNotes();
        }
        break;
  
      case HOLD:
        if (key == splFnKey) {
          globalBlink = true;    // Blink the LED when holding the * key. Secondary function
        }
        break;
      default:      
        break;
    }
  }
}
