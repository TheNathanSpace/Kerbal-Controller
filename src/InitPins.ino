#include <Arduino.h>

void initPins() {

  // Raw pins
  pinMode(iTranslateX, INPUT);
  pinMode(iTranslateY, INPUT);
  pinMode(iTranslateZ, INPUT);

  pinMode(iOrientX, INPUT);
  pinMode(iOrientY, INPUT);
  pinMode(iOrientZ, INPUT);

  pinMode(iThrottleValue, INPUT);
  pinMode(oMotorOn, OUTPUT);
  pinMode(oMotorUp, OUTPUT);
  pinMode(oMotorDown, OUTPUT);

  // Debounced buttons
  bIva.begin();
  bMapView.begin();
  bDockingMode.begin();

  tsArmStage.begin();
  tsArmAbort.begin();
  bTriggerStage.begin();
  bTriggerAbort.begin();

  for (int CAG = 1; CAG < 10; CAG++) {
    CAGArray[CAG].begin();
  }

  tsBrakes.begin();
  tsGear.begin();
  tsLights.begin();
  tsRCS.begin();

  tsSAS.begin();
  for (int SASPin = 1; SASPin < 10; SASPin++) {
    SASArray[SASPin].begin();
  }

  bTranslateButton.begin();
  bOrientButton.begin();

  tsRocketMode.begin();
  tsFlyPrecision.begin();
  tsThrottleSensitivity.begin();
  bMinThrottle.begin();
  bMaxThrottle.begin();

}
