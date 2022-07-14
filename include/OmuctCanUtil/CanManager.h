#ifndef OCU_CAN_MANAGER_H_
#define OCU_CAN_MANAGER_H_

#include <array>
#include <functional>
#include <tuple>

#include "CanBus.h"
#include "CanId.h"
#include "CanMessage.h"
#include "CanUtil.h"

namespace omuct_can_util {

struct CanManager {
  CanManager(CanBus& can) : can_{can} {}

  void set_callback(const std::function<void(CanMessage)> f) noexcept {
    f_ = f;
  }

  void task() {
    if(!f_) return;
    if(CanMessage msg; can_.read(msg)) {
      f_(msg);
    }
  }

  void send(const CanMessage& msg) {
    can_.write(msg);
  }

  void set_state(const State state, const CanId& id) {
    uint8_t data[] = {Command::set_state, state};
    CanMessage msg{id.get_raw(), data, size(data)};
    can_.write(msg);
  }
  void who_am_i(const CanId& id) {
    uint8_t data[] = {Command::who_am_i};
    CanMessage msg{id.get_raw(), data, size(data)};
    can_.write(msg);
  }
  void hard_reset(const CanId& id) {
    uint8_t data[] = {Command::hard_reset};
    CanMessage msg{id.get_raw(), data, size(data)};
    can_.write(msg);
  }

  void set_state(const State state, const ApiId target = ApiId::broadcast) {
    set_state(state, CanId{target, ApiId::broadcast});
  }
  void who_am_i(const ApiId target = ApiId::broadcast) {
    who_am_i(CanId{target, ApiId::broadcast});
  }
  void hard_reset(const ApiId target = ApiId::broadcast) {
    hard_reset(CanId{target, ApiId::broadcast});
  }

 private:
  CanBus& can_;
  std::function<void(CanMessage)> f_;
};

}  // namespace omuct_can_util

#endif  // OCU_CAN_MANAGER_H_
