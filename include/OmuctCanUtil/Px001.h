#ifndef OCU_PX001_H_
#define OCU_PX001_H_

#include "CanId.h"
#include "CanMessage.h"
#include "CanMessage.h"
#include "PlugBase.h"

namespace omuct_can_util {

struct Px001 : PlugBase {
  void task(CanBus& can, const CanMessage& msg) override {
    if() {
      can.write(msg);
    }
  }
};

}  // namespace omuct_can_util

#endif  // OCU_P001_H_
