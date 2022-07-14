#ifndef STACK_CONTAINER_H_
#define STACK_CONTAINER_H_

namespace stack_container_ns {
namespace detail {
template<class...Args>
constexpr std::size_t sum(Args...args) {
  return (... + args);
}
}  // namespace detail

template<class... Args>
struct StackContainer {
  static constexpr std::size_t buf_size = sum(sizeof(std::declval<Args>())...);
  StackContainer(const Args...args) {
    push(buf_, args...);
  }
  auto get() -> uint8_t(&)[buf_size] {
    return buf_;
  }
 private:
  template<class Head, class...Args2>
  void push(void* p, Head head, Args2...args) {
    memcpy(p, &head, sizeof(Head));
    push(p, args...);
  }
  template<class Head>
  void push(void* p, Head head) {
    memcpy(p, &head, sizeof(Head));
  }
  uint8_t buf_[buf_size];
};

}

#endif  // STACK_CONTAINER_H_
