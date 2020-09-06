cmake_minimum_required(VERSION 3.17)
project(NumericalPricing)

set(CMAKE_CXX_STANDARD 14)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

include_directories(src)
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(lib/googletest)

add_executable(HW1 hw1.cpp)
target_link_libraries(HW1 pricer_lib)