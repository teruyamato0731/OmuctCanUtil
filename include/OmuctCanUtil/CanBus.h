#ifndef OCU_CAN_BUS_H_
#define OCU_CAN_BUS_H_

#ifdef __MBED__

#include <mbed.h>
namespace omuct_can_util {
using CanBus = mbed::CAN;
}  // namespace omuct_can_util
#elif defined(ARDUINO)  // __MBED__

#include <Arduino.h>
#include <CAN.h>

#include "CanMessage.h"

namespace omuct_can_util {
struct CanBus {
  CanBus(const int rx, const int tx, const long hz) {
    CAN.begin(hz);
    CAN.setPins(rx, tx);
  }
  int read(CanMessage& msg) {
    if(CAN.available()) {
      for(int i = 0; i < CAN.packetDlc(); ++i) {
        msg.data[i] = static_cast<uint8_t>(CAN.read());
      }
    }
    return 0;
  }
  int write(CanMessage& msg) {
    if(msg.format == CANStandard) {
      CAN.beginPacket(msg.id, msg.type);
    } else if(msg.format == CANExtended) {
      CAN.beginExtendedPacket(msg.id, msg.type);
    }
    CAN.write(msg.data, msg.len);
    CAN.endPacket();
    return 0;
  }
  // int frequency() {
  //   return 0;
  // }
};
}  // namespace omuct_can_util
#else
#error unsupported framework
#endif

#endif  // OCU_CAN_BUS_H_
