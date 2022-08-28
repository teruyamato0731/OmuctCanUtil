/// Copyright (c) 2022 Yoshikawa Teru
/// This software is released under the MIT License, see LICENSE.
#ifndef OCU_PX002_H_
#define OCU_PX002_H_

#include <optional>

#include "CanId.h"
#include "CanManager.h"
#include "CanMessage.h"
#include "CanUtil.h"
#include "PlugBase.h"

namespace omuct_can_util {
OCU_BEGIN_NAMESPACE_VERSION

/// @brief ソレノイド基板のプラグイン
struct Px002 final : PlugBase {
  /// コンストラクタ
  /// @param manager CAN通信に使用するCanManager
  /// @param individual_id 個体ID
  constexpr Px002(CanManager& manager, const uint16_t individual_id) noexcept
      : PlugBase{manager, CanId<CANExtended>{0x002, individual_id}} {}

  /// @brief setupで呼び出し set_receive_idコマンドとset_stateコマンドを送信する
  /// @param receive_id ソレノイドの値を受け取るid
  /// @param state セットするstate
  /// @see set_mosi_id set_state
  void setup(const uint16_t receive_id, const State state) {
    set_mosi_id(receive_id);
    set_state(state);
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

  /// @brief receive_idにソレノイド出力コマンドを送信する
  /// @param sol_flg 8bitのソレノイド出力状態
  void sol_write(const uint8_t sol_flg) {
    if(receive_id_) {
      sol_flg_ = sol_flg;
      manager_.send_data(unique_id_, {sol_flg});
    }
  }

  /// @brief 固有IDにソレノイド出力コマンド(force_sol_write)を送信する
  /// @note stop状態でも強制的に出力される
  /// @param sol_flg 8bitのソレノイド出力状態
  void force_sol_write(const uint8_t sol_flg) {
    sol_flg_ = sol_flg;
    manager_.send_data(unique_id_, {Command::call_api, SpecifyCommand_002::force_sol_write, sol_flg});
  }

 private:
  std::optional<CanId<CANStandard>> receive_id_ = std::nullopt;
  uint8_t sol_flg_ = 0;
};

OCU_END_NAMESPACE_VERSION
}  // namespace omuct_can_util

#endif  // OCU_P002_H_
