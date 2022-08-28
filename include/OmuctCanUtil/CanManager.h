/// Copyright (c) 2022 Yoshikawa Teru
/// This software is released under the MIT License, see LICENSE.
#ifndef OCU_CAN_MANAGER_H_
#define OCU_CAN_MANAGER_H_

#include <array>
#include <functional>
#include <tuple>

#include "CanBus.h"
#include "CanId.h"
#include "CanMessage.h"
#include "CanUtil.h"

namespace omuct_can_util {
OCU_BEGIN_NAMESPACE_VERSION

/// @brief CanBusを操作するインターフェイス
struct CanManager {
  /// @brief コンストラクタ
  /// @param CanBus CAN通信に使用するバス
  explicit CanManager(CanBus& can) noexcept : can_{can} {}

  /// @brief callback関数の設定
  /// @param f callback関数 CanMessageを受信したとき、呼び出される
  void set_callback(const std::function<void(CanMessage)> f) noexcept {
    f_ = f;
  }

  /// @brief CanBusを監視し、Messageがあった場合はcallback関数を呼び出す main-loop内で呼び出しておくこと
  void task() {
    if(!f_) return;
    if(CanMessage msg; can_.read(msg)) {
      f_(msg);
    }
  }

  /// @brief CanMessageをCanBusに送信
  /// @param msg 送信するメッセージ
  void send(const CanMessage& msg) {
    can_.write(msg);
  }
  /// @brief byte型配列をCanBusに送信
  /// @param id 送信先
  /// @param data 送信するデータ
  template<CanFormat E, std::size_t N>
  void send_data(const CanId<E> id, const uint8_t (&data)[N]) {
    CanMessage msg{id.get_id(), data, N, CANData, E};
    send(msg);
  }
  /// @brief argsをbyte型に変換してCanBusに送信
  /// @param id 送信先
  /// @param args... 送信するデータ
  /// @tparam Args... 送信するデータの型 trivially-copyable型 かつ standard-layout型 であること
  template<CanFormat E, class... Args>
  void send_data(const CanId<E> id, const Args&... args) {
    uint8_t data[(sizeof(Args) + ...)];
    make_data(data, args...);
    send_data(id, data);
  }

  /// @brief set_stateコマンドを送信する
  /// @param state セットするstate
  /// @param id 操作対象のid
  void set_state(const State state, const CanId<CANExtended>& id) {
    send_data(id, {Command::set_state, state});
  }
  /// @brief set_stateコマンドを送信する
  /// @param state セットするstate
  /// @param target 操作対象のapi-id
  void set_state(const State state, const ApiId target = ApiId::broadcast) {
    set_state(state, CanId<CANExtended>{target, ApiId::broadcast});
  }

  /// @brief who_am_iコマンドを送信する
  /// @param id 操作対象のid
  void who_am_i(const CanId<CANExtended>& id) {
    send_data(id, {Command::who_am_i});
  }
  /// @brief who_am_iコマンドを送信する
  /// @param target 操作対象のapi-id
  void who_am_i(const ApiId target = ApiId::broadcast) {
    who_am_i(CanId<CANExtended>{target, ApiId::broadcast});
  }

  /// @brief hard_resetコマンドを送信する
  /// @param id 操作対象のid
  void hard_reset(const CanId<CANExtended>& id) {
    send_data(id, {Command::hard_reset});
  }
  /// @brief hard_resetコマンドを送信する
  /// @param target 操作対象のapi-id
  void hard_reset(const ApiId target = ApiId::broadcast) {
    hard_reset(CanId<CANExtended>{target, ApiId::broadcast});
  }

 private:
  CanBus& can_;
  std::function<void(CanMessage)> f_;
};

OCU_END_NAMESPACE_VERSION
}  // namespace omuct_can_util

#endif  // OCU_CAN_MANAGER_H_
