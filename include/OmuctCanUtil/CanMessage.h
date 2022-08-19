#ifndef OCU_CAN_MESSAGE_H_
#define OCU_CAN_MESSAGE_H_

#ifdef __MBED__
#include <mbed.h>
namespace omuct_can_util {
using CanMessage = mbed::CANMessage;
using CanFormat = CANFormat;
}  // namespace omuct_can_util
#elif defined(ARDUINO)
namespace omuct_can_util {
enum CanFormat {
  CANStandard = 0,
  CANExtended = 1,
  CANAny = 2
};
enum CANType {
  CANData = 0,
  CANRemote = 1
};
struct CanMessage {
  constexpr CanMessage(unsigned int _id, const unsigned char *_data, unsigned char _len = 8, CANType _type = CANData,
                       CanFormat _format = CANStandard) noexcept {
    len = (_len > 8) ? 8 : _len;
    type = _type;
    format = _format;
    id = _id;
    memcpy(data, _data, len);
  }
  constexpr CanMessage(unsigned int _id, CanFormat _format = CANStandard) noexcept {
    len = 0;
    type = CANRemote;
    format = _format;
    id = _id;
    memset(data, 0, 8);
  }
  unsigned int id;        // 29 bit identifier
  unsigned char data[8];  // Data field
  unsigned char len;      // Length of data field in bytes
  CanFormat format;       // Format ::CanFormat
  CANType type;           // Type ::CANType
};
};  // namespace omuct_can_util
#else
#error unsupported framework
#endif

#endif  // OCU_CAN_MESSAGE_H_
