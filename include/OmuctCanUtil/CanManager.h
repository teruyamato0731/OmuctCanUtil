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
  explicit CanManager(CanBus& can) noexcept : can_{can} {}

  // CanMessageを受信したとき、task内で呼び出されるcallback関数を設定する
  void set_callback(const std::function<void(CanMessage)> f) noexcept {
    f_ = f;
  }

  // CanMessageを受信時、callback関数を呼び出し
  void task() {
    if(!f_) return;
    if(CanMessage msg; can_.read(msg)) {
      f_(msg);
    }
  }

  // CanBusにCanMessageを送信
  void send(const CanMessage& msg) {
    can_.write(msg);
  }
  // CanBusにdataを送信
  template<CanFormat E, std::size_t N>
  void send_data(const CanId<E> id, const uint8_t (&data)[N]) {
    CanMessage msg{id.get_id(), data, N, CANData, E};
    send(msg);
  }
  // CanBusにargsを送信
  template<CanFormat E, class... Args>
  void send_data(const CanId<E> id, const Args&... args) {
    uint8_t data[(sizeof(Args) + ...)];
    make_data(data, args...);
    send_data(id, data);
  }

  void set_state(const State state, const CanId<CANExtended>& id) {
    send_data(id, {Command::set_state, state});
  }
  void who_am_i(const CanId<CANExtended>& id) {
    send_data(id, {Command::who_am_i});
  }
  void hard_reset(const CanId<CANExtended>& id) {
    send_data(id, {Command::hard_reset});
  }

  void set_state(const State state, const ApiId target = ApiId::broadcast) {
    set_state(state, CanId<CANExtended>{target, ApiId::broadcast});
  }
  void who_am_i(const ApiId target = ApiId::broadcast) {
    who_am_i(CanId<CANExtended>{target, ApiId::broadcast});
  }
  void hard_reset(const ApiId target = ApiId::broadcast) {
    hard_reset(CanId<CANExtended>{target, ApiId::broadcast});
  }

 private:
  CanBus& can_;
  std::function<void(CanMessage)> f_;
};

}  // namespace omuct_can_util

#endif  // OCU_CAN_MANAGER_H_
