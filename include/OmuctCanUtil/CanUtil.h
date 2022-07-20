#ifndef OCU_CAN_UTIL_H_
#define OCU_CAN_UTIL_H_

namespace omuct_can_util {

struct State {
  enum Type : uint8_t {
    stop = 0, start = 1
  };
  enum Type _type;
  State(const Type v) : _type(v) {}
  operator enum Type() const { return _type; }
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
  enum Type _type;
  Command(const Type v) : _type(v) {}
  operator enum Type() const { return _type; }
};

struct ApiId {
  enum Type : uint16_t {
    broadcast = 0,
    Px001 = 0x001,
    Px002 = 0x002,
    Px400 = 0x400,
    PxC00 = 0xC00,
  };
  enum Type _type;
  ApiId(const Type v) : _type(v) {}
  operator enum Type() const { return _type; }
};

// struct MosiPosition {
//   uint16_t id;
// };

// struct MisoPosition {
//   uint16_t id;
// };

// TODO Position どっちも統合 Misoじゃなくてreceive?

// struct Pwm {
//   float pwm;
//   /// @note aggregate
//   int get_int() {
//     return static_cast<int>(pwm*255)
//   }
// }

}  // namespace omuct_can_util

#endif  // OCU_CAN_UTIL_H_
