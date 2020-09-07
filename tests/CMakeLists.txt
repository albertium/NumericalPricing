add_executable(pricer_test header.h GeneralTests.cpp)
#add_executable(pricer_test header.h BinomialPricerTests.cpp)
add_test(NAME pricer_test COMMAND pricer_test)
target_link_libraries(pricer_test PUBLIC pricer_lib gtest gtest_main)