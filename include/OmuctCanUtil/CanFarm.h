#ifndef OCU_CAN_FARM_H_
#define OCU_CAN_FARM_H_

namespace omuct_can_util {

struct ReceivePosition {};

struct Pwm {
  float pwm;
  /// @note aggregate

  int get_int() {
    return static_cast<int>(pwm*255)
  }
}

}

#endif  // OCU_CAN_FARM_H_
