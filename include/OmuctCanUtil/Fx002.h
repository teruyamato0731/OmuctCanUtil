#ifndef FARM002_H_
#define FARM002_H_

#include <mbed.h>

#include <array>
#include <optional>

#include "OmuctCanUtil/CanUtil.h"
#include "OmuctCanUtil/FirmBase.h"

struct Fx002 : FirmBase {
  template<class... Args>
  Fx002(const CanBus& can, const uint16_t individual_id, const Args... pins)
      : can_{can}, id_{0x002, individual_id}, sols_{pins}... {
    static_assert(sizeof...(Args) == 8);
  }

  auto get_id() const noexcept {
    return id_;
  }

  void sol_write(const uint8_t state) {
    for(uint8_t i = 0; i < 8; ++i) {
      sols[i] = state & (1 << i);
    }
  }

  void set_mosi_id(const CanId<CANExtended> id) {
    mosi_ = id;
  }

  void call_api(const uint8_t (&data)[8]) {
    switch(data[1]) {
      case SpecifyCommand_002::force_sol_write:
        sol_write(data[2]);
        break;
    }
  }

  void call_command(const uint8_t (&data)[8]) {
    switch(data[0]) {
      case Command::who_am_i:
        who_am_I(data[2]);
        break;
    }
  }

  void task() {
    // TODO
    if(CanMessage msg; can.read(msg)) {
      if(msg.format == CANExtended) {
        const CanId<CANExtended> msg_id = {msg.id};
        if(msg_id.is_target(id_)) {
          call_command(msg.data);
        }
      } else if(msg.format == CANStandard && state_ == State::start) {
        if(msg.id == mosi_->get_id()) {
          sol_write(data[0]);
        }
      }
    }
  }

 private:
  CanBus& can_;
  CanId<CANExtended> id_;
  std::array<mbed::DigitalWrite, 8> sols_;
  std::optional<ShortCanId> mosi_ = std::nullopt;
};

#endif  // FARM002_H_
