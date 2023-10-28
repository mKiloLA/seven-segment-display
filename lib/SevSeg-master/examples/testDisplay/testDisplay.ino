/* SevSeg testDisplay
 
 Copyright 2023 Dean Reading
 
 This example is helpful to test a display by cycling through each segment,
 then each digit.

 You can simulate this sketch on Wokwi
 https://wokwi.com/projects/371856060223388673
 */

#include <SevSeg.h>

void nextState(); // Forward declaration of function

SevSeg sevseg; // Instantiate a seven segment object
uint8_t state = 0;
uint8_t numDigits;
const uint32_t INTERVAL_MS = 500; // The time spent in each state

// setup
/******************************************************************************/
void setup() {
  numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected. Then, you only need to specify 7 segmentPins[]

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);

  Serial.println("SevSeg testDisplay.ino");
  Serial.println("This sketch will cycle through all segments, then all digits");
  Serial.println("2023 Dean Reading");
  Serial.begin(115200);
}

// loop
/******************************************************************************/
void loop() {
  static unsigned long timer = millis();
  static int deciSeconds = 0;
  
  if (millis() - timer >= 100) {
    timer += 100;
    deciSeconds++; // 100 milliSeconds is equal to 1 deciSecond
    
    if (deciSeconds == 10000) { // Reset to 0 after counting for 1000 seconds.
      deciSeconds=0;
    }
    sevseg.setNumber(deciSeconds, 1);
  }

  sevseg.refreshDisplay(); // Must run repeatedly
}