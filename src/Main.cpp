#include <Arduino.h>
#include <Button.h>
#include <KerbalSimpit.h>
#include <Keyboard.h>

#include "AnalogControl.cpp"

KerbalSimpit mySimpit(Serial);
Keyboard keyboard;

// INPUTS
// Prefix "i" refers to input pin. Prefix "b" refers to debounced button
// object. Prefix "ts" refers to toggle switch debounced button object.

// Misc.
const byte iIVA = ;        // Keyboard shortcut
const byte iMapView = ;    // Keyboard shortcut
const byte iDockingMode = ;// Keyboard shortcut

// Stage/Abort
const byte iArmStage = ;
const byte iTriggerStage = ;
const byte iArmAbort = ;
const byte iTriggerAbort = ;

// Custom Action Groups
const byte iAG1 = ;
const byte iAG2 = ;
const byte iAG3 = ;
const byte iAG4 = ;
const byte iAG5 = ;
const byte iAG6 = ;
const byte iAG7 = ;
const byte iAGChutes = ;
const byte iAGSolar = ;
const byte iAGLadders = ;

// Game Action Groups
const byte iBrakes = ;
const byte iGear = ;
const byte iLights = ;
const byte iRCS = ;

// Do these need pullup resistors?
const byte iSAS = ;
const byte iSASMode1 = ;
const byte iSASMode2 = ;
const byte iSASMode3 = ;
const byte iSASMode4 = ;
const byte iSASMode5 = ;
const byte iSASMode6 = ;
const byte iSASMode7 = ;
const byte iSASMode8 = ;
const byte iSASMode9 = ;
const byte iSASMode10 = ;
// byte SASArray[] = {iSASMode1, iSASMode2, iSASMode3, iSASMode4, iSASMode5,
// iSASMode6, iSASMode7, iSASMode8, iSASMode9, iSASMode10};

// LED Bar Graphs

// Initiate Debounced Button Objects
Button bIVA(iIVA);
Button bMapView(iMapView);
Button bDockingMode(iDockingMode);

Button tsArmStage(iArmStage);
Button tsArmAbort(iArmAbort);
Button bTriggerStage(iTriggerStage);
Button bTriggerAbort(iTriggerAbort);

Button bAG1(iAG1);
Button bAG2(iAG2);
Button bAG3(iAG3);
Button bAG4(iAG4);
Button bAG5(iAG5);
Button bAG6(iAG6);
Button bAG7(iAG7);
Button bAG8(iAG8);
Button tsAGChutes(iAGChutes);
Button tsAGSolar(iAGSolar);
Button tsAGLadders(iAGLadders);
Button CAGArray[] = {bAG1, bAG2, bAG3, bAG4, bAG5,
                     bAG6, bAG7, tsAGChutes, tsAGSolar, tsAGLadders};

Button tsBrakes(iBrakes);
Button tsGear(iGear);
Button tsLights(iLights);
Button tsRCS(iRCS);

// NOTE ON SAS: AutopilotMode::AP_STABILITYASSIST
// https://kerbalsimpit-arduino.readthedocs.io/en/stable/messagetypes.html?highlight=autopilotmode#_CPPv313AutopilotMode
Button tsSAS(iSAS);
Button bSASMode1(iSASMode1);
Button bSASMode2(iSASMode2);
Button bSASMode3(iSASMode3);
Button bSASMode4(iSASMode4);
Button bSASMode5(iSASMode5);
Button bSASMode6(iSASMode6);
Button bSASMode7(iSASMode7);
Button bSASMode8(iSASMode8);
Button bSASMode9(iSASMode9);
Button bSASMode10(iSASMode10);
Button SASArray[] = {bSASMode1, bSASMode2, bSASMode3, bSASMode4, bSASMode5,
                     bSASMode6, bSASMode7, bSASMode8, bSASMode9, bSASMode10};
int currentSAS = 0;

byte STATUS_SAS_TOGGLE = LOW;// Stores whether or not SAS is enabled
byte OUTPUT_SAS_TOGGLE = ;   // LED displays whether or not SAS is enabled

void setup()
{
    Serial.begin(115200);

    initPins();

    while (!mySimpit.init())
        ;

    // mySimpit.registerChannel(ACTIONSTATUS_MESSAGE);
    registerChannels();

    mySimpit.inboundHandler(callbackHandler);
}

void loop()
{
    mySimpit.update();
    checkInputs();
    setOutputs();
}

void callbackHandler(byte messageType, byte message[], byte messageSize)
{
    switch (messageType)
    {
        case ACTIONSTATUS_MESSAGE:
            byte actions = message[0];

            // SAS_ACTION tells whether or not it's enabled
            // https://kerbalsimpitrevamped-arduino.readthedocs.io/en/latest/messagetypes.html#_CPPv4N15OutboundPackets20ACTIONSTATUS_MESSAGEE
            if (actions & SAS_ACTION)
            {
                if (!STATUS_SAS_TOGGLE)
                {
                    STATUS_SAS_TOGGLE = HIGH;
                    digitalWrite(OUTPUT_SAS_TOGGLE, HIGH);
                }
            }
            else
            {
                STATUS_SAS_TOGGLE = LOW;
                digitalWrite(OUTPUT_SAS_TOGGLE, LOW);
            }

            break;
    }
}

void setOutputs()
{
    motorFader();
}

void checkInputs()
{
    if (buttonPressed(bIVA))
    {
        keyboard.sendKey('C');
    }

    if (buttonPressed(bMapView))
    {
        keyboard.sendKey('M');
    }

    if (buttonPressed(bDockingMode))
    {
        keyboard.sendKey('D');// todo: replace with delete key
    }

    if (buttonPressed(tsArmStage))
    {
        // activate light, or else wire light directly to arming switch

        if (buttonPressed(bTriggerStage))
        {
            mySimpit.activateAction(STAGE_ACTION);
        }
    }

    if (buttonPressed(tsArmAbort))
    {
        // activate light, or else wire light directly to arming switch

        if (buttonPressed(bTriggerAbort))
        {
            mySimpit.activateAction(ABORT_ACTION);
        }
    }

    // todo: audit this
    for (int CAG = 1; CAG < 10; CAG++)
    {
        if (CAG <= 7 && buttonPressed(CAGArray[CAG]))
        {
            mySimpit.toggleCAG(CAG);
        }

        if (CAG > 7 && buttonChanged(CAG))
        {
            mySimpit.toggleCAG(CAG);
        }
    }
    // finish below section
    for (int SAS = 1; SAS < 10; SAS++)
    {
        if (buttonPressed(SASArray[SAS]))
        {
            if (!(currentSAS == SAS))
            {
                currentSAS = SAS;
                mySimpit.setSASMode(SAS);
            }
        }
    }

    if (buttonChanged(tsBrakes))
    {
        mySimpit.toggleAction(BRAKES_ACTION);
    }

    if (buttonChanged(tsGear))
    {
        mySimpit.toggleAction(GEAR_ACTION);
    }

    if (buttonChanged(tsLights))
    {
        mySimpit.toggleAction(LIGHT_ACTION);
    }

    if (buttonChanged(tsRCS))
    {
        mySimpit.toggleAction(RCS_ACTION);
    }

    if (buttonChanged(tsSAS))
    {
        mySimpit.toggleAction(SAS_ACTION);
    }

    if (buttonChanged(tsThrottleSensitivity))
    {
        toggleThrottleSensitivity();
    }

    updateJoysticks(mySimpit);
}

/*
 *   INIT CHANNELS, PINS, BUTTONS, ETC.
 */
void registerChannels()
{
    mySimpit.registerChannel(CAGTOGGLE_MESSAGE);
    mySimpit.registerChannel(AGACTIVATE_MESSAGE);
    mySimpit.registerChannel(AGTOGGLE_MESSAGE);
    mySimpit.registerChannel(SAS_MODE_MESSAGE);

    mySimpit.registerChannel(THROTTLE_MESSAGE);
    mySimpit.registerChannel(WHEEL_MESSAGE);
    mySimpit.registerChannel(ROTATION_MESSAGE);
    mySimpit.registerChannel(TRANSLATION_MESSAGE);
}

void initPins()
{
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
    bIVA.begin();
    bMapView.begin();
    bDockingMode.begin();

    tsArmStage.begin();
    tsArmAbort.begin();
    bTriggerStage.begin();
    bTriggerAbort.begin();

    for (int CAG = 1; CAG < 10; CAG++)
    {
        CAGArray[CAG].begin();
    }

    tsBrakes.begin();
    tsGear.begin();
    tsLights.begin();
    tsRCS.begin();

    tsSAS.begin();
    for (int SASPin = 1; SASPin < 10; SASPin++)
    {
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