#include "ScopedMeasurement.h"
#include <future>
#include <gtest/gtest.h>

TEST(ScopedMeasurementTest, AutomaticScopeComplete) {
  testing::internal::CaptureStdout();
  { CScopedMeasurement m("AutomaticScopeComplete"); }
  const std::string output = testing::internal::GetCapturedStdout();
  ASSERT_EQ(false, output.empty());
}

TEST(ScopedMeasurementTest, ManualScopeReduction) {
  testing::internal::CaptureStdout();
  auto m1 = std::make_unique<CScopedMeasurement>("ManualScopeReduction");
  m1.reset();
  const std::string output1 = testing::internal::GetCapturedStdout();
  ASSERT_EQ(false, output1.empty());

  testing::internal::CaptureStdout();
  auto m2 = std::make_unique<CScopedMeasurement>("ManualScopeReduction");
  const std::string output2 = testing::internal::GetCapturedStdout();

  ASSERT_EQ(true, output2.empty());
}

TEST(ScopedMeasurementTest, MeasureBeforeScopeCompletion) {
  testing::internal::CaptureStdout();
  CScopedMeasurement m("MeasureBeforeScopeCompletion");

  auto fu = std::async(std::launch::async, []() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
  });

  fu.get();
  m.PrintTimeConsumed();
  const std::string output = testing::internal::GetCapturedStdout();
  ASSERT_EQ(false, output.empty());
}