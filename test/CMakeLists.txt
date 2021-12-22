cmake_minimum_required(VERSION 3.10)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ../src ./test)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_executable(ScopedMeasurementTest main.cpp ScopedMeasurementTest.cpp ../src/ScopedMeasurement.cpp ../src/ScopedMeasurement.h)
target_link_libraries(ScopedMeasurementTest ${GTEST_LIBRARIES} pthread)