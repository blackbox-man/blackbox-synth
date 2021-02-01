void playString(float freq, int stringNum) {
//  Serial.print("String plucked");
  float velocity = 0.8;
  
  string1.setFreq(freq);
  string2.setFreq(2*freq);
  string3.setFreq(3*freq);
  string4.setFreq(4*freq);

  string1.setDecay(0.5);
  string2.setDecay(0.5);
  string3.setDecay(0.5);
  string4.setDecay(0.5);

  string1.pluck(velocity);
  delay(2);
  string2.pluck(velocity);
  delay(2);
  string3.pluck(velocity);
  delay(2);
  string4.pluck(velocity);
  
//  if (stringNum < 4) {
//    switch (stringNum) {
//      case 0:
//        string1.pluck(velocity);
//        break;
//      case 1:
//        string2.pluck(velocity);
//        break;
//      case 2:
//        string3.pluck(velocity);
//        break;
//      case 3:
//        string4.pluck(velocity);
//        break;
//      default:
//        Serial.println("String overload!");
//    }
//  }
}
