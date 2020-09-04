cmake_minimum_required(VERSION 3.17)
project(NumericalPricing)

set(CMAKE_CXX_STANDARD 14)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(HW1
        hw1.cpp
        src/base.h src/common.h src/analytical.h src/analytical.cpp
        src/BinomialPricer.h src/BinomialPricer.cpp src/AnalyticalPricer.cpp src/AnalyticalPricer.h src/numerical.h src/numerical.cpp)

target_link_libraries(HW1 Eigen3::Eigen)