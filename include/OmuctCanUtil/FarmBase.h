#ifndef OCU_CAN_FARM_H_
#define OCU_CAN_FARM_H_

namespace omuct_can_util {

struct FarmBase {
  virtual void who_am_i() = 0;
  virtual void hard_reset() = 0;  // HAL_NVIC_SystemReset
  virtual void set_state(const State state) {
    // state_ = state;
  }

  // virtual void stop() {
  //   state_ = State::stop;
  // }
  // virtual void start() {
  //   state_ = State::start;
  // }

  // virtual void set_recieve_id(const uint16_t id, const uint8_t byte) {};
  // virtual void set_send_id(const uint16_t id, const uint8_t byte) {};
  // virtual void call_api_specify_command() {};

 protected:
  // State state_ = State::stop;
};

// struct Pwm {
//   float pwm;
//   /// @note aggregate

//   int get_int() {
//     return static_cast<int>(pwm*255)
//   }
// }

}  // namespace omuct_can_util

#endif  // OCU_CAN_FARM_H_
