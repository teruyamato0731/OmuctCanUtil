#ifndef OCU_CAN_FARM_H_
#define OCU_CAN_FARM_H_

namespace omuct_can_util {

struct FarmBase {
  virtual void who_am_i() = 0;
  void hard_reset() {
#ifdef __MBED__
    HAL_NVIC_SystemReset();
#else  // __MBED__
#error unsupported framework
#endif
  }

  virtual void set_state(const State state) {
    state_ = state;
  }

  // virtual void set_recieve_id(const uint16_t id, const uint8_t byte) {};
  // virtual void set_send_id(const uint16_t id, const uint8_t byte) {};
  // virtual void call_api_specify_command() {};

 protected:
  State state_ = State::stop;
};

}  // namespace omuct_can_util

#endif  // OCU_CAN_FARM_H_
