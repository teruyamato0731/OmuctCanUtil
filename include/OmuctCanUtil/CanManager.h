#ifndef OCU_CAN_MANAGER_H_
#define OCU_CAN_MANAGER_H_

#include <array>
#include <functional>
#include <tuple>

#include "CanBus.h"
#include "CanMessage.h"

namespace omuct_can_util {

template<class T, class ...Args>
struct CanManager {
  CanManager(T& can, Args&... args) : can_{can}, t_{args...} {}

  void task() {
    const CanMessage msg = can_.read();
    task_impl<0, sizeof...(Args)>(msg);
  }

  template<int I, int N>
  void task_impl(const CanMessage& msg) {
    if constexpr (I < N) {
      std::get<I>(t_).task(can_, msg);
      task_impl<I+1, N>(msg);
    }
  }

  // void send(const CanMessage& msg) {
  //   can_.write(msg);
  // }

  T& can_;
  std::tuple<Args&...> t_;
};

// deduction guide
template<class...Args>
CanManager(T, Args&&...) -> CanManager<T, sizeof...(Args)>;

}  // namespace omuct_can_util

#endif  // OCU_CAN_MANAGER_H_
