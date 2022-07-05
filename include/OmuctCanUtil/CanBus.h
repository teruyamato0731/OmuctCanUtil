#ifndef OCU_CAN_BUS_H_
#define OCU_CAN_BUS_H_

namespace omuct_can_util {

#ifdef __MBED__

using CanBus = mbed::CAN;

#elif defined(ARDUINO)  // __MBED__

// TODO
#include <Arduino.h>
struct CanBus {
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
#else
#error unsupported framework
#endif

}

#endif  // OCU_CAN_BUS_H_
