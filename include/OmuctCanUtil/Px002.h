/// Copyright (c) 2022 Yoshikawa Teru
/// This software is released under the MIT License, see LICENSE.
/// ソレノイド基板のプラグイン
/// @file Px002.h
/// @author Yoshikawa Teru

#ifndef OCU_PX002_H_
#define OCU_PX002_H_

#include "CanId.h"
#include "CanManager.h"
#include "CanMessage.h"
#include "CanUtil.h"
#include "PlugBase.h"

#include <optional>

namespace omuct_can_util {

// namespace detail {
// struct ForceSolWrite {
//   Command = static_cast<uint8_t>(Command::call_api);
//   SpecifyCommand = static_cast<uint8_t>(SpecifyCommand::force_set_state);
//   uint8_t sol_flg;
// };
// }

struct Px002 : PlugBase {
  // API固有コマンド
  struct SpecifyCommand {
    enum Type : uint8_t {
      force_sol_write = 1,
    };
    enum Type _type;
    SpecifyCommand(const Type v) : _type(v) {}
    operator enum Type() const { return _type; }
  };

  /// コンストラクタ
  /// @param manager CanManager
  /// @param individual_id 個体ID
  constexpr Px002(CanManager& manager, const uint16_t individual_id) noexcept
      : manager_{manager}, id_{0x002, individual_id} {}

  /// setupで呼び出し
  void setup(const uint16_t id, const State state) {
    set_mosi_id(id);
    set_state(state);
  }

  // start stop を切り替え
  void set_state(const State state) {
    uint8_t data[] = {state};
    CANMessage msg{id_.get_raw(), data, size(data), CANData, CANExtended};
  }

  // master out slave in の id を設定
  void set_mosi_id(const uint16_t id) {
    set_mosi_id(MosiPosition{id});
  }

  void set_mosi_id(const MosiPosition pos) {
    pos_ = pos;
    // uint8_t* data = reinterpret_cast<uint8_t*>(&(pos_.value()));
    // CANMessage msg{id_.get_raw(), data, sizeof(decltype(pos)), CANData, CANExtended};
    uint8_t data[] = {static_cast<uint8_t>(Command::set_mosi_id), static_cast<uint8_t>(id >> 8u), static_cast<uint8_t>(id & 0xffu)};
    CANMessage msg{id_.get_raw(), data, size(data)};
    manager_.send(msg);
  }

  // hard reset
  void hard_reset() {
    uint8_t data[] = {Command::hard_reset};
    CANMessage msg{id_.get_raw(), data, size(data), CANData, CANExtended};
    manager_.send(msg);
  }

  // ソレノイドを出力
  void sol_write(const uint8_t sol_flg) {
    if(pos_) {
      sol_flg_ = sol_flg;
      CANMessage msg{pos_->id, &sol_flg_, 1};
      manager_.send(msg);
    }
  }

  // ソレノイドを出力(stopでも強制的に出力)
  void force_sol_write(const uint8_t sol_flg) {
    sol_flg_ = sol_flg;
    uint8_t data[] = {
      Command::call_api,
      SpecifyCommand::force_sol_write,
      sol_flg_
    };
    CANMessage msg{id_.get_raw(), data, size(data), CANData, CANExtended};
    manager_.send(msg);
  }

 private:
  CanManager& manager_;
  const CanId id_;
  std::optional<MosiPosition> pos_ = std::nullopt;
  // State state_ = State::stop;
  uint8_t sol_flg_ = 0;
};

}  // namespace omuct_can_util

#endif  // OCU_P002_H_
