#include <Arduino.h>

boolean checkButton(Button inputButton) {
  return inputButton.read() == Button:PRESSED;
}

boolean buttonChanged(Button inputButton) {
  return inputButton.has_changed();
}
