#ifndef OCU_PLUG_BASE_H_
#define OCU_PLUG_BASE_H_

#include "CanMessage.h"

namespace omuct_can_util {

struct PlugBase {
  virtual void task(CanBus& can, const CanMessage& msg) = 0;
  virtual void who_am_i() {}
  // virtual void hard_reset() = 0;
  // virtual void stop() = 0;
  // virtual void start() = 0;
  // virtual void set_recieve_id() = 0;
  // virtual void set_send_id() = 0;
  // virtual void call_api_specify_command() = 0;
};

}  // namespace omuct_can_util

#endif  // OCU_PLUG_BASE_H_
