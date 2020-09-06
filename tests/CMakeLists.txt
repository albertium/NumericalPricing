add_executable(pricer_test BinomialPricerTests.cpp)
add_test(NAME pricer_test COMMAND pricer_test)
target_link_libraries(pricer_test PUBLIC pricer_lib gtest gtest_main)