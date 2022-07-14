/// Copyright (c) 2022 Yoshikawa Teru
/// This software is released under the MIT License, see LICENSE.
/// サーボ基板のプラグイン
/// @file Px002.h
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

struct Px400 {
  // API固有コマンド
  struct SpecifyCommand {
    enum Type : uint8_t {
      force_write = 1,
      set_up = 2,
      set_min_pulse = 3,
      set_max_pulse = 4,
      set_one_cycle = 5,
    };
    enum Type _type;
    SpecifyCommand(const Type v) : _type(v) {}
    operator enum Type() const { return _type; }
  };
  struct __attribute__((packed)) ServoPulseConfig {
    uint16_t min_pulse_us;
    uint16_t max_pulse_us;
    uint16_t one_cycle_us;
  };

  /// コンストラクタ
  /// @param manager CanManager
  /// @param individual_id 個体ID
  constexpr Px400(CanManager& manager, const uint16_t individual_id) noexcept
      : manager_{manager}, id_{0x400, individual_id} {}

  /// setupで呼び出し
  void setup(const uint16_t id, const State state, const ServoPulseConfig& config) {
    set_mosi_id(id);
    set_state(state);
    set_config(config);
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
    uint8_t* data = reinterpret_cast<uint8_t*>(&(pos_.value()));
    const CANMessage msg{id_.get_raw(), data, sizeof(MosiPosition), CANData, CANExtended};
    manager_.send(msg);
  }

  void set_config(const ServoPulseConfig& config) {
    // uint8_t data[8] = {Command::call_api, SpecifyCommand::set_up};
    // ServoPulseConfig* p = &data[2];
    // // config_ = config;
    // *p = config;
    struct __attribute__((packed)) set_config {
      Command com;
      SpecifyCommand s_com;
      ServoPulseConfig config;
    } data = {Command::call_api, SpecifyCommand::set_up, config};
    const CANMessage msg{id_.get_raw(), &data, sizeof(MosiPosition), CANData, CANExtended};
    manager_.send(msg);
  }

  // hard reset
  void hard_reset() {
    uint8_t data[] = {Command::hard_reset};
    CANMessage msg{id_.get_raw(), data, size(data), CANData, CANExtended};
    manager_.send(msg);
  }

  // サーボを出力
  void servo_write(const float duty) {
    if(pos_) {
      uint8_t data[] = {Command::call_api, SpecifyCommand::force_set_state, duty};
      CANMessage msg{pos_->id, data, size(data), CANData, CANExtended};
      manager_.send(msg);
    }
  }

  // Deg/Radでサーボ出力 未実装 欲しくなったら実装する
  // void servo_write(const Degree deg) {}
  // void servo_write(const Radian rad) {}

  // サーボを出力
  void force_write(const float duty) {
    if(pos_) {
      uint8_t data[] = {Command::call_api, SpecifyCommand::force_set_state, duty};
      CANMessage msg{pos_->id, data, size(data), CANData, CANExtended};
      manager_.send(msg);
    }
  }

 private:
  CanManager& manager_;
  const CanId id_;
  std::optional<MosiPosition> pos_ = std::nullopt;
  // std::optional<ServoPulseConfig> config_ = std::optional;
  // State state_ = State::stop;
  // uint8_t duty = 0;
};

}  // namespace omuct_can_util

#endif  // OCU_P400_H_
