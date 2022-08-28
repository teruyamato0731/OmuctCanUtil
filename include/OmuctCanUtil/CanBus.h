/// Copyright (c) 2022 Yoshikawa Teru
/// This software is released under the MIT License, see LICENSE.
#ifndef OCU_CAN_BUS_H_
#define OCU_CAN_BUS_H_

#include "CanUtil.h"

#ifdef __MBED__

#include <mbed.h>
namespace omuct_can_util {
OCU_BEGIN_NAMESPACE_VERSION
using CanBus = mbed::CAN;
OCU_END_NAMESPACE_VERSION
}  // namespace omuct_can_util
#elif defined(ARDUINO)  // __MBED__

#include <Arduino.h>
#include <CAN.h>

#include "CanMessage.h"

namespace omuct_can_util {
OCU_BEGIN_NAMESPACE_VERSION
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
  int write(const CanMessage& msg) {
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
OCU_END_NAMESPACE_VERSION
}  // namespace omuct_can_util
#else
#error unsupported framework
#endif

#endif  // OCU_CAN_BUS_H_
