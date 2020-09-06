//
// Created by Albert Wong on 9/5/20.
//
#include "base.h"


namespace core {
    template<typename PayoffT, typename AdjustT, typename StepbackT, typename TagT>
    void Pricer<PayoffT, AdjustT, StepbackT, TagT>::profile(const std::vector<TagT> &tags, const std::string& name) {
        std::ofstream file{"../output/" + name + ".csv"};
        file << tags[0].header() << ",Price,Delta,Gamma,Theta" << std::endl;
        for (const TagT& tag : tags)
            file << price(tag) << std::endl;
    }
}