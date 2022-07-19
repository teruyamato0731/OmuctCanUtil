#include <mbed.h>
#include <OmuctCanUtil/FarmBase.h>

using namespace omuct_can_util;

BufferedSerial pc{USBTX, USBRX, 115200};
CanBus can{HOGE, FUGA};

struct Farm002 : FarmBase {
  constexpr uint16_t api_id = 0x002;
  Farm002(const CanBus& can, const uint16_t individual_id, const initializerlist<PinName> pins) : can_{can}, id_{api_id, individual_id} ,sol{pins}... {}
  
  void sol_write(const uint8_t state) {
    for(uint8_t i = 0; i < 8; ++i) {
      sols[i] = state & (1 << i);
    }
  }

  void task() {
    if(CanMessage msg; can.read(msg)) {

      if(msg.format == CANExtended) {
        const auto msg_id = CanId::make(msg.id);
        if(msg_id.include(id_)) {

        }
      } else if(msg.format == CANStandard && state_ == State::start) {
        if(msg.id == receave_position) {
          sol_write(data[0]);
        }
      }
    }
  }

 private:
  CanBus& can_;
  CanId id_;
  std::array<mbed::DigitalWrite, 8> sols;
};

Farm002 farm{can, 1};

int main() {
  farm.task();
}


































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































}