/// Copyright (c) 2022 Yoshikawa Teru
/// This software is released under the MIT License, see LICENSE.
#ifndef OCU_CAN_ID_H_
#define OCU_CAN_ID_H_

#include <cstddef>

#include "CanMessage.h"
#include "CanUtil.h"

namespace omuct_can_util {
OCU_BEGIN_NAMESPACE_VERSION

/// @tparam E 標準フォーマットID or 拡張フォーマットID
template<CanFormat E>
struct CanId;

/// @brief 標準フォーマットのCAN ID
/// @remark リトルエンディアンを使用すること
/// @remark standard-layout であることを規定
/// @remark trivially-copyable であることを規定
template<>
struct CanId<CANStandard> {
  /// コンストラクタ
  explicit constexpr CanId(const uint16_t id) : id_{id} {}
  explicit CanId(const uint8_t* const data) : id_{parse<uint16_t>(data)} {}
  /// トリビアルなコピームーブ可
  constexpr CanId(const CanId&) noexcept = default;
  constexpr CanId(CanId&&) noexcept = default;
  constexpr CanId& operator=(const CanId&) noexcept = default;
  constexpr CanId& operator=(CanId&&) noexcept = default;

  constexpr uint16_t get_id() const noexcept {
    return id_;
  }
 private:
  uint16_t id_;
};

/// @brief 拡張フォーマットのCAN ID
/// @remark standard-layout であることを規定
/// @remark trivially-copyable であることを規定
template<>
struct CanId<CANExtended> {
  /// コンストラクタ
  /// @param id 固有id
  explicit constexpr CanId(const uint32_t id) noexcept : id_{id} {}

  /// @param api_id API ID
  /// @param individual_id 個体ID
  /// @param is_return=false
  constexpr CanId(const uint16_t api_id, const uint16_t individual_id, const bool is_return = false) noexcept
      : id_{((api_id & 0xfffu) << 13) | ((individual_id & 0xfffu) << 1) | is_return} {}
  /// トリビアルなコピームーブ可
  constexpr CanId(const CanId&) noexcept = default;
  constexpr CanId(CanId&&) noexcept = default;
  constexpr CanId& operator=(const CanId&) noexcept = default;
  constexpr CanId& operator=(CanId&&) noexcept = default;

  // getter
  constexpr uint32_t get_id() const noexcept {
    return id_;
  }
  constexpr uint16_t get_api_id() const noexcept {
    return (id_ >> 13) & 0xfffu;
  }
  constexpr uint16_t get_individual_id() const noexcept {
    return (id_ >> 1) & 0xfffu;
  }

  // query
  constexpr bool is_return() const noexcept {
    return id_ & 1;
  }
  constexpr CanId make_return() const noexcept {
    return CanId{id_ | 1u};
  }
  constexpr bool is_target(const uint32_t receive_id) const noexcept {
    return is_target(CanId{receive_id});
  }
  constexpr bool is_target(const CanId receive_id) const noexcept {
    if(receive_id.is_return()) return false;

    return (receive_id.get_api_id() == ApiId::broadcast || receive_id.get_api_id() == this->get_api_id()) &&
           (receive_id.get_individual_id() == this->get_individual_id() ||
            receive_id.get_individual_id() == ApiId::broadcast);
  }

 private:
  const uint32_t id_;
};

OCU_END_NAMESPACE_VERSION
}  // namespace omuct_can_util

#endif  // OCU_CAN_ID_H_
