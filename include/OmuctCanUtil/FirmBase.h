/// Copyright (c) 2022 Yoshikawa Teru
/// This software is released under the MIT License, see LICENSE.
#ifndef OCU_CAN_FARM_H_
#define OCU_CAN_FARM_H_

#include "CanBus.h"
#include "CanId.h"
#include "CanMessage.h"
#include "CanUtil.h"

namespace omuct_can_util {
OCU_BEGIN_NAMESPACE_VERSION

// 仮想関数じゃなくてCRTPしたい！！！

/// @brief ファームウェアのインターフェイス
struct FirmBase {
  /// コンストラクタ
  /// @param can CAN通信に使用するバス
  /// @param id 固有ID
  FirmBase(CanBus& can, const CanId<CANExtended> unique_id) noexcept : can_{can}, unique_id_{unique_id} {}
  virtual ~FirmBase() noexcept = default;
  /// @brief 引数をもとにreceive_idをセットする
  /// @param data CanMessageのコマンドの引数
  virtual void set_mosi_id(const uint8_t (&data)[8]) {}
  /// @brief 引数をもとにsend_idをセットする
  /// @param data CanMessageのコマンドの引数
  virtual void set_miso_id(const uint8_t (&data)[8]) {}
  /// @brief 引数をもとにAPI固有コマンドを呼び出す
  /// @param data CanMessageのコマンドの引数
  virtual void call_api(const uint8_t (&data)[8]) {}
  /// @brief CanMessage受信時に呼び出される
  virtual void on_receive(const CanMessage& msg) {}

  /// @brief CanBusを監視し、Messageがあった場合はon_receiveを呼び出す main-loop内で呼び出しておくこと
  void task() {
    if(CanMessage msg; can_.read(msg)) {
      if(msg.format == CANExtended) {
        const CanId<CANExtended> msg_id{msg.id};
        if(msg_id.is_target(unique_id_)) {
          call_command(msg.data);
        }
      }
      on_receive(msg);
    }
  }

  /// @brief 引数をもとに各種コマンドを呼び出す
  /// @param data CanMessageのコマンドの引数
  void call_command(const uint8_t (&data)[8]) {
    switch(data[0]) {
      case Command::who_am_i:
        this->who_am_i();
        break;
      case Command::hard_reset:
        this->hard_reset();
        break;
      case Command::set_state:
        this->set_state(State{data[1]});
        break;
      case Command::set_mosi_id:
        this->set_mosi_id(data);
        break;
      case Command::set_miso_id:
        this->set_miso_id(data);
        break;
      case Command::call_api:
        this->call_api(data);
        break;
    }
  }

  /// @brief who_am_iコマンドを受信したときに実行 返信を行う
  void who_am_i() {
    CanMessage msg{unique_id_.make_return().get_id(), CANExtended};
    can_.write(msg);
  };

  /// @brief hard_resetコマンドを受信したときに実行 hard_resetを行う
  void hard_reset() {
#ifdef USE_HAL_DRIVER
    HAL_NVIC_SystemReset();
#else  // USE_HAL_DRIVER
#error unsupported framework
#endif
  }

  /// @brief set_stateコマンドを受信したときに実行 stateを更新する
  void set_state(const State state) noexcept {
    state_ = state;
  }

 protected:
  CanBus& can_;
  const CanId<CANExtended> unique_id_;
  State state_ = State::stop;
};

OCU_END_NAMESPACE_VERSION
}  // namespace omuct_can_util

#endif  // OCU_CAN_FARM_H_
