#ifndef CAN_MANEGAR_H_
#define CAN_MANEGAR_H_


CANMessage

template<class T>
class CanManeger {
  using can_type = T;
  CanManeger(T can) : can_{can};
  CanManeger(const CanManeger&) = delete;
  CanManeger(CanManeger&&) = delete;

  read() [

  ]

  void write(const CANMessage msg) {

  }

 private:
  can_type can_;
}

#endif  // CAN_MANEGAR_H_
