#ifndef OCU_CAN_UTIL_H_
#define OCU_CAN_UTIL_H_

namespace omuct_can_util {

enum class State : uint8_t {
  stop = 0, start = 1
};

enum class Command : uint8_t {
  who_am_i = 0,
  hard_reset = 1,
  stop = 2,
  start = 3,
  set_mosi_id = 4,
  set_miso_id = 5,
  call_api = 255,
};

enum class ApiId : uint16_t {
  broadcast = 0,
  Px001 = 0x001,
  Px002 = 0x002,
  Px400 = 0x400,
  PxC00 = 0xC00,
};

struct MosiPosition {
  uint16_t id;
  // uint8_t byte;
};

struct MisoPosition {
  uint16_t id;
  // uint8_t byte;
};

}  // namespace omuct_can_util

#endif  // OCU_CAN_UTIL_H_
