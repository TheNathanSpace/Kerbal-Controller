#include <Arduino.h>

registerChannels() {
  mySimpit.registerChannel(CAGTOGGLE_MESSAGE);
  mySimpit.registerChannel(AGACTIVATE_MESSAGE);
  mySimpit.registerChannel(AGTOGGLE_MESSAGE);
  mySimpit.registerChannel(SAS_MODE_MESSAGE);

  mySimpit.registerChannel(THROTTLE_MESSAGE);
  mySimpit.registerChannel(WHEEL_MESSAGE);
  mySimpit.registerChannel(ROTATION_MESSAGE);
  mySimpit.registerChannel(TRANSLATION_MESSAGE);
}
