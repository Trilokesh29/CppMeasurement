#include "ScopedMeasurement.h"
#include <future>
#include <gtest/gtest.h>

TEST(ScopedMeasurementTest, AutomaticScopeComplete) {
  testing::internal::CaptureStdout();
  { benchmark::timer m("AutomaticScopeComplete"); }
  const std::string output = testing::internal::GetCapturedStdout();
  ASSERT_EQ(false, output.empty());
}

TEST(ScopedMeasurementTest, ManualScopeReduction) {
  testing::internal::CaptureStdout();
  auto m1 = std::make_unique<benchmark::timer>("ManualScopeReduction");
  m1.reset();
  const std::string output1 = testing::internal::GetCapturedStdout();
  ASSERT_EQ(false, output1.empty());

  testing::internal::CaptureStdout();
  auto m2 = std::make_unique<benchmark::timer>("ManualScopeReduction");
  const std::string output2 = testing::internal::GetCapturedStdout();

  ASSERT_EQ(true, output2.empty());
}

TEST(ScopedMeasurementTest, MeasureBeforeScopeCompletion) {
  testing::internal::CaptureStdout();
  benchmark::timer m("MeasureBeforeScopeCompletion");

  auto fu = std::async(std::launch::async, []() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
  });

  fu.get();
  m.print_time_consumed();
  const std::string output = testing::internal::GetCapturedStdout();
  ASSERT_EQ(false, output.empty());
}

TEST(ScopedMeasurementTest, TestMoveMeasurement) {

  testing::internal::CaptureStdout();

  benchmark::timer m("MoveMeasurement");

  std::this_thread::sleep_for(std::chrono::seconds(2));

  const auto func = [](auto &&measure) {
    auto fu = std::async(std::launch::async, []() {
      std::this_thread::sleep_for(std::chrono::seconds(3));
    });
    fu.get();
    measure.print_time_consumed();
    const std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(false, output.empty());
  };

  func(std::move(m));
}

TEST(ScopedMeasurementTest, TestNanoMsFunc) {
  benchmark::timer tm("NanoMsFunctionTest");
  std::this_thread::sleep_for(std::chrono::seconds(3));
  const double elapsed = tm.get_elapsed_ns();
  const auto expected_min =
      std::chrono::duration_cast<std::chrono::nanoseconds>(
          std::chrono::seconds(3));
  ASSERT_GT(elapsed, expected_min.count());
}
