/// Copyright (c) 2022 Yoshikawa Teru
/// This software is released under the MIT License, see LICENSE.
#ifndef OCU_CAN_UTIL_H_
#define OCU_CAN_UTIL_H_

#include <cstdint>
#include <cstring>

#ifndef OCU_NO_INLINE_VERSION
/// @version 1.0.0
#define OCU_BEGIN_NAMESPACE_VERSION namespace ocu1_0_0 {
#define OCU_END_NAMESPACE_VERSION }
namespace omuct_can_util {
inline OCU_BEGIN_NAMESPACE_VERSION OCU_END_NAMESPACE_VERSION
}
#else
#define OCU_BEGIN_NAMESPACE_VERSION
#define OCU_END_NAMESPACE_VERSION
#endif  // OCU_NO_INLINE_VERSION

namespace omuct_can_util {
OCU_BEGIN_NAMESPACE_VERSION

/// @brief uint8_t* data を T型オブジェクトに変換
/// @param data 変換元データ
/// @tparam T 変換先の型 trivially-copyable型 かつ standard-layout型 であること
/// @return 変換後データ
template<class T>
T parse(const uint8_t* const data) {
  alignas(T) uint8_t t_buff[sizeof(T)];
  memcpy(t_buff, data, sizeof(T));
  return *reinterpret_cast<T*>(t_buff);
}

/// @brief args...を uint8_t* data に変換
/// @param buf 変換後データを入れるバッファ
/// @param head,args... 変換元データ
/// @tparam Head,Args... 変換元の型 trivially-copyable型 かつ standard-layout型 であること
template<class Head, class... Args>
void make_data(uint8_t* buf, const Head& head, const Args&... args) {
  memcpy(buf, &head, sizeof(Head));
  if constexpr(sizeof...(Args)) {
    make_data(buf + sizeof(Head), args...);
  }
}

// 動作状態
struct State {
  enum Type : uint8_t {
    stop = 0,
    start = 1,
  };
  State(const Type v) noexcept : type_(v) {}
  explicit State(const uint8_t v) noexcept : type_(static_cast<Type>(v)) {}
  operator enum Type() const noexcept { return type_; }
 private : enum Type type_;
};

struct Command {
  enum Type : uint8_t {
    who_am_i = 0,
    hard_reset = 1,
    set_state = 2,
    set_mosi_id = 3,
    set_miso_id = 4,
    call_api = 255,
  };
  Command(const Type v) noexcept : type_(v) {}
  explicit Command(const uint8_t v) noexcept : type_(static_cast<Type>(v)) {}
  operator enum Type() const noexcept { return type_; }
 private : enum Type type_;
};

struct ApiId {
  enum Type : uint16_t {
    broadcast = 0,
    Px001 = 0x001,
    Px002 = 0x002,
    Px400 = 0x400,
    PxC00 = 0xC00,
  };
  ApiId(const Type v) noexcept : type_(v) {}
  explicit ApiId(const uint8_t v) noexcept : type_(static_cast<Type>(v)) {}
  operator enum Type() const noexcept { return type_; }
 private : enum Type type_;
};

// API固有コマンド
struct SpecifyCommand_002 {
  enum Type : uint8_t {
    force_sol_write = 1,
  };
  SpecifyCommand_002(const Type v) noexcept : type_(v) {}
  explicit SpecifyCommand_002(const uint8_t v) noexcept : type_(static_cast<Type>(v)) {}
  operator enum Type() const noexcept { return type_; }
 private : enum Type type_;
};
struct SpecifyCommand_400 {
  enum Type : uint8_t {
    force_write = 1,
    set_config = 2,
  };
  SpecifyCommand_400(const Type v) noexcept : type_(v) {}
  explicit SpecifyCommand_400(const uint8_t v) noexcept : type_(static_cast<Type>(v)) {}
  operator enum Type() const noexcept { return type_; }
 private : enum Type type_;
};

/// @brief サーボ設定
/// @note trivial型 かつ standard-layout型
struct __attribute__((packed)) ServoPulseConfig {
  uint16_t min_pulse_us;  // 最小パルス幅(マイクロ秒)
  uint16_t max_pulse_us;  // 最大パルス幅(マイクロ秒)
  uint16_t one_cycle_us;  // PWM信号の1周期(マイクロ秒)
};

OCU_END_NAMESPACE_VERSION
}  // namespace omuct_can_util

#ifndef OCU_NO_GLOBAL_USING_DIRECTIVE
using namespace omuct_can_util;
#endif

#endif  // OCU_CAN_UTIL_H_
