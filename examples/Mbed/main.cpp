#include <mbed.h>
#include <CanManager.h>
#include <plugin_sol_002.h>

CAN can{PA_11, PA_12, (int)1e6};
CanManeger<CAN>{can};

int main() {
  while(1) {

  }
}
