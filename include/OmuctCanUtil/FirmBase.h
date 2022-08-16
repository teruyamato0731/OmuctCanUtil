#ifndef OCU_CAN_FARM_H_
#define OCU_CAN_FARM_H_

#include "CanMessage.h"
#include "CanUtil.h"

namespace omuct_can_util {

// 仮想関数じゃなくてCRTPしたい！！！
struct FirmBase {
  FirmBase(CAN& can, const CanId<CANExtended> id) noexcept : manager_{manager}, id_{id} {}
  virtual ~FirmBase() = default;
  virtual void set_mosi_id(const uint8_t(data&)[8]) {}
  virtual void set_miso_id(const uint8_t(data&)[8]) {}
  virtual void call_api(const uint8_t(data&)[8]) {}
  virtual void on_receive(const CanMessage& msg) {}

  void task() {
    if(CanMessage msg; can.read(msg)) {
      if(msg.format == CANExtended) {
        const CanId<CANExtended> msg_id = {msg.id};
        if(msg_id.is_target(id_)) {
          call_command(msg.data);
        }
      }
      on_receive(msg);
    }
  }

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
        this->set_mosi_id(data);
        break;
      case Command::set_miso_id:
        this->set_miso_id(data);
        break;
      case Command::call_api:
        this->call_api(data);
        break;
    }
  }

  void who_am_i() {
    CanMessage msg{id_.make_return().get_id(), CANExtended};
    can.send(msg);
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

 protected:
  CAN& can;
  const CanId<CANExtended> id_;
  State state_ = State::stop;
};

}  // namespace omuct_can_util

#endif  // OCU_CAN_FARM_H_
