#ifndef ARDUINO_CAN_ADAPTOR_H
#define ARDUINO_CAN_ADAPTOR_H

#ifdef ARDUINO
#include <Arduino.h>

struct ArduinoCanAdaptor {
  int read() {
    return 0;
  }
  int write() {
    return 0;
  }
  int frequency() {
    return 0;
  }
};

#endif  // ARDUINO
#endif  // ARDUINO_CAN_ADAPTOR_H
