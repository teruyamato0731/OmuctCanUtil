#ifndef OCU_CAN_MANAGER_H_
#define OCU_CAN_MANAGER_H_

#include <array>
#include <functional>
#include <tuple>

#include "CanBus.h"
#include "CanMessage.h"

#include <mbed.h>

namespace omuct_can_util {

template<class ...Args>
struct CanManager {
  CanManager(CanBus& can, Args&... args) : can_{can}, t_{args...} {
    timer_.start();
  }

  // TODO先で read呼び出し出来ないように
  void task() {
    CanMessage msg;
    can_.read(msg);
    // const auto delta_period = timer_.elapsed_time();  // TODO
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

  CanBus& can_;
  std::tuple<Args&...> t_;
  mbed::Timer timer_;
};

}  // namespace omuct_can_util

#endif  // OCU_CAN_MANAGER_H_
