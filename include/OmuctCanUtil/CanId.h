#ifndef OCU_CAN_ID_H_
#define OCU_CAN_ID_H_

#include <stdint.h>

namespace omuct_can_util {

struct CanId {
  static constexpr CanId make(const uint32_t id) noexcept {
    return CanId{id};
  }
  constexpr CanId(const uint16_t api_id, const uint16_t individual_id, const bool is_return = false) noexcept
      : id_{((api_id & 0xfffu) << 13) | ((individual_id & 0xfffu) << 1) | is_return} {}
  constexpr uint16_t get_api_id() const noexcept {
    return (id_>> 13) & 0xfffu;
  }
  constexpr uint16_t get_individual_id() const noexcept {
    return (id_>> 1) & 0xfffu;
  }
  constexpr bool is_return() const noexcept {
    return id_& 1;
  }
  constexpr CanId make_return() const noexcept {
    return CanId{id_| 1u};
  }
  constexpr uint32_t get_raw() const noexcept {
    return id_;
  }
  // constexpr void set_raw(const uint32_t id) noexcept {
  //   id_ = id;
  // }
  constexpr bool include(const uint32_t receive_id) const noexcept {
    return include(CanId::make(receive_id));
  }
  constexpr bool include(const CanId receive_id) const noexcept {
    if(receive_id.is_return()) return false;

    return (receive_id.get_api_id() == ApiId::broadcast || receive_id.get_api_id() == id_.get_api_id()) &&
           (receive_id.get_individual_id() == id_.get_individual_id() || receive_id.get_individual_id() == ApiId::broadcast);
  }

 private:
  explicit constexpr CanId(const uint32_t id) noexcept : id_{id} {}
  const uint32_t id_;
};

struct ShortCanId {
  auto data() -> uint8_t(&)[2] {
    return reinterpret_cast<uint8_t(&)[2]>(id);
  }
  auto id() const noexcept {
    return id;
  }
 private:
  uint16_t id;
};

}  // namespace omuct_can_util

#endif  // OCU_CAN_ID_H_
