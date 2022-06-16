#ifndef OCU_CAN_BUS_H_
#define OCU_CAN_BUS_H_

namespace omuct_can_util {

#ifdef __MBED__
using CanBus = mbed::CAN;
#else  // __MBED__
struct CanBus {
  // TODO Arduino用
  // read write
};

// or Arduino Can Adaptor
#endif

}

#endif  // OCU_CAN_BUS_H_
