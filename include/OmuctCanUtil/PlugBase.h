#ifndef OCU_PLUG_BASE_H_
#define OCU_PLUG_BASE_H_

#include "CanMessage.h"
#include "CanUtil.h"

namespace omuct_can_util {

struct PlugBase {
  // virtual void who_am_i() = 0;
  // virtual void hard_reset() = 0;
  // virtual void stop() {
  //   state_ = State::stop;
  // }
  // virtual void start() {
  //   state_ = State::start;
  // }
  // virtual void set_recieve_id(const uint16_t id, const uint8_t byte) {};
  // virtual void set_send_id(const uint16_t id, const uint8_t byte) {};
  // virtual void call_api_specify_command() {};

 protected:
  // State state_ = State::stop;
};

}  // namespace omuct_can_util

#endif  // OCU_PLUG_BASE_H_
