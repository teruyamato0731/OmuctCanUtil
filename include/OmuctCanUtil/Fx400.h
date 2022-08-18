#ifndef FARM400_H_
#define FARM400_H_

#include <mbed.h>

#include <array>
#include <optional>

#include "OmuctCanUtil/CanUtil.h"
#include "OmuctCanUtil/FirmBase.h"

struct Fx400 final : FirmBase {
  Fx400(CAN& can, const uint16_t individual_id, const PinName pin)
      : FirmBase{can, {0x002, individual_id}}, pwm_out{pin} {}

  void servo_write(const float duty) {
    if(config) {
      pwm_out.pulsewidth_us(config->min_us + duty * (config->max_us - config->min_us));
    }
  }

  void set_config(const ServoPulseConfig& config) {
    config_ = config;
    pwm_out.period_us(config.one_cycle_us);
  }

  void on_receive(const CanMessage& msg) override {
    if(msg.format == CANStandard && state_ == State::start && receive_id_ && msg.id == receive_id_->get_id()) {
      servo_write(data);
    }
  }

  void call_api(const uint8_t (&data)[8]) override {
    switch(data[1]) {
      case SpecifyCommand_002::force_sol_write:
        servo_write(parse<float>(&data[2]));
        break;
      case SpecifyCommand_002::set_config:
        set_config(parse<ServoPulseConfig>(&data[2]));
        break;
    }
  }

  void set_mosi_id(const uint8_t (&data)[8]) override {
    receive_id_ = CanId{&data[1]};
  }

 private:
  mbed::PwmOut pwm_out;
  std::optional<ServoPulseConfig> config_ = std::nullopt;
  std::optional<CanId<CANStandard>> receive_id_ = std::nullopt;
};

#endif  // FARM400_H_
