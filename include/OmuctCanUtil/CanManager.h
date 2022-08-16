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

  template<CANFormat E, std::size_t N>
  void send_data(const CanId<E> id, const uint8_t (&data)[N]) {
    CanMessage msg{id.get_id(), data, N, CANData, E};
    send(msg);
  }
  template<CANFormat E, std::size_t N, std::size_t O, std::size_t... I, std::size_t... J>
  void send_data(const CanId<E> id, const uint8_t (&data)[N], const uint8_t (&data2)[O], std::index_sequence<I...>,
                 std::index_sequence<J...>) {
    send_data(id, {data[I]..., data2[J]...});
  }
  template<CANFormat E, std::size_t N, class T>
  void send_data(const CanId<E> id, const uint8_t (&data)[N], const T& t) {
    send_data(id, data, reinterpret_cast<const uint8_t(&)[sizeof(T)]>(t), std::make_index_sequence<N>(),
              std::make_index_sequence<sizeof(T)>());
  }

  void set_state(const State state, const CanId<CANExtended>& id) {
    send_data(id, {Command::set_state, state});
  }
  void get_state(const CanId<CANExtended>& id) {
    send_data(id, {Command::get_state});
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
  void get_state(const ApiId target = ApiId::broadcast) {
    get_state(CanId<CANExtended>{target, ApiId::broadcast});
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
