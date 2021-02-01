void startTrill() {   //TODO:   add more trill sensors; set threshold and sensitivity
  int ret = trillSqr.begin(Trill::TRILL_SQUARE);
  if(ret != 0) {
    Serial.println(F("failed to initialise trill Square"));
    Serial.print(F("Error code: "));
    Serial.println(ret);
  }
  else {
    sqrPresent = true;
//    trillSqr calibration code!
  }
  int ret2 = trillBar1.begin(Trill::TRILL_BAR);
  if(ret2 != 0) {
    Serial.println(F("failed to initialise trill Square"));
    Serial.print(F("Error code: "));
    Serial.println(ret2);
  }
  else {
    bar1Present = true;
//    calibrate
  }
}


void getSquareData() {
  if (sqrPresent && trillSqrTimer > 5) {      // hardcoded frequency of update
//    Serial.print("Reading Trill Square...");
//    Serial.println(trillSqrTimer);
    trillSqr.read();
    
    if(trillSqr.getNumTouches() > 0) {      
      sqrNumTouches = trillSqr.getNumTouches();
      sqrNumHorizTouches = trillSqr.getNumHorizontalTouches();
      
      int newTouchLocX = trillSqr.touchLocation(0);
      if (newTouchLocX < 1793)                // hardcoded: upper limit of location-x; condition to random overshoot; TODO: calibrate for practical range, specially lower limit 
        sqrTouchLocX = newTouchLocX;
        
      int newTouchLocY = trillSqr.touchHorizontalLocation(0);
      if (newTouchLocY < 1793)                // hardcoded: upper limit of location-y
        sqrTouchLocY = newTouchLocY;
      
      sqrTouchSize = trillSqr.touchSize(0);
      sqrTouchHorizSize = trillSqr.touchHorizontalSize(0);

//      Serial.print(F("Square data: "));
//      Serial.print(sqrNumTouches);
//      Serial.print(F(" touches, "));
//      Serial.print(sqrNumHorizTouches);
//      Serial.print(F(" hor. touches, "));
//      Serial.print(F("X: "));
//      Serial.print(sqrTouchLocX);
//      Serial.print(F(", Y: "));      
//      Serial.print(sqrTouchLocY);
//      Serial.print(F(", SizeX: "));
//      Serial.print(sqrTouchSize);
//      Serial.print(F(", SizeY: "));
//      Serial.println(sqrTouchHorizSize);
      sqrTouchActive = true;
    }
    else if(sqrTouchActive) {
      // Print a single line when touch goes off
      Serial.println("0 0");
      sqrTouchActive = false;
      sqrNumTouches = 0;
      sqrTouchLocX = isSprungSqrX ? 0 : sqrTouchLocX;
      sqrTouchLocY = isSprungSqrY ? 0 : sqrTouchLocY;
    }
    trillSqrTimer = 0;
  }
}


void getBar1Data() {
  if (bar1Present && trillBar1Timer > 5) {
//    Serial.print("Reading Trill Square...");
//    Serial.println(trillBar1Timer);
    trillBar1.read();
  
    if(trillBar1.getNumTouches() > 0) {    
      bar1NumTouches = trillBar1.getNumTouches();    
      
//      for(int i = 0; i < trillBar1.getNumTouches(); i++) {      // temp: run only once for monophonic implementation; uncomment for polyphony
        for(int i = 0; i < 1; i++) {
          int tempTouchLoc = trillBar1.touchLocation(i);
          if (tempTouchLoc < 3200)                           // hardcoded: upper limit of location-x; condition to random overshoot; TODO: calibrate for practical range
            bar1TouchLoc = tempTouchLoc;
          bar1TouchSize = trillBar1.touchSize(i);
      }

//      Serial.print(F("Bar1 data: "));
//      Serial.print(bar1NumTouches);
//      Serial.print(F(" touches, "));
//      Serial.print(F("Loc: "));
//      Serial.print(bar1TouchLoc);
//      Serial.print(F(", Size: "));
//      Serial.println(bar1TouchSize);      
      bar1TouchActive = true;

//      playSynth();
    }
    else if(bar1TouchActive) {
      // Print a single line when touch goes off
      Serial.println("0 0");
      bar1TouchActive = false;
      bar1NumTouches = 0;
      bar1TouchLoc = isSprungBar1 ? 0 : bar1TouchLoc;
    }
    trillBar1Timer = 0;
  }
}


float barLocToFreq (float loc) {
  int baseMidi = noteRangeStart + (currentOctave - 1) * 12;
  float baseNoteFreq = NoteFreqMap[baseMidi][1];
  float newFreq = baseNoteFreq * pow(2, loc);
  return newFreq;
}
