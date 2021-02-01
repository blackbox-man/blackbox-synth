void startTrill() {   //TODO:   add more trill sensors; set threshold and sensitivity
  int ret = trillSqr.begin(Trill::TRILL_SQUARE);
  if(ret != 0) {
    Serial.println("failed to initialise trill Square");
    Serial.print("Error code: ");
    Serial.println(ret);
  }
  int ret2 = trillBar1.begin(Trill::TRILL_BAR);
  if(ret2 != 0) {
    Serial.println("failed to initialise trill Square");
    Serial.print("Error code: ");
    Serial.println(ret2);
  }
}


void getSquareData() {
//  Serial.print("Reading Trill Square...");
  delay(50);
  trillSqr.read();

  if(trillSqr.getNumTouches() > 0) {    
    sqrNumTouches = trillSqr.getNumTouches();
    sqrNumHorizTouches = trillSqr.getNumHorizontalTouches();
    Serial.print(sqrNumTouches);
    Serial.print(" ");
    Serial.print(sqrNumHorizTouches);
    Serial.print(" ");
    
    for(int i = 0; i < trillSqr.getNumTouches(); i++) {
        int tempTouchLocX = trillSqr.touchLocation(i);
        if (tempTouchLocX < 1793)
          sqrTouchLocX = tempTouchLocX;
        sqrTouchSize = trillSqr.touchSize(i);
        Serial.print(tempTouchLocX);
        Serial.print(" ");
        Serial.print(sqrTouchSize);
        Serial.print(" ");
    }
    for(int i = 0; i < trillSqr.getNumHorizontalTouches(); i++) {
        int tempTouchLocY = trillSqr.touchHorizontalLocation(i);
        if (tempTouchLocY < 1793)
          sqrTouchLocY = tempTouchLocY;
        sqrTouchHorizSize = trillSqr.touchHorizontalSize(i);
        Serial.print(tempTouchLocY);
        Serial.print(" ");
        Serial.print(sqrTouchHorizSize);
        Serial.print(" ");
    }

    Serial.println("");
    sqrTouchActive = true;
  }
  else if(sqrTouchActive) {
    // Print a single line when touch goes off
    Serial.println("0 0");
    sqrTouchActive = false;
  }
}

void getBar1Data() {
//  Serial.print("Reading Trill Square...");
  delay(50);
  trillBar1.read();

  if(trillBar1.getNumTouches() > 0) {    
    bar1NumTouches = trillBar1.getNumTouches();    
    Serial.print(bar1NumTouches);    
    Serial.print(" ");
    
    for(int i = 0; i < trillBar1.getNumTouches(); i++) {
        int tempTouchLoc = trillBar1.touchLocation(i);
        if (tempTouchLoc < 1793)
          bar1TouchLoc = tempTouchLoc;
        bar1TouchSize = trillBar1.touchSize(i);
        Serial.print(tempTouchLoc);
        Serial.print(" ");
        Serial.print(bar1TouchSize);
        Serial.print(" ");
    }
    
    Serial.println("");
    bar1TouchActive = true;
  }
  else if(bar1TouchActive) {
    // Print a single line when touch goes off
    Serial.println("0 0");
    bar1TouchActive = false;
  }
}
