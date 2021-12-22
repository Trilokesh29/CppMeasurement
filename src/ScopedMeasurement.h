#pragma once
#include <memory>
#include <string>

class CScopedMeasurement final {

public:
  explicit CScopedMeasurement(const char *aIdentifier);
  ~CScopedMeasurement();
  CScopedMeasurement(const CScopedMeasurement &) = delete;
  CScopedMeasurement &operator=(const CScopedMeasurement &) = delete;
  CScopedMeasurement(CScopedMeasurement &&);
  CScopedMeasurement &operator=(CScopedMeasurement &&);

  void PrintTimeConsumed() const;

private:
  struct Details;
  std::unique_ptr<Details> mDetails;
};