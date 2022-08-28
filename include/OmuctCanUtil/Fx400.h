/// Copyright (c) 2022 Yoshikawa Teru
/// This software is released under the MIT License, see LICENSE.
#ifndef OCU_FARM400_H_
#define OCU_FARM400_H_

#include <mbed.h>

#include <array>
#include <optional>

#include "CanUtil.h"
#include "FirmBase.h"

namespace omuct_can_util {
OCU_BEGIN_NAMESPACE_VERSION

/// @brief サーボ基板のファームウェア ソースはexampleのFirm内
struct Fx400 final : FirmBase {
  /// コンストラクタ
  /// @param can 通信に使用するCanBus
  /// @param individual_id 個体ID
  /// @param pins サーボ出力に使用するピン
  Fx400(CAN& can, const uint16_t individual_id, const PinName pin)
      : FirmBase{can, {0x002, individual_id}}, pwm_out{pin} {}

  /// コピームーブ不可
  Fx002(const Fx002&) = delete;
  Fx002(Fx002&&) = delete;

  /// @brief 現在のconfigからパルス幅を計算しPWMを出力する
  /// @param duty 出力するデューティ比 0.0<=duty<=1.0
  void servo_write(const float duty) {
    if(config_) {
      pwm_out.pulsewidth_us(config_->min_us + duty * (config_->max_us - config_->min_us));
    }
  }

  /// @brief set_config受信時に実行
  /// @param config セットするサーボのパルス幅設定
  void set_config(const ServoPulseConfig& config) {
    config_ = config;
    pwm_out.period_us(config.one_cycle_us);
  }

  /// @brief メッセージ受信時の動作 task内で呼び出される
  /// @param msg 受信したメッセージ
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

OCU_END_NAMESPACE_VERSION
}  // namespace omuct_can_util

#endif  // OCU_FARM400_H_
