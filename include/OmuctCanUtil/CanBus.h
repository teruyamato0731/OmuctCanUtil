#ifndef OCU_CAN_BUS_H_
#define OCU_CAN_BUS_H_

namespace omuct_can_util {

#ifdef __MBED__

using CanBus = mbed::CAN;

#elif defined(ARDUINO)  // __MBED__

#include "ArduinoCanAdaptor.h"
using CanBus = ArduinoCanAdaptor;

#endif

}

#endif  // OCU_CAN_BUS_H_
