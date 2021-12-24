#pragma once

#include <chrono>
#include <iostream>
#include <string>

namespace benchmark {
class timer final {

public:
  explicit timer(const char *aIdentifier) {
    identifier = aIdentifier;
    start_time = std::chrono::steady_clock::now();
  }
  ~timer() { print_time_consumed(); }

  inline void restart() { start_time = std::chrono::steady_clock::now(); }

  inline void print_time_consumed() const noexcept {
    std::cout << identifier << " took: [DURATION " << get_elapsed_ms() << "ms]"
              << std::endl;
  }

  inline double get_elapsed_ms() const noexcept {
    return get_elapsed_ns() / 1000000.0;
  }

  inline double get_elapsed_us() const noexcept {
    return get_elapsed_ns() / 1000.0;
  }

  double get_elapsed_ns() const noexcept {
    const std::chrono::duration<double, std::nano> elapsed =
        std::chrono::steady_clock::now() - start_time;
    return elapsed.count();
  }

private:
  std::string identifier;
  std::chrono::steady_clock::time_point start_time;
};
} // namespace benchmark