#include <OmuctCanUtil/CanManager.h>
#include <OmuctCanUtil/Px400.h>
#include <mbed.h>

using namespace omuct_can_util;

// Serial
BufferedSerial pc{USBTX, USBRX, 115200};

// Can
CanBus can{PB_12, PB_13, (int)1e6};
CanManager can_manager{can};

// servo
Px400 px400{can_manager, 0x01};
constexpr ServoPulseConfig config = {(int)0.5e3, (int)2.4e3, (int)20e3};

Timer timer;

int main() {
  printf("setup\n");
  timer.start();

  can_manager.set_callback([](const CanMessage& msg) {
    printf("hoge\t%d\n", msg.id);
  });

  while(1) {
    can_manager.task();

    auto now = timer.elapsed_time();
    static auto pre = now;
    constexpr auto wait = chrono::milliseconds{200};
    if(now - pre > wait) {
      static int i = 0;
      ++i;
      if(i == 1) {
        px400.servo_write(0.0);
      } else if(i == 2) {
        px400.servo_write(1.0);
      } else if(i == 3) {
        px400.force_write(0.75);
      } else {
        px400.force_write(0.25);
        i = 0;
      }
      printf("send\n");
    }
  }
}
