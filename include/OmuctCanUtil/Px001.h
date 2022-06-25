#ifndef OCU_PX001_H_
#define OCU_PX001_H_

#include "CanId.h"
#include "CanMessage.h"
#include "PlugBase.h"

namespace omuct_can_util {

struct Px001 : PlugBase {
  // TODO
  constexpr Px001(CanManager) noexcept {}

  void task(CanBus& can, const CanMessage& msg) override {
    if(false) {
      can.write(msg);
    }
  }

  const CanId can_id = {0x001, 0};
};

}  // namespace omuct_can_util

#endif  // OCU_P001_H_
