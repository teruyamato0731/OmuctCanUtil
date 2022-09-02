#include <OmuctCanUtil/CanManager.h>
#include <OmuctCanUtil/Fx400.h>
#include <mbed.h>

using namespace omuct_can_util;

// IO
// BufferedSerial pc{USBTX, USBRX, 115200};
CAN can{PA_11, PA_12, (int)1e6};

// Firm
std::array<Fx400, 4> farms{Fx400{can, 1, D4}, Fx400{can, 2, D5}, Fx400{can, 3, D6}, Fx400{can, 4, D7}};

int main() {
  for(auto& farm: farms) {
    farm.task();
  }
}
