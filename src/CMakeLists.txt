add_library(pricer_lib STATIC
        core.h base.h base.cpp common.h numerical.h numerical.cpp
        BinomialPricer.h BinomialPricer.cpp
        AnalyticalPricer.h AnalyticalPricer.cpp)

target_link_libraries(pricer_lib PUBLIC Eigen3::Eigen)