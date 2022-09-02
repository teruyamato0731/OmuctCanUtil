#include <OmuctCanUtil/CanManager.h>
#include <OmuctCanUtil/Fx002.h>
#include <mbed.h>

using namespace omuct_can_util;

// IO
// BufferedSerial pc{USBTX, USBRX, 115200};
CAN can{PA_11, PA_12, (int)1e6};

// Firm
Fx002 farm{can, 1, {D4, D5, D6, D7, D8, D9, D12, D11}};

int main() {
  farm.task();
}
