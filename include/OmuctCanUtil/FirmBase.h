#ifndef OCU_CAN_FARM_H_
#define OCU_CAN_FARM_H_

namespace omuct_can_util {

// TODO
struct FirmBase {
  void call_command(const uint8_t(data&)[8]) {
    switch(data[0]) {
      case Command::who_am_i:
        this->who_am_i();
        break;
      case Command::hard_reset:
        this->hard_reset();
        break;
      case Command::set_state:
        this->set_state(data[1]);
        break;
      case Command::set_mosi_id:
        this->set_mosi_id(data[1]);
        break;
      case Command::set_miso_id:
        this->set_miso_id(data[1]);
        break;
      case Command::call_api:
        this->call_api(data);
        break;
    }
  }

  void who_am_i() {
    CanId<CANExtended> id = this->get_id();
    uint8_t data[] = {};
  };

  void hard_reset() {
#ifdef USE_HAL_DRIVER
    HAL_NVIC_SystemReset();
#else  // USE_HAL_DRIVER
#error unsupported framework
#endif
  }

  void set_state(const State state) {
    state_ = state;
  }
  void set_mosi_id(const CanId<CANExtended>) {}
  void set_miso_id(const CanId<CANExtended>) {}
  void call_api(const uint8_t(data&)[8]) {}

 protected:
  State state_ = State::stop;
};

}  // namespace omuct_can_util

#endif  // OCU_CAN_FARM_H_
