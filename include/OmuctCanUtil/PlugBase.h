/// Copyright (c) 2022 Yoshikawa Teru
/// This software is released under the MIT License, see LICENSE.
#ifndef OCU_PLUG_BASE_H_
#define OCU_PLUG_BASE_H_

#include "CanManager.h"
#include "CanMessage.h"
#include "CanUtil.h"

namespace omuct_can_util {
OCU_BEGIN_NAMESPACE_VERSION

/// @brief プラグインのインターフェイス
struct PlugBase {
  /// コンストラクタ
  /// @param manager CAN通信に使用するCanManager
  /// @param unique_id 固有ID
  constexpr PlugBase(CanManager& manager, const CanId<CANExtended> unique_id) noexcept
      : manager_{manager}, unique_id_{unique_id} {};
  virtual ~PlugBase() noexcept = default;

  /// @brief hard_resetコマンドを送信する
  void hard_reset() {
    manager_.send_data(unique_id_, {Command::hard_reset});
  }

  /// @brief set_stateコマンドを送信する
  /// @param state セットするstate
  void set_state(const State state) {
    manager_.send_data(unique_id_, {state});
  }

 protected:
  CanManager& manager_;
  const CanId<CANExtended> unique_id_;
};

OCU_END_NAMESPACE_VERSION
}  // namespace omuct_can_util

#endif  // OCU_PLUG_BASE_H_
