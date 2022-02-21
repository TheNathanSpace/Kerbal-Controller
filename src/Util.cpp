#include "Button.h"

/*
 *   CHECK INPUTS
 */
boolean buttonPressed(Button inputButton)
{
    return inputButton.pressed();
}

boolean buttonChanged(Button inputButton)
{
    return inputButton.has_changed();
}