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
    CANMessage msg{id_.get_id(), data, size(data), CANData, CANExtended};
    manager_.send(msg);
  }

  // master out slave in の id を設定
  void set_mosi_id(const uint16_t id) {
    set_mosi_id(CanId<CANStandard>{id});
  }

  void set_mosi_id(const CanId<CANStandard> receive_id) {
    receive_id_ = receive_id;
    // uint8_t* data = reinterpret_cast<uint8_t*>(&(receive_id_.value()));
    // CANMessage msg{id_.get_id(), data, sizeof(decltype(receive_id)), CANData, CANExtended};
    uint8_t data[] = {Command::set_mosi_id, receive_id[0], receive_id[1]};
    CANMessage msg{id_.get_id(), data, size(data)};
    manager_.send(msg);
  }

  // hard reset
  void hard_reset() {
    uint8_t data[] = {Command::hard_reset};
    CANMessage msg{id_.get_id(), data, size(data), CANData, CANExtended};
    manager_.send(msg);
  }

  // ソレノイドを出力
  void sol_write(const uint8_t sol_flg) {
    if(receive_id_) {
      sol_flg_ = sol_flg;
      CANMessage msg{receive_id_->get_id(), &sol_flg_, 1};
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
    CANMessage msg{id_.get_id(), data, size(data), CANData, CANExtended};
    manager_.send(msg);
  }

  template<CANFormat E, std::size_t N>
  void send_data(const CanId<E> id, uint8_t(&data)[N]) {
    CANMessage msg{id.get_id(), data, N, CANData, E};
    manager_.send(msg);
  }

 private:
  CanManager& manager_;
  const CanId<CANExtended> id_;
  std::optional<CanId<CANStandard> > receive_id_ = std::nullopt;
  uint8_t sol_flg_ = 0;
};

}  // namespace omuct_can_util

#endif  // OCU_P002_H_
