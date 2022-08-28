/// Copyright (c) 2022 Yoshikawa Teru
/// This software is released under the MIT License, see LICENSE.
#ifndef OCU_FARM002_H_
#define OCU_FARM002_H_

#include <mbed.h>

#include <array>
#include <optional>

#include "CanUtil.h"
#include "FirmBase.h"

namespace omuct_can_util {
OCU_BEGIN_NAMESPACE_VERSION

/// @brief ソレノイドのファームウェア ソースはexampleのFirm内
struct Fx002 final : FirmBase {
  /// コンストラクタ
  /// @param can 通信に使用するCanBus
  /// @param individual_id 個体ID
  /// @param pins ソレノイド出力に使用するピン
  Fx002(CAN& can, const uint16_t individual_id, const PinName (&pins)[8])
      : Fx002{can, individual_id, pins, std::make_index_sequence<8>{}} {}
  template<std::size_t... I>
  Fx002(CAN& can, const uint16_t individual_id, const PinName (&pins)[8], std::index_sequence<I...>)
      : FirmBase{can, {0x002, individual_id}}, sols_{pins[I]...} {}

  /// コピームーブ不可
  Fx002(const Fx002&) = delete;
  Fx002(Fx002&&) = delete;

  /// @brief sol_flgをもとに1bitずつソレノイドを出力する
  /// @param sol_flg 8bitのソレノイド出力状態
  void sol_write(const uint8_t state) {
    for(uint8_t i = 0; i < 8; ++i) {
      sols[i] = state & (1 << i);
    }
  }

  void on_receive(const CanMessage& msg) override {
    if(msg.format == CANStandard && state_ == State::start && receive_id_ && msg.id == receive_id_->get_id()) {
      sol_write(msg.data[0]);
    }
  }

  /// @brief force_sol_writeを受信したとき、sol_writeを呼び出し
  void call_api(const uint8_t (&data)[8]) override {
    switch(data[1]) {
      case SpecifyCommand_002::force_sol_write:
        sol_write(data[2]);
        break;
    }
  }

  void set_mosi_id(const uint8_t (&data)[8]) override {
    receive_id_ = CanId{&data[1]};
  }

 private:
  std::array<mbed::DigitalWrite, 8> sols_;
  std::optional<CanId<CANStandard>> receive_id_ = std::nullopt;
};

OCU_END_NAMESPACE_VERSION
}  // namespace omuct_can_util

#endif  // OCU_FARM002_H_
