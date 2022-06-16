#include <mbed.h>
#include <CanManager.h>
#include <plugin_sol_002.h>

CAN can{PA_11, PA_12, (int)1e6};
CanManager<CAN>{can};

int main() {
  CanBus can{};
  Px001 px001{};
  CanManager hoge {can, px001};
  while(1) {
    hoge.task();
  }
}
