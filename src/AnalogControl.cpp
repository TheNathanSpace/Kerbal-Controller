#include "KerbalSimpit.h"
#include "Util.cpp"
#include <Arduino.h>


const byte iRocketMode = ;
const byte iFlyPrecision = ;
boolean throttleSensitive = false;
int throttleTarget;
int throttleThreshold = 30;

Button tsRocketMode(iRocketMode);
Button tsFlyPrecision(iFlyPrecision);

int flyMode = 0;
int mappedThrottleValue;

const byte iTranslateX = ;
const byte iTranslateY = ;
const byte iTranslateZ = ;
const byte iTranslateButton = ;

const byte iOrientX = ;
const byte iOrientY = ;
const byte iOrientZ = ;
const byte iOrientButton = ;

const byte iThrottleValue = ;
const byte oMotorOn = ;
const byte oMotorUp = ;
const byte oMotorDown = ;
const byte iThrottleSensitivity = ;
const byte iMinThrottle = ;
const byte iMaxThrottle = ;

// The following two buttons are currently unused. Maybe they can be hooked up to weapons or something. I don't know.
Button bTranslateButton(iTranslateButton);
Button bOrientButton(iOrientButton);

Button tsThrottleSensitivity(iThrottleSensitivity);
Button bMinThrottle(iMinThrottle);
Button bMaxThrottle(iMaxThrottle);

// SOURCE: https://github.com/Richi0D/KerbalController-Simpit/blob/master/Output.ino

void updateJoysticks(KerbalSimpit &mySimpit)
{
    // create structs and masks
    rotationMessage rotationMsg;
    rotationMsg.mask = 1 | 2 | 4;
    translationMessage translationMsg;
    translationMsg.mask = 1 | 2 | 4;
    wheelMessage wheelMsg;
    wheelMsg.mask = 1 | 2;

    // MAKE SURE THE BOOLEAN IS SET UP CORRECTLY, ESPECIALLY WITH THE PULLUP
    // Precision on = precision mode. Rocket on = rocket mode.
    if ((!buttonPressed(tsFlyPrecision)) and (buttonPressed(tsRocketMode)))
    {
        flyMode = 0;
    }// rocket mode
    else if ((!buttonPressed(tsFlyPrecision)) and (!buttonPressed(tsRocketMode)))
    {
        flyMode = 1;
    }// plane mode
    else if ((buttonPressed(tsFlyPrecision)) and (buttonPressed(tsRocketMode)))
    {
        flyMode = 2;
    }// rocket mode + precision
    else if ((buttonPressed(tsFlyPrecision)) and (!buttonPressed(tsRocketMode)))
    {
        flyMode = 3;
    }// plane mode + precision
    else
    {
        flyMode = 0;
    }

    int deadzone = 50;
    int deadzonethrottle = 25;

    switch (flyMode)
    {
        case 0:                                                                                                                                 // Rocket mode
            mappedThrottleValue = constrain(map(analogRead(iThrottleValue), 1023 - deadzonethrottle, 0 + deadzonethrottle, 0, 32767), 0, 32767);// Maps 0-1028 throttle values to  0-32767 values. Deletes everything outside of those bounds (because they'd be erroneous).
            wheelMsg.throttle = constrain(map(analogRead(iThrottleValue), 1023 - deadzonethrottle, 0 + deadzonethrottle, 0, 32767), 0, 32767);

            if (analogRead(iOrientX) >= 512 + deadzone)
            {
                rotationMsg.yaw = constrain(map(analogRead(iOrientX), 512 + deadzone, 1023, 0, 32767), 0, 32767);
                wheelMsg.steer = constrain(map(analogRead(iOrientX), 1023, 512 + deadzone, -32767, 0), -32767, 0);
            }
            else if (analogRead(iOrientX) <= 512 - deadzone)
            {
                rotationMsg.yaw = constrain(map(analogRead(iOrientX), 0, 512 - deadzone, -32767, 0), -32767, 0);
                wheelMsg.steer = constrain(map(analogRead(iOrientX), 512 - deadzone, 0, 0, 32767), 0, 32767);
            }
            else
            {
                rotationMsg.yaw = 0;
                wheelMsg.steer = 0;
            }

            if (analogRead(iOrientY) >= 512 + deadzone)
            {
                rotationMsg.pitch = constrain(map(analogRead(iOrientY), 512 + deadzone, 1023, 0, 32767), 0, 32767);
            }
            else if (analogRead(iOrientY) <= 512 - deadzone)
            {
                rotationMsg.pitch = constrain(map(analogRead(iOrientY), 0, 512 - deadzone, -32767, 0), -32767, 0);
            }
            else
            {
                rotationMsg.pitch = 0;
            }

            if (analogRead(iOrientZ) >= 512 + deadzone)
            {
                rotationMsg.roll = constrain(map(analogRead(iOrientZ), 512 + deadzone, 1023, 0, 32767), 0, 32767);
            }
            else if (analogRead(iOrientZ) <= 512 - deadzone)
            {
                rotationMsg.roll = constrain(map(analogRead(iOrientZ), 0, 512 - deadzone, -32767, 0), -32767, 0);
            }
            else
            {
                rotationMsg.roll = 0;
            }

            if (analogRead(iTranslateX) >= 512 + deadzone)
            {
                translationMsg.X = constrain(map(analogRead(iTranslateX), 1023, 512 + deadzone, -32767, 0), -32767, 0);
            }
            else if (analogRead(iTranslateX) <= 512 - deadzone)
            {
                translationMsg.X = constrain(map(analogRead(iTranslateX), 512 - deadzone, 0, 0, 32767), 0, 32767);
            }
            else
            {
                translationMsg.X = 0;
            }

            if (analogRead(iTranslateY) >= 512 + deadzone)
            {
                translationMsg.Y = constrain(map(analogRead(iTranslateY), 1023, 512 + deadzone, -32767, 0), -32767, 0);
            }
            else if (analogRead(iTranslateY) <= 512 - deadzone)
            {
                translationMsg.Y = constrain(map(analogRead(iTranslateY), 512 - deadzone, 0, 0, 32767), 0, 32767);
            }
            else
            {
                translationMsg.Y = 0;
            }

            if (analogRead(iTranslateZ) >= 512 + deadzone)
            {
                translationMsg.Z = constrain(map(analogRead(iTranslateZ), 1023, 512 + deadzone, -32767, 0), -32767, 0);
            }
            else if (analogRead(iTranslateZ) <= 512 - deadzone)
            {
                translationMsg.Z = constrain(map(analogRead(iTranslateZ), 512 - deadzone, 0, 0, 32767), 0, 32767);
            }
            else
            {
                translationMsg.Z = 0;
            }

            break;

        case 1:
            mappedThrottleValue = constrain(map(analogRead(iThrottleValue), 1023 - deadzonethrottle, 0 + deadzonethrottle, 0, 32767), 0, 32767);
            wheelMsg.throttle = constrain(map(analogRead(iThrottleValue), 1023 - deadzonethrottle, 0 + deadzonethrottle, 0, 32767), 0, 32767);

            if (analogRead(iOrientX) >= 512 + deadzone)
            {
                rotationMsg.roll = constrain(map(analogRead(iOrientX), 512 + deadzone, 1023, 0, 32767), 0, 32767);
            }
            else if (analogRead(iOrientX) <= 512 - deadzone)
            {
                rotationMsg.roll = constrain(map(analogRead(iOrientX), 0, 512 - deadzone, -32767, 0), -32767, 0);
            }
            else
            {
                rotationMsg.roll = 0;
            }

            if (analogRead(iOrientY) >= 512 + deadzone)
            {
                rotationMsg.pitch = constrain(map(analogRead(iOrientY), 512 + deadzone, 1023, 0, 32767), 0, 32767);
            }
            else if (analogRead(iOrientY) <= 512 - deadzone)
            {
                rotationMsg.pitch = constrain(map(analogRead(iOrientY), 0, 512 - deadzone, -32767, 0), -32767, 0);
            }
            else
            {
                rotationMsg.pitch = 0;
            }

            if (analogRead(iOrientZ) >= 512 + deadzone)
            {
                rotationMsg.yaw = constrain(map(analogRead(iOrientZ), 512 + deadzone, 1023, 0, 32767), 0, 32767);
                wheelMsg.steer = constrain(map(analogRead(iOrientZ), 1023, 512 + deadzone, -32767, 0), -32767, 0);
            }
            else if (analogRead(iOrientZ) <= 512 - deadzone)
            {
                rotationMsg.yaw = constrain(map(analogRead(iOrientZ), 0, 512 - deadzone, -32767, 0), -32767, 0);
                wheelMsg.steer = constrain(map(analogRead(iOrientZ), 512 - deadzone, 0, 0, 32767), 0, 32767);
            }
            else
            {
                rotationMsg.yaw = 0;
                wheelMsg.steer = 0;
            }

            if (analogRead(iTranslateX) >= 512 + deadzone)
            {
                translationMsg.X = constrain(map(analogRead(iTranslateX), 1023, 512 + deadzone, -32767, 0), -32767, 0);
            }
            else if (analogRead(iTranslateX) <= 512 - deadzone)
            {
                translationMsg.X = constrain(map(analogRead(iTranslateX), 512 - deadzone, 0, 0, 32767), 0, 32767);
            }
            else
            {
                translationMsg.X = 0;
            }

            if (analogRead(iTranslateY) >= 512 + deadzone)
            {
                translationMsg.Y = constrain(map(analogRead(iTranslateY), 1023, 512 + deadzone, -32767, 0), -32767, 0);
            }
            else if (analogRead(iTranslateY) <= 512 - deadzone)
            {
                translationMsg.Y = constrain(map(analogRead(iTranslateY), 512 - deadzone, 0, 0, 32767), 0, 32767);
            }
            else
            {
                translationMsg.Y = 0;
            }

            if (analogRead(iTranslateZ) >= 512 + deadzone)
            {
                translationMsg.Z = constrain(map(analogRead(iTranslateZ), 1023, 512 + deadzone, -32767, 0), -32767, 0);
            }
            else if (analogRead(iTranslateZ) <= 512 - deadzone)
            {
                translationMsg.Z = constrain(map(analogRead(iTranslateZ), 512 - deadzone, 0, 0, 32767), 0, 32767);
            }
            else
            {
                translationMsg.Z = 0;
            }

            break;

        case 2:
            mappedThrottleValue = constrain(map(analogRead(iThrottleValue), 1023 - deadzonethrottle, 0 + deadzonethrottle, 0, 32767), 0, 32767);
            wheelMsg.throttle = constrain(map(analogRead(iThrottleValue), 1023 - deadzonethrottle, 0 + deadzonethrottle, 0, 32767), 0, 32767);

            if (analogRead(iOrientX) >= 512 + deadzone)
            {
                rotationMsg.yaw = constrain(map(analogRead(iOrientX), 512 + deadzone, 1023, 0, 8192), 0, 8192);
                wheelMsg.steer = constrain(map(analogRead(iOrientX), 1023, 512 + deadzone, -8192, 0), -8192, 0);
            }
            else if (analogRead(iOrientX) <= 512 - deadzone)
            {
                rotationMsg.yaw = constrain(map(analogRead(iOrientX), 0, 512 - deadzone, -8192, 0), -8192, 0);
                wheelMsg.steer = constrain(map(analogRead(iOrientX), 512 - deadzone, 0, 0, 8192), 0, 8192);
            }
            else
            {
                rotationMsg.yaw = 0;
                wheelMsg.steer = 0;
            }

            if (analogRead(iOrientY) >= 512 + deadzone)
            {
                rotationMsg.pitch = constrain(map(analogRead(iOrientY), 512 + deadzone, 1023, 0, 8192), 0, 8192);
            }
            else if (analogRead(iOrientY) <= 512 - deadzone)
            {
                rotationMsg.pitch = constrain(map(analogRead(iOrientY), 0, 512 - deadzone, -8192, 0), -8192, 0);
            }
            else
            {
                rotationMsg.pitch = 0;
            }

            if (analogRead(iOrientZ) >= 512 + deadzone)
            {
                rotationMsg.roll = constrain(map(analogRead(iOrientZ), 512 + deadzone, 1023, 0, 8192), 0, 8192);
            }
            else if (analogRead(iOrientZ) <= 512 - deadzone)
            {
                rotationMsg.roll = constrain(map(analogRead(iOrientZ), 0, 512 - deadzone, -8192, 0), -8192, 0);
            }
            else
            {
                rotationMsg.roll = 0;
            }

            if (analogRead(iTranslateX) >= 512 + deadzone)
            {
                translationMsg.X = constrain(map(analogRead(iTranslateX), 1023, 512 + deadzone, -8192, 0), -8192, 0);
            }
            else if (analogRead(iTranslateX) <= 512 - deadzone)
            {
                translationMsg.X = constrain(map(analogRead(iTranslateX), 512 - deadzone, 0, 0, 8192), 0, 8192);
            }
            else
            {
                translationMsg.X = 0;
            }

            if (analogRead(iTranslateY) >= 512 + deadzone)
            {
                translationMsg.Y = constrain(map(analogRead(iTranslateY), 1023, 512 + deadzone, -8192, 0), -8192, 0);
            }
            else if (analogRead(iTranslateY) <= 512 - deadzone)
            {
                translationMsg.Y = constrain(map(analogRead(iTranslateY), 512 - deadzone, 0, 0, 8192), 0, 8192);
            }
            else
            {
                translationMsg.Y = 0;
            }

            if (analogRead(iTranslateZ) >= 512 + deadzone)
            {
                translationMsg.Z = constrain(map(analogRead(iTranslateZ), 1023, 512 + deadzone, -8192, 0), -8192, 0);
            }
            else if (analogRead(iTranslateZ) <= 512 - deadzone)
            {
                translationMsg.Z = constrain(map(analogRead(iTranslateZ), 512 - deadzone, 0, 0, 8192), 0, 8192);
            }
            else
            {
                translationMsg.Z = 0;
            }

            break;

        case 3:
            mappedThrottleValue = constrain(map(analogRead(iThrottleValue), 1023 - deadzonethrottle, 0 + deadzonethrottle, 0, 32767), 0, 32767);
            wheelMsg.throttle = constrain(map(analogRead(iThrottleValue), 1023 - deadzonethrottle, 0 + deadzonethrottle, 0, 32767), 0, 32767);

            if (analogRead(iOrientX) >= 512 + deadzone)
            {
                rotationMsg.roll = constrain(map(analogRead(iOrientX), 512 + deadzone, 1023, 0, 8192), 0, 8192);
            }
            else if (analogRead(iOrientX) <= 512 - deadzone)
            {
                rotationMsg.roll = constrain(map(analogRead(iOrientX), 0, 512 - deadzone, -8192, 0), -8192, 0);
            }
            else
            {
                rotationMsg.roll = 0;
            }

            if (analogRead(iOrientY) >= 512 + deadzone)
            {
                rotationMsg.pitch = constrain(map(analogRead(iOrientY), 512 + deadzone, 1023, 0, 8192), 0, 8192);
            }
            else if (analogRead(iOrientY) <= 512 - deadzone)
            {
                rotationMsg.pitch = constrain(map(analogRead(iOrientY), 0, 512 - deadzone, -8192, 0), -8192, 0);
            }
            else
            {
                rotationMsg.pitch = 0;
            }

            if (analogRead(iOrientZ) >= 512 + deadzone)
            {
                rotationMsg.yaw = constrain(map(analogRead(iOrientZ), 512 + deadzone, 1023, 0, 8192), 0, 8192);
                wheelMsg.steer = constrain(map(analogRead(iOrientZ), 1023, 512 + deadzone, -8192, 0), -8192, 0);
            }
            else if (analogRead(iOrientZ) <= 512 - deadzone)
            {
                rotationMsg.yaw = constrain(map(analogRead(iOrientZ), 0, 512 - deadzone, -8192, 0), -8192, 0);
                wheelMsg.steer = constrain(map(analogRead(iOrientZ), 512 - deadzone, 0, 0, 8192), 0, 8192);
            }
            else
            {
                rotationMsg.yaw = 0;
                wheelMsg.steer = 0;
            }

            if (analogRead(iTranslateX) >= 512 + deadzone)
            {
                translationMsg.X = constrain(map(analogRead(iTranslateX), 1023, 512 + deadzone, -8192, 0), -8192, 0);
            }
            else if (analogRead(iTranslateX) <= 512 - deadzone)
            {
                translationMsg.X = constrain(map(analogRead(iTranslateX), 512 - deadzone, 0, 0, 8192), 0, 8192);
            }
            else
            {
                translationMsg.X = 0;
            }

            if (analogRead(iTranslateY) >= 512 + deadzone)
            {
                translationMsg.Y = constrain(map(analogRead(iTranslateY), 1023, 512 + deadzone, -8192, 0), -8192, 0);
            }
            else if (analogRead(iTranslateY) <= 512 - deadzone)
            {
                translationMsg.Y = constrain(map(analogRead(iTranslateY), 512 - deadzone, 0, 0, 8192), 0, 8192);
            }
            else
            {
                translationMsg.Y = 0;
            }

            if (analogRead(iTranslateZ) >= 512 + deadzone)
            {
                translationMsg.Z = constrain(map(analogRead(iTranslateZ), 1023, 512 + deadzone, -8192, 0), -8192, 0);
            }
            else if (analogRead(iTranslateZ) <= 512 - deadzone)
            {
                translationMsg.Z = constrain(map(analogRead(iTranslateZ), 512 - deadzone, 0, 0, 8192), 0, 8192);
            }
            else
            {
                translationMsg.Z = 0;
            }

            break;
    }

    // send the control packet to the Simpit plugin
    mySimpit.send(THROTTLE_MESSAGE, mappedThrottleValue);// Throttle
    mySimpit.send(WHEEL_MESSAGE, wheelMsg);              // Roll
    mySimpit.send(ROTATION_MESSAGE, rotationMsg);        // Yaw/pitch
    mySimpit.send(TRANSLATION_MESSAGE, translationMsg);
}

void toggleThrottleSensitivity()
{
    if (throttleSensitive)
    {
        throttleSensitive = false;
    }
    else
    {
        throttleSensitive = true;
    }
}

void setThrottleSensitive(boolean sensitive)
{
    throttleSensitive = sensitive;
}

// Does fine tune need

// TODO: Finish adding throttle stuff into here. Particularily the read/write parts. Also make sure it's not reversed.
void motorFader()
{
    if (buttonPressed(bMaxThrottle))
    {
        throttleTarget = 0;
        digitalWrite(oMotorOn, HIGH);
    }
    else if (buttonPressed(bMinThrottle))
    {
        throttleTarget = 1020;
        digitalWrite(oMotorOn, HIGH);
    }
    else
    {
        throttleTarget = iThrottleValue;
        digitalWrite(oMotorOn, LOW);
    }

    if (analogRead(iThrottleValue) > (throttleTarget + throttleThreshold))
    {
        analogWrite(oMotorDown, 0);
        analogWrite(oMotorUp, 255);
    }
    else if (analogRead(iThrottleValue) < (throttleTarget - throttleThreshold))
    {
        analogWrite(oMotorDown, 255);
        analogWrite(oMotorUp, 0);
    }
    else
    {
        analogWrite(oMotorDown, 0);
        analogWrite(oMotorUp, 0);
    }
}
