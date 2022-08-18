#ifndef OCU_CAN_UTIL_H_
#define OCU_CAN_UTIL_H_

#include <cstdint>

namespace omuct_can_util {

/// @brief uint8_t*data を T型オブジェクトに変換 (T は standard layout であること)
template<class T>
T parse(const uint8_t* const data) {
  T* tp;
  memcpy(tp, data, sizeof(T));
  return *tp;
}

template<class Head, class... Args>
void make_data(uint8_t* data, const Head& head, const Args&... args) {
  std::memcpy(data, reinterpret_cast<const uint8_t*>(&head), sizeof(Head));
  if constexpr(sizeof...(Args)) {
    make_data(data + sizeof(Head), args...);
  }
}

// 動作状態
struct State {
  enum Type : uint8_t {
    stop = 0,
    start = 1,
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

// API固有コマンド
struct SpecifyCommand_002 {
  enum Type : uint8_t {
    force_sol_write = 1,
  };
  enum Type _type;
  SpecifyCommand_002(const Type v) : _type(v) {}
  operator enum Type() const { return _type; }
};
struct SpecifyCommand_400 {
  enum Type : uint8_t {
    force_write = 1,
    set_config = 2,
  };
  enum Type _type;
  SpecifyCommand_400(const Type v) : _type(v) {}
  operator enum Type() const { return _type; }
};
struct __attribute__((packed)) ServoPulseConfig {
  uint16_t min_pulse_us;
  uint16_t max_pulse_us;
  uint16_t one_cycle_us;
};


}  // namespace omuct_can_util

#endif  // OCU_CAN_UTIL_H_
