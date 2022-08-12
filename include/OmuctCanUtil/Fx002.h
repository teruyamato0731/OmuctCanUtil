#ifndef FARM002_H_
#define FARM002_H_

#include <mbed.h>

#include <array>
#include <optional>

#include "OmuctCanUtil/CanUtil.h"
#include "OmuctCanUtil/FirmBase.h"

struct Fx002 final : FirmBase {
  Fx002(CanManager& manager, const uint16_t individual_id, const PinName (&pins)[6])
      : Fx002{manager, individual_id, pins, std::make_index_sequence<6>{}} {}
  template<std::size_t... I>
  Fx002(CanManager& manager, const uint16_t individual_id, const PinName (&pins)[6], std::index_sequence<I...>)
      : FirmBase{manager, {0x002, individual_id}}, sols_{pins[I]...} {}

  void sol_write(const uint8_t state) {
    for(uint8_t i = 0; i < 8; ++i) {
      sols[i] = state & (1 << i);
    }
  }

  void on_receive(const CanMessage& msg) override {
    if(msg.format == CANStandard && state_ == State::start && mosi_ && msg.id == mosi_->get_id()) {
      sol_write(msg.data[0]);
    }
  }

  void call_api(const uint8_t (&data)[8]) override {
    switch(data[1]) {
      case SpecifyCommand_002::force_sol_write:
        sol_write(data[2]);
        break;
    }
  }

  void set_mosi_id(const uint8_t (&data)[8]) override {
    mosi_ = CanId{data};
  }

 private:
  std::array<mbed::DigitalWrite, 8> sols_;
  std::optional<ShortCanId> mosi_ = std::nullopt;
};

#endif  // FARM002_H_
