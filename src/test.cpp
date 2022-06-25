#include <mbed.h>
// #include <OmuctCanUtil/CanManager.h>
// #include <OmuctCanUtil/Px002.h>

// using namespace omuct_can_util;

// Serial
// BufferedSerial pc{USBTX, USBRX, 115200};

// // Can
// CanBus can{PA_11, PA_12, (int)1e6};
// CanManager can_manager{can};

// // sol
// Px002 px002{can_manager, 0x01};

int main() {
  // printf("setup\n");
  while(1) {
    // printf("hoge\n");
  }
}
// int main() {
//   printf("setup\n");
//   can_manager.set_callback([](const CanMessage& msg) {
//     printf("hoge\t%d\n", msg.id);
//   });

//   can_manager.who_am_i();
//   px002.set_mosi_id(1);

//   while(1) {
//     printf("hoge\n");
//     can_manager.task();
//     px002.set_state(0b1010);
//   }
// }
