#ifndef OCU_PX002_H_
#define OCU_PX002_H_

#include "CanId.h"
#include "CanManager.h"
#include "CanMessage.h"
#include "CanUtil.h"
#include "PlugBase.h"

#include <optional>

namespace omuct_can_util {

struct Px002 : PlugBase {
  enum class SpecifyCommand : uint8_t {
    force_set_state = 1
  };

  constexpr Px002(CanManager& manager, const uint16_t individual_id) noexcept
      : manager_{manager}, id_{0x002, individual_id} {}

  void set_state(const uint8_t state) {
    if(pos_) {
      uint8_t data[] = {static_cast<uint8_t>(Command::call_api), static_cast<uint8_t>(SpecifyCommand::force_set_state), state};
      CANMessage msg{pos_.value().id, data, size(data)};
      manager_.send(msg);
    }
  }

  void set_mosi_id(const uint16_t id) {
    const MosiPosition pos = {id};
    pos_ = pos;

    uint8_t data[] = {static_cast<uint8_t>(Command::set_mosi_id), id >> 8u, id & 0xffu};
    CANMessage msg{id_.get_raw(), data, size(data)};
    manager_.send(msg);
  }

  void hard_reset() {
    uint8_t data[] = {static_cast<uint8_t>(Command::hard_reset)};
    CANMessage msg{id_.get_raw(), data, size(data)};
    manager_.send(msg);
  }

 private:
  CanManager& manager_;
  const CanId id_;
  std::optional<MosiPosition> pos_;
  uint8_t sol_state_ = 0;
};

}  // namespace omuct_can_util

#endif  // OCU_P002_H_
