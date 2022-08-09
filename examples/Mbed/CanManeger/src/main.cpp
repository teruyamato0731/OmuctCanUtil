#include <mbed.h>
#include <OmuctCanUtil/CanManager.h>

using namespace omuct_can_util;

// Serial
BufferedSerial pc{USBTX, USBRX, 115200};

// Can
CanBus can{PB_12, PB_13, (int)1e6};
CanManager can_manager{can};

// sol
Px002 px002{can_manager, 0x01};

int main() {
  printf("setup\n");

  can_manager.set_callback([](const CanMessage& msg) {
    printf("hoge\t%d\n", msg.id);
  });


  while(1) {
    can_manager.who_am_i();
    printf("send\n");

    can_manager.task();

    ThisThread::sleep_for(500ms);
  }
}
