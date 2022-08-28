#include <OmuctCanUtil/CanManager.h>
#include <OmuctCanUtil/Px002.h>
#include <mbed.h>

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

  px002.setup(1, State::start);

  while(1) {
    can_manager.task();

    auto now = timer.elapsed_time();
    static auto pre = now;
    constexpr auto wait = chrono::milliseconds{200};
    if(now - pre > wait) {
      can_manager.who_am_i();
      px002.sol_write(0b1010);
      printf("send\n");
    }
  }
}
