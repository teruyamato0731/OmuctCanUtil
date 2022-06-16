#ifndef OCU_PLUG_BASE_H_
#define OCU_PLUG_BASE_H_

// #include "CanId.h"
#include "CanMessage.h"

struct PlugBase {
  virtual CanMessage task(CanBus& can, const CanMessage& msg) = 0;
};

#endif  // OCU_PLUG_BASE_H_
