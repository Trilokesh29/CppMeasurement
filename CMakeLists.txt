cmake_minimum_required(VERSION 3.10)
project(ScopedMeasurementTest)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ./ ./test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -ggdb -o0")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug) 


add_executable(ScopedMeasurementTest test/main.cpp test/ScopedMeasurementTest.cpp ScopedMeasurement.h)
target_link_libraries(ScopedMeasurementTest ${GTEST_LIBRARIES} pthread)