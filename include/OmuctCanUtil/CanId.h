#ifndef OCU_CAN_ID_H_
#define OCU_CAN_ID_H_

#include <cstddef>

#include "OmuctCanUtil/CanMessage.h"
#include "OmuctCanUtil/CanUtil.h"

namespace omuct_can_util {

template<CANFormat E>
struct CanId;

template<>
struct CanId<CANExtended> {
  // コンストラクタ
  explicit constexpr CanId(const uint32_t id) noexcept : id_{id} {}
  constexpr CanId(const uint16_t api_id, const uint16_t individual_id, const bool is_return = false) noexcept
      : id_{((api_id & 0xfffu) << 13) | ((individual_id & 0xfffu) << 1) | is_return} {}
  constexpr CanId(const CanId& can_id) noexcept = default;
  constexpr CanId(CanId&& can_id) noexcept = default;

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
  // constexpr void set_raw(const uint32_t id) noexcept {
  //   id_ = id;
  // }
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

/// リトルエンディアンを使用すること
template<>
struct CanId<CANStandard> {
  explicit constexpr CanId(const uint16_t id) : id_{id} {}
  explicit constexpr CanId(const uint8_t* const data) : id_{parse<uint16_t>(data)} {}
  // explicit constexpr CanId(const uint8_t* const data) : id_{static_cast<uint16_t>(data[1] << 8u | data[0])} {}
  constexpr uint16_t get_id() const noexcept {
    return id_;
  }
  constexpr uint8_t operator[](const std::size_t n) const noexcept {
    return reinterpret_cast<const uint8_t(&)[2]>(id_)[n];
  }
  // constexpr uint8_t upper() const {
  //   return operator[](0);
  // }
  // constexpr uint8_t lower() const {
  //   return operator[](1);
  // }

 private:
  uint16_t id_;
};

}  // namespace omuct_can_util

#endif  // OCU_CAN_ID_H_
