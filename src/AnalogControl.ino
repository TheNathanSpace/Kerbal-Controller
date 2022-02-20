#include <Arduino.h>

// SOURCE: https://github.com/Richi0D/KerbalController-Simpit/blob/master/Output.ino

void updateJoysticks() {
    //create structs and masks
    rotationMessage rotationMsg;
    rotationMsg.mask=1|2|4;
    translationMessage translationMsg;
    translationMsg.mask=1|2|4;    
    wheelMessage wheelMsg;
    wheelMsg.mask=1|2; 

    // MAKE SURE THE BOOLEAN IS SET UP CORRECTLY, ESPECIALLY WITH THE PULLUP
    // Precision on = precision mode. Rocket on = rocket mode.
     if((!checkButton(tsFlyPrecision)) and (checkButton(tsRocketMode)){
       flymode = 0;} // rocket mode
     else if((!checkButton(tsFlyPrecision)) and (!checkButton(tsRocketMode))){
       flymode = 1;} // plane mode
     else if((checkButton(tsFlyPrecision)) and (checkButton(tsRocketMode))){
       flymode = 2;} // rocket mode + precision      
     else if((checkButton(tsFlyPrecision)) and (!checkButton(tsRocketMode))){
       flymode = 3;} // plane mode + precision
     else {flymode = 0;}

    int deadzone = 50;
    int deadzonethrottle = 25;
    
    switch (flymode) {
    case 0: // Rocket mode
        mappedThrottleValue = constrain(map(analogRead(iThrottleValue), 1023 - deadzonethrottle, 0 + deadzonethrottle, 0, 32767), 0, 32767); // Maps 0-1028 throttle values to  0-32767 values. Deletes everything outside of those bounds (because they'd be erroneous).
        wheelMsg.throttle = constrain(map(analogRead(iThrottleValue), 1023 - deadzonethrottle, 0 + deadzonethrottle, 0, 32767), 0, 32767);
    
        if (analogRead(iOrientX) >= 512 + deadzone) {
            rotationMsg.yaw = constrain(map(analogRead(iOrientX), 512 + deadzone, 1023, 0, 32767), 0, 32767);
            wheelMsg.steer = constrain(map(analogRead(iOrientX), 1023, 512 + deadzone, -32767, 0), -32767, 0);
        }
        else if (analogRead(iOrientX) <= 512 - deadzone) {
            rotationMsg.yaw = constrain(map(analogRead(iOrientX), 0, 512 - deadzone, -32767, 0), -32767, 0);
            wheelMsg.steer = constrain(map(analogRead(iOrientX), 512 - deadzone, 0, 0, 32767), 0, 32767);
        }
        else {
            rotationMsg.yaw = 0;
            wheelMsg.steer = 0;
        }
        if (analogRead(iOrientY) >= 512 + deadzone) {
            rotationMsg.pitch = constrain(map(analogRead(iOrientY), 512 + deadzone, 1023, 0, 32767), 0, 32767);
        }
        else if (analogRead(iOrientY) <= 512 - deadzone) {
            rotationMsg.pitch = constrain(map(analogRead(iOrientY), 0, 512 - deadzone, -32767, 0), -32767, 0);
        }
        else {
            rotationMsg.pitch = 0;
        }
        if (analogRead(iOrientZ) >= 512 + deadzone) {
            rotationMsg.roll = constrain(map(analogRead(iOrientZ), 512 + deadzone, 1023, 0, 32767), 0, 32767);
        }
        else if (analogRead(iOrientZ) <= 512 - deadzone) {
            rotationMsg.roll = constrain(map(analogRead(iOrientZ), 0, 512 - deadzone, -32767, 0), -32767, 0);
        }
        else {
            rotationMsg.roll = 0;
        }
    
        if (analogRead(iTranslateX) >= 512 + deadzone) {
            translationMsg.X = constrain(map(analogRead(iTranslateX), 1023, 512 + deadzone, -32767, 0), -32767, 0);
        }
        else if (analogRead(iTranslateX) <= 512 - deadzone) {
            translationMsg.X = constrain(map(analogRead(iTranslateX), 512 - deadzone, 0, 0, 32767), 0, 32767);
        }
        else {
            translationMsg.X = 0;
        }
        if (analogRead(iTranslateY) >= 512 + deadzone) {
            translationMsg.Y = constrain(map(analogRead(iTranslateY), 1023, 512 + deadzone, -32767, 0), -32767, 0);
        }
        else if (analogRead(iTranslateY) <= 512 - deadzone) {
            translationMsg.Y = constrain(map(analogRead(iTranslateY), 512 - deadzone, 0, 0, 32767), 0, 32767);
        }
        else {
            translationMsg.Y = 0;
        }
        if (analogRead(iTranslateZ) >= 512 + deadzone) {
            translationMsg.Z = constrain(map(analogRead(iTranslateZ), 1023, 512 + deadzone, -32767, 0), -32767, 0);
        }
        else if (analogRead(iTranslateZ) <= 512 - deadzone) {
            translationMsg.Z = constrain(map(analogRead(iTranslateZ), 512 - deadzone, 0, 0, 32767), 0, 32767);
        }
        else {
            translationMsg.Z = 0;
        }
    
        break;
    case 1:
        mappedThrottleValue = constrain(map(analogRead(iThrottleValue), 1023 - deadzonethrottle, 0 + deadzonethrottle, 0, 32767), 0, 32767);
        wheelMsg.throttle = constrain(map(analogRead(iThrottleValue), 1023 - deadzonethrottle, 0 + deadzonethrottle, 0, 32767), 0, 32767);
    
        if (analogRead(iOrientX) >= 512 + deadzone) {
            rotationMsg.roll = constrain(map(analogRead(iOrientX), 512 + deadzone, 1023, 0, 32767), 0, 32767);
        }
        else if (analogRead(iOrientX) <= 512 - deadzone) {
            rotationMsg.roll = constrain(map(analogRead(iOrientX), 0, 512 - deadzone, -32767, 0), -32767, 0);
        }
        else {
            rotationMsg.roll = 0;
        }
        if (analogRead(iOrientY) >= 512 + deadzone) {
            rotationMsg.pitch = constrain(map(analogRead(iOrientY), 512 + deadzone, 1023, 0, 32767), 0, 32767);
        }
        else if (analogRead(iOrientY) <= 512 - deadzone) {
            rotationMsg.pitch = constrain(map(analogRead(iOrientY), 0, 512 - deadzone, -32767, 0), -32767, 0);
        }
        else {
            rotationMsg.pitch = 0;
        }
        if (analogRead(iOrientZ) >= 512 + deadzone) {
            rotationMsg.yaw = constrain(map(analogRead(iOrientZ), 512 + deadzone, 1023, 0, 32767), 0, 32767);
            wheelMsg.steer = constrain(map(analogRead(iOrientZ), 1023, 512 + deadzone, -32767, 0), -32767, 0);
        }
        else if (analogRead(iOrientZ) <= 512 - deadzone) {
            rotationMsg.yaw = constrain(map(analogRead(iOrientZ), 0, 512 - deadzone, -32767, 0), -32767, 0);
            wheelMsg.steer = constrain(map(analogRead(iOrientZ), 512 - deadzone, 0, 0, 32767), 0, 32767);
        }
        else {
            rotationMsg.yaw = 0;
            wheelMsg.steer = 0;
        }
    
        if (analogRead(iTranslateX) >= 512 + deadzone) {
            translationMsg.X = constrain(map(analogRead(iTranslateX), 1023, 512 + deadzone, -32767, 0), -32767, 0);
        }
        else if (analogRead(iTranslateX) <= 512 - deadzone) {
            translationMsg.X = constrain(map(analogRead(iTranslateX), 512 - deadzone, 0, 0, 32767), 0, 32767);
        }
        else {
            translationMsg.X = 0;
        }
        if (analogRead(iTranslateY) >= 512 + deadzone) {
            translationMsg.Y = constrain(map(analogRead(iTranslateY), 1023, 512 + deadzone, -32767, 0), -32767, 0);
        }
        else if (analogRead(iTranslateY) <= 512 - deadzone) {
            translationMsg.Y = constrain(map(analogRead(iTranslateY), 512 - deadzone, 0, 0, 32767), 0, 32767);
        }
        else {
            translationMsg.Y = 0;
        }
        if (analogRead(iTranslateZ) >= 512 + deadzone) {
            translationMsg.Z = constrain(map(analogRead(iTranslateZ), 1023, 512 + deadzone, -32767, 0), -32767, 0);
        }
        else if (analogRead(iTranslateZ) <= 512 - deadzone) {
            translationMsg.Z = constrain(map(analogRead(iTranslateZ), 512 - deadzone, 0, 0, 32767), 0, 32767);
        }
        else {
            translationMsg.Z = 0;
        }
    
        break;
    case 2:
        mappedThrottleValue = constrain(map(analogRead(iThrottleValue), 1023 - deadzonethrottle, 0 + deadzonethrottle, 0, 32767), 0, 32767);
        wheelMsg.throttle = constrain(map(analogRead(iThrottleValue), 1023 - deadzonethrottle, 0 + deadzonethrottle, 0, 32767), 0, 32767);
    
        if (analogRead(iOrientX) >= 512 + deadzone) {
            rotationMsg.yaw = constrain(map(analogRead(iOrientX), 512 + deadzone, 1023, 0, 8192), 0, 8192);
            wheelMsg.steer = constrain(map(analogRead(iOrientX), 1023, 512 + deadzone, -8192, 0), -8192, 0);
        }
        else if (analogRead(iOrientX) <= 512 - deadzone) {
            rotationMsg.yaw = constrain(map(analogRead(iOrientX), 0, 512 - deadzone, -8192, 0), -8192, 0);
            wheelMsg.steer = constrain(map(analogRead(iOrientX), 512 - deadzone, 0, 0, 8192), 0, 8192);
        }
        else {
            rotationMsg.yaw = 0;
            wheelMsg.steer = 0;
        }
        if (analogRead(iOrientY) >= 512 + deadzone) {
            rotationMsg.pitch = constrain(map(analogRead(iOrientY), 512 + deadzone, 1023, 0, 8192), 0, 8192);
        }
        else if (analogRead(iOrientY) <= 512 - deadzone) {
            rotationMsg.pitch = constrain(map(analogRead(iOrientY), 0, 512 - deadzone, -8192, 0), -8192, 0);
        }
        else {
            rotationMsg.pitch = 0;
        }
        if (analogRead(iOrientZ) >= 512 + deadzone) {
            rotationMsg.roll = constrain(map(analogRead(iOrientZ), 512 + deadzone, 1023, 0, 8192), 0, 8192);
        }
        else if (analogRead(iOrientZ) <= 512 - deadzone) {
            rotationMsg.roll = constrain(map(analogRead(iOrientZ), 0, 512 - deadzone, -8192, 0), -8192, 0);
        }
        else {
            rotationMsg.roll = 0;
        }
    
        if (analogRead(iTranslateX) >= 512 + deadzone) {
            translationMsg.X = constrain(map(analogRead(iTranslateX), 1023, 512 + deadzone, -8192, 0), -8192, 0);
        }
        else if (analogRead(iTranslateX) <= 512 - deadzone) {
            translationMsg.X = constrain(map(analogRead(iTranslateX), 512 - deadzone, 0, 0, 8192), 0, 8192);
        }
        else {
            translationMsg.X = 0;
        }
        if (analogRead(iTranslateY) >= 512 + deadzone) {
            translationMsg.Y = constrain(map(analogRead(iTranslateY), 1023, 512 + deadzone, -8192, 0), -8192, 0);
        }
        else if (analogRead(iTranslateY) <= 512 - deadzone) {
            translationMsg.Y = constrain(map(analogRead(iTranslateY), 512 - deadzone, 0, 0, 8192), 0, 8192);
        }
        else {
            translationMsg.Y = 0;
        }
        if (analogRead(iTranslateZ) >= 512 + deadzone) {
            translationMsg.Z = constrain(map(analogRead(iTranslateZ), 1023, 512 + deadzone, -8192, 0), -8192, 0);
        }
        else if (analogRead(iTranslateZ) <= 512 - deadzone) {
            translationMsg.Z = constrain(map(analogRead(iTranslateZ), 512 - deadzone, 0, 0, 8192), 0, 8192);
        }
        else {
            translationMsg.Z = 0;
        }
    
        break;
    case 3:
        mappedThrottleValue = constrain(map(analogRead(iThrottleValue), 1023 - deadzonethrottle, 0 + deadzonethrottle, 0, 32767), 0, 32767);
        wheelMsg.throttle = constrain(map(analogRead(iThrottleValue), 1023 - deadzonethrottle, 0 + deadzonethrottle, 0, 32767), 0, 32767);
    
        if (analogRead(iOrientX) >= 512 + deadzone) {
            rotationMsg.roll = constrain(map(analogRead(iOrientX), 512 + deadzone, 1023, 0, 8192), 0, 8192);
        }
        else if (analogRead(iOrientX) <= 512 - deadzone) {
            rotationMsg.roll = constrain(map(analogRead(iOrientX), 0, 512 - deadzone, -8192, 0), -8192, 0);
        }
        else {
            rotationMsg.roll = 0;
        }
        if (analogRead(iOrientY) >= 512 + deadzone) {
            rotationMsg.pitch = constrain(map(analogRead(iOrientY), 512 + deadzone, 1023, 0, 8192), 0, 8192);
        }
        else if (analogRead(iOrientY) <= 512 - deadzone) {
            rotationMsg.pitch = constrain(map(analogRead(iOrientY), 0, 512 - deadzone, -8192, 0), -8192, 0);
        }
        else {
            rotationMsg.pitch = 0;
        }
        if (analogRead(iOrientZ) >= 512 + deadzone) {
            rotationMsg.yaw = constrain(map(analogRead(iOrientZ), 512 + deadzone, 1023, 0, 8192), 0, 8192);
            wheelMsg.steer = constrain(map(analogRead(iOrientZ), 1023, 512 + deadzone, -8192, 0), -8192, 0);
        }
        else if (analogRead(iOrientZ) <= 512 - deadzone) {
            rotationMsg.yaw = constrain(map(analogRead(iOrientZ), 0, 512 - deadzone, -8192, 0), -8192, 0);
            wheelMsg.steer = constrain(map(analogRead(iOrientZ), 512 - deadzone, 0, 0, 8192), 0, 8192);
        }
        else {
            rotationMsg.yaw = 0;
            wheelMsg.steer = 0;
        }
    
        if (analogRead(iTranslateX) >= 512 + deadzone) {
            translationMsg.X = constrain(map(analogRead(iTranslateX), 1023, 512 + deadzone, -8192, 0), -8192, 0);
        }
        else if (analogRead(iTranslateX) <= 512 - deadzone) {
            translationMsg.X = constrain(map(analogRead(iTranslateX), 512 - deadzone, 0, 0, 8192), 0, 8192);
        }
        else {
            translationMsg.X = 0;
        }
        if (analogRead(iTranslateY) >= 512 + deadzone) {
            translationMsg.Y = constrain(map(analogRead(iTranslateY), 1023, 512 + deadzone, -8192, 0), -8192, 0);
        }
        else if (analogRead(iTranslateY) <= 512 - deadzone) {
            translationMsg.Y = constrain(map(analogRead(iTranslateY), 512 - deadzone, 0, 0, 8192), 0, 8192);
        }
        else {
            translationMsg.Y = 0;
        }
        if (analogRead(iTranslateZ) >= 512 + deadzone) {
            translationMsg.Z = constrain(map(analogRead(iTranslateZ), 1023, 512 + deadzone, -8192, 0), -8192, 0);
        }
        else if (analogRead(iTranslateZ) <= 512 - deadzone) {
            translationMsg.Z = constrain(map(analogRead(iTranslateZ), 512 - deadzone, 0, 0, 8192), 0, 8192);
        }
        else {
            translationMsg.Z = 0;
        }
    
        break;
    }
    
    //send the control packet to the Simpit plugin
    mySimpit.send(THROTTLE_MESSAGE, mappedThrottleValue);  // Throttle
    mySimpit.send(WHEEL_MESSAGE, wheelMsg);           // Roll
    mySimpit.send(ROTATION_MESSAGE,rotationMsg);      // Yaw/pitch
    mySimpit.send(TRANSLATION_MESSAGE,translationMsg);

}

void toggleThrottleSensitivity() {
  if(throttleSensitive) {
    throttleSensitive = false;
  } else {
    throttleSensitive = true;
  }
}

void setThrottleSensitive(boolean sensitive) {
  throttleSensitive = sensitive;
}

// Does fine tune need 

// TODO: Finish adding throttle stuff into here. Particularily the read/write parts. Also make sure it's not reversed.
void motorfader() {
  if (buttonPressed(bMaxThrottle)) {
    throttleTarget = 0;
    digitalWrite(motoron, HIGH);
  } else if (buttonPressed(bMinThrottle)) {
    throttleTarget = 1020;
    digitalWrite(motoron, HIGH);
  } else {
    throttleTarget = iThrottleValue;
    digitalWrite(motoron, LOW);
  }

  if (analogRead(iThrottleValue) > (throttleTarget + throttleThreshold)) {
    analogWrite(motordown, 0);
    analogWrite(motorup, 255);
  } else if (analogRead(iThrottleValue) < (throttleTarget - throttleThreshold)) {
    analogWrite(motordown, 255);
    analogWrite(motorup, 0);
  } else {
    analogWrite(motordown, 0);
    analogWrite(motorup, 0);
  }
}
