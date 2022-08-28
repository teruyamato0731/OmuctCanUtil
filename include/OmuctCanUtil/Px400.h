/// Copyright (c) 2022 Yoshikawa Teru
/// This software is released under the MIT License, see LICENSE.
#ifndef OCU_PX400_H_
#define OCU_PX400_H_

#include "CanId.h"
#include "CanManager.h"
#include "CanMessage.h"
#include "CanUtil.h"
#include "PlugBase.h"

namespace omuct_can_util {
OCU_BEGIN_NAMESPACE_VERSION

/// @brief サーボ基板のプラグイン
struct Px400 final : PlugBase {
  /// コンストラクタ
  /// @param manager CAN通信に使用するCanManager
  /// @param individual_id 個体ID
  constexpr Px400(CanManager& manager, const uint16_t individual_id) noexcept
      : PlugBase{manager, CanId<CANExtended>{0x400, individual_id}} {}

  /// @brief setupで呼び出し set_receive_id, set_state, set_configコマンドを送信する
  /// @param receive_id ソレノイドの値を受け取るid
  /// @param state セットするstate
  /// @param config セットするサーボ設定
  void setup(const uint16_t receive_id, const State state, const ServoPulseConfig& config) {
    set_mosi_id(receive_id);
    set_state(state);
    set_config(config);
  }

  /// @brief set_receive_idコマンドを送信する
  /// @param receive_id セットする受信ID
  void set_mosi_id(const uint16_t receive_id) {
    set_mosi_id(CanId<CANStandard>{receive_id});
  }
  /// @brief set_receive_idコマンドを送信する
  /// @param receive_id セットする受信ID
  void set_mosi_id(const CanId<CANStandard> receive_id) {
    receive_id_ = receive_id;
    manager_.send_data(unique_id_, Command::set_mosi_id, receive_id.get_id());
  }

  /// @brief set_configコマンドを送信する
  /// @param config セットするサーボ設定
  void set_config(const ServoPulseConfig& config) {
    manager_.send_data(unique_id_, Command::call_api, SpecifyCommand_400::set_config, config);
  }

  /// @brief receive_idにサーボ出力コマンドを送信する
  /// @param duty 出力するデューティ比
  void servo_write(const float duty) {
    if(receive_id_) {
      manager_.send_data(receive_id_.value(), Command::call_api, SpecifyCommand_400::force_write, duty);
    }
  }

  /// @brief 固有IDにサーボ出力コマンド(force_write)を送信する
  /// @param duty 出力するデューティ比
  void force_write(const float duty) {
    manager_.send_data(unique_id_, Command::call_api, SpecifyCommand_400::force_write, duty);
  }

  // Deg/Radでサーボ出力 未実装 欲しくなったら実装する
  // void servo_write(const Degree deg) {}
  // void servo_write(const Radian rad) {}

 private:
  std::optional<CanId<CANStandard>> receive_id_ = std::nullopt;
};

OCU_END_NAMESPACE_VERSION
}  // namespace omuct_can_util

#endif  // OCU_P400_H_
