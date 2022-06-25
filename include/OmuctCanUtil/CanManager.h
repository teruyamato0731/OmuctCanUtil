#ifndef OCU_CAN_MANAGER_H_
#define OCU_CAN_MANAGER_H_

#include <array>
#include <functional>
#include <tuple>

#include "CanBus.h"
#include "CanMessage.h"
#include "CanUtil.h"

namespace omuct_can_util {

struct CanManager {
  CanManager(CanBus& can) : can_{can} {}

  void set_callback(std::function<void(CanMessage)> f) noexcept {
    f_ = f;
  }

  void task() {
    if(CANMessage enc_msg; can_.read(enc_msg)) {
      printf("%d\n", enc_msg.id);
      f_(enc_msg);
    } else {
      printf("no msg\n");
    }
  }

  void send(const CanMessage& msg) {
    can_.write(msg);
  }

  void who_am_i(ApiId target = ApiId::broadcast) {
    uint8_t data[] = {static_cast<uint8_t>(Command::who_am_i)};
    CANMessage msg{static_cast<uint8_t>(target), data, size(data)};
    can_.write(msg);
  }

 private:
  CanBus& can_;
  std::function<void(CanMessage)> f_;
};

}  // namespace omuct_can_util

#endif  // OCU_CAN_MANAGER_H_
