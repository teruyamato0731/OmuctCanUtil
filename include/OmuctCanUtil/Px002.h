/// Copyright (c) 2022 Yoshikawa Teru
/// This software is released under the MIT License, see LICENSE.
/// ソレノイド基板のプラグイン
/// @file Px002.h
/// @author Yoshikawa Teru

#ifndef OCU_PX002_H_
#define OCU_PX002_H_

#include <optional>

#include "CanId.h"
#include "CanManager.h"
#include "CanMessage.h"
#include "CanUtil.h"
#include "PlugBase.h"

namespace omuct_can_util {

struct Px002 final : PlugBase {
  /// コンストラクタ
  /// @param manager CanManager
  /// @param individual_id 個体ID
  constexpr Px002(CanManager& manager, const uint16_t individual_id) noexcept
      : PlugBase{manager, CanId<CANExtended>{0x002, individual_id}} {}

  /// setupで呼び出し
  void setup(const uint16_t id, const State state) {
    set_mosi_id(id);
    set_state(state);
  }

  // master out slave in の id を設定
  void set_mosi_id(const uint16_t id) {
    set_mosi_id(CanId<CANStandard>{id});
  }
  void set_mosi_id(const CanId<CANStandard> receive_id) {
    receive_id_ = receive_id;
    manager_.send_data(id_, {Command::set_mosi_id}, receive_id.get_id());
    // manager_.send_data(id_, {Command::set_mosi_id, receive_id.upper(), receive_id.lower()});
  }

  // ソレノイドを出力
  void sol_write(const uint8_t sol_flg) {
    if(receive_id_) {
      sol_flg_ = sol_flg;
      manager_.send_data(id_, {sol_flg});
    }
  }

  // ソレノイドを出力(stopでも強制的に出力)
  void force_sol_write(const uint8_t sol_flg) {
    sol_flg_ = sol_flg;
    manager_.send_data(id_, {Command::call_api, SpecifyCommand_002::force_sol_write, sol_flg});
  }

 private:
  std::optional<CanId<CANStandard>> receive_id_ = std::nullopt;
  uint8_t sol_flg_ = 0;
};

}  // namespace omuct_can_util

#endif  // OCU_P002_H_
