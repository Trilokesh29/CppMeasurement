#include "ScopedMeasurement.h"
#include <chrono>
#include <iostream>

using namespace std::chrono;

struct CScopedMeasurement::Details {
  std::string identifier;
  steady_clock::time_point startTime;
};

CScopedMeasurement::CScopedMeasurement(const char *aIdentifier)
    : mDetails(std::make_unique<Details>()) {
  mDetails->identifier = aIdentifier;
  mDetails->startTime = steady_clock::now();
}

CScopedMeasurement::~CScopedMeasurement() { PrintTimeConsumed(); }

void CScopedMeasurement::PrintTimeConsumed() const {
  const auto duration = static_cast<unsigned int>(
      duration_cast<milliseconds>(steady_clock::now() - mDetails->startTime)
          .count());
  std::cout << mDetails->identifier << "took: [DURATION " << duration << "ms]"
            << std::endl;
}