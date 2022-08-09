#ifndef FARM002_H_
#define FARM002_H_

#include <array>
#include <optional>
#include <OmuctCanUtil/FirmBase.h>
#include <mbed.h>

struct Fx002 : FirmBase {
  struct SpecifyCommand {
    enum Type : uint8_t {
      force_sol_write = 1,
    };
    enum Type _type;
    State(const Type v) : _type(v) {}
    operator enum Type() const { return _type; }
  };

  constexpr uint16_t api_id = 0x002;
  template<class... Args>
  Fx002(const CanBus& can, const uint16_t individual_id, const Args... pins) : can_{can}, id_{api_id, individual_id} ,sols_{pins}... {
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
    switch (data[1]) {
      case 1:  // force digital out
        sol_write(data[2]);
        break;
    }
  }

  void call_command(const uint8_t (&data)[8]) {
    switch (data[0]) {
      case 1:  // Who am I
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
