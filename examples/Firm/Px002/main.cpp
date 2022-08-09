#include <mbed.h>
#include <Firm002.h>

// IO
BufferedSerial pc{USBTX, USBRX, 115200};
CAN can{PA_11, PA_12, (int)1e6};

// Firm
Firm002 farm{can, 1};

// TODO set_callback

int main() {
  farm.task();
}
