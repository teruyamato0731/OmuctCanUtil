/// Copyright (c) 2022 Yoshikawa Teru
/// This software is released under the MIT License, see LICENSE.
/// サーボ基板のプラグイン
/// @file Px400.h
/// @author Yoshikawa Teru

#ifndef OCU_PX400_H_
#define OCU_PX400_H_

#include "CanId.h"
#include "CanManager.h"
#include "CanMessage.h"
#include "CanUtil.h"
#include "PlugBase.h"

// #include <optional>

namespace omuct_can_util {

struct Px400 final : PlugBase {
  /// コンストラクタ
  /// @param manager CanManager
  /// @param individual_id 個体ID
  constexpr Px400(CanManager& manager, const uint16_t individual_id) noexcept
      : PlugBase{manager, CanId<CANExtended>{0x400, individual_id}} {}

  /// setupで呼び出し
  void setup(const uint16_t id, const State state, const ServoPulseConfig& config) {
    set_mosi_id(id);
    set_state(state);
    set_config(config);
  }

  // master out slave in の id を設定
  void set_mosi_id(const uint16_t id) {
    set_mosi_id(CanId<CANStandard>{id});
  }
  void set_mosi_id(const CanId<CANStandard> receive_id) {
    receive_id_ = receive_id;
    manager_.send_data(id_, Command::set_mosi_id, receive_id.get_id());
  }

  void set_config(const ServoPulseConfig& config) {
    manager_.send_data(id_, Command::call_api, SpecifyCommand_400::set_config, config);
  }

  // サーボを出力
  void servo_write(const float duty) {
    if(receive_id_) {
      manager_.send_data(receive_id_.value(), Command::call_api, SpecifyCommand_400::force_write, duty);
    }
  }

  // Deg/Radでサーボ出力 未実装 欲しくなったら実装する
  // void servo_write(const Degree deg) {}
  // void servo_write(const Radian rad) {}

  // サーボを出力
  void force_write(const float duty) {
    manager_.send_data(id_, Command::call_api, SpecifyCommand_400::force_write, duty);
  }

 private:
  std::optional<CanId<CANStandard>> receive_id_ = std::nullopt;
};

}  // namespace omuct_can_util

#endif  // OCU_P400_H_
