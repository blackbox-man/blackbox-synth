void playString(float freq, int stringNum) {
//  Serial.print("String plucked");
  float velocity = 0.8;
  if (stringNum < 4) {
    switch (stringNum) {
      case 0:
        string1.noteOn(freq, velocity);
        break;
      case 1:
        string2.noteOn(freq, velocity);
        break;
      case 2:
        string3.noteOn(freq, velocity);
        break;
      case 3:
        string4.noteOn(freq, velocity);
        break;
      default:
        Serial.println("String overload!");
    }
  }
}
