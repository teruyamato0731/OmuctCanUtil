#ifndef CAN_ID_H_
#define CAN_ID_H_

#include <stdint.h>

namespace omuct_can_util {

struct CanId {
  enum {
    broadcast = 0
  };

  explicit constexpr CanId(uint32_t id) : id{id} {}

  static constexpr CanId make_can_id(const uint16_t api_id, const uint16_t individual_id, const bool is_return = false) noexcept {
    return CanId{((api_id & 0xfffu) << 13) | ((individual_id & 0xfffu) << 1) | is_return};
  }
  constexpr uint16_t get_api_id() const noexcept {
    return (id >> 13) & 0xfffu;
  }
  constexpr uint16_t get_individual_id() const noexcept {
    return (id >> 1) & 0xfffu;
  }
  constexpr bool is_return() const noexcept {
    return id & 1;
  }
  constexpr bool is_for_me(const uint32_t receive_id) const noexcept {
    return (receive_id == broadcast) || (receive_id == (id & 0xfff000u)) || (receive_id == id);
  }
  constexpr CanId make_return() const noexcept {
    return CanId{id | 1u};
  }
  constexpr uint32_t get_raw() const noexcept {
    return id;
  }
  constexpr void set_raw(const uint32_t id) {
    this->id = id;
  }
  uint32_t id;
};

}

#endif  // CAN_ID_H_
