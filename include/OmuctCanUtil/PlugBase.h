#ifndef OCU_PLUG_BASE_H_
#define OCU_PLUG_BASE_H_

#include "CanMessage.h"
#include "CanUtil.h"

namespace omuct_can_util {

struct PlugBase {
  constexpr PlugBase(CanManager& manager, const CanId<CANExtended> id) noexcept : manager_{manager}, id_{id} {};

  // hard reset
  void hard_reset() {
    manager_.send_data(id_, {Command::hard_reset});
  }

  // start stop を切り替え
  void set_state(const State state) {
    manager_.send_data(id_, {state});
  }

 protected:
  CanManager& manager_;
  const CanId<CANExtended> id_;
};

}  // namespace omuct_can_util

#endif  // OCU_PLUG_BASE_H_
