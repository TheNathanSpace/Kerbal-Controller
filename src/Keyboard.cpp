#include "Keyboard.h"
#include "Arduino.h"

Keyboard::Keyboard()
{
}

void Keyboard::sendKey(char key)
{
    Serial.print(key);
}