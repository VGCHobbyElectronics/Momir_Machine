void setup() {

//TEST CODE TEST CODE//
//randomSeed(analogRead(A0));
setPinModes();
Wire.begin();
Serial.begin(9600);
mySerial.begin(19200);
printer.begin();
}

void setPinModes() {
  //Currently nothing here.
}
