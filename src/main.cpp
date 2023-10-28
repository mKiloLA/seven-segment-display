#include <Arduino.h>
#include <SevSeg.h>

SevSeg sevseg; // Instantiate a seven segment object
uint8_t numDigits = 4;
static unsigned long timer = millis();

byte digitPins[] = {2, 3, 4, 5}; // attach pins D1-D4
byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13}; // attach pins from A to DP in order
bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
byte hardwareConfig = COMMON_CATHODE; // See README.md for options
bool updateWithDelays = false; // Default 'false' is Recommended
bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
bool disableDecPoint = true; // Use 'true' if your decimal point doesn't exist or isn't connected. Then, you only need to specify 7 segmentPins[]

long randNumber;

void setup() {
  sevseg.begin(hardwareConfig, numDigits, digitPins, 
               segmentPins, resistorsOnSegments, 
               updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(100);

  // Set the random seed using noise on pin 0
  randomSeed(analogRead(0));
}

void loop() {
  // Generate a new number every two seconds
  if (millis() - timer >= 2000) {
    timer = millis();
    randNumber = random(9999);
    sevseg.setNumber(randNumber);
  }
  sevseg.refreshDisplay(); // Must run repeatedly
}

