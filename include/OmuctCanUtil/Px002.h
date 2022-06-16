#ifndef OCU_PX002_H_
#define OCU_PX002_H_

#include "CanId.h"
#include "CanMessage.h"
#include "PlugBase.h"

namespace omuct_can_util {

struct Px002 : PlugBase {
  constexpr Px002(const CanId individual_id) noexcept
      : id_{0x02, individual_id} {}

  // TODO friend & private?
  void task(CanBus& can, const CanMessage&) override {
    if(false) {
      CanMessage msg{};
      can.write(msg);
    }
  }

  void send_state(CanBus& can) {
    // TODO
    CanMessage msg{};
    can.write(msg);
  }

  void set_state(const uint8_t state) {
    state_ = state;
  }

 private:
  const CanId id_;
  uint8_t state_ = 0;
  // bool send_flg
};

}  // namespace omuct_can_util

#endif  // OCU_P002_H_
