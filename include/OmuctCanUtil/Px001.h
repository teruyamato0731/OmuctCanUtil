#ifndef OCU_PX001_H_
#define OCU_PX001_H_

#include "CanId.h"
#include "CanMessage.h"
#include "PlugBase.h"

namespace omuct_can_util {

struct Px001 : PlugBase {
  constexpr Px001() noexcept = default;

  void task(CanBus& can, const CanMessage& msg) override {
    if(false) {
      can.write(msg);
    }
  }

  const CanId can_id = {0x001, 0};
};

}  // namespace omuct_can_util

#endif  // OCU_P001_H_
