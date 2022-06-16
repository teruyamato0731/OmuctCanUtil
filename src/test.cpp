#include <mbed.h>
#include <OmuctCanUtil/CanManager.h>
#include <OmuctCanUtil/Px002.h>

using namespace omuct_can_util;

CanBus can{PA_11, PA_12, (int)1e6};
Px002 px002{0x01};
CanManager can_manager{can, px002};

int main() {
  while(1) {
    px002.set_state();
    can_manager.task();
    // can_manager.who_am_i();
  }
}
