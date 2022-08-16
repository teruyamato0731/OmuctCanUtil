#include <Arduino.h>
#include <OmuctCanUtil/CanManager.h>

using namespace omuct_can_util;

// Serial
BufferedSerial pc{USBTX, USBRX, 115200};

// Can
CanBus can{PB_12, PB_13, (int)1e6};
CanManager can_manager{can};

void setup() {
  printf("setup\n");

  can_manager.set_callback([](const CanMessage& msg) {
    printf("hoge\t%d\n", msg.id);
  });
}

void loop() {
  auto now = timer.elapsed_time();
  static auto pre = now;
  constexpr auto wait = chrono::seconds{1};
  if(now - pre > wait) {
    can_manager.who_am_i();
    printf("send\n");
  }

  can_manager.task();
}
