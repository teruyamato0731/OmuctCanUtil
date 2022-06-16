#ifndef OCU_CAN_MESSAGE_H_
#define OCU_CAN_MESSAGE_H_

namespace omuct_can_util {

// TODO user define
#ifdef __MBED__
#include <mbed.h>
using CanMessage = mbed::CANMessage;
using CanFormat = ::CANFormat;
#else  // __MBED__
struct CANMessage {
  unsigned int   id;       // 29 bit identifier
  unsigned char  data[8];  // Data field
  unsigned char  len;      // Length of data field in bytes
  CANFormat      format;   // Format ::CANFormat
  CANType        type;     // Type ::CANType
};
enum CANFormat {
  CANStandard = 0,
  CANExtended = 1,
  CANAny = 2
};
enum CANType {
  CANData   = 0,
  CANRemote = 1
};
#endif  // __MBED__

}  // namespace omuct_can_util

#endif  // OCU_CAN_MESSAGE_H_
