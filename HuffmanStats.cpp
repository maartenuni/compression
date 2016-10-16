
#include "HuffmanStats.h"

HuffmanStats::HuffmanStats(const std::string& input)
    : my_sum(0), my_fracsum(0)
{

    for (const auto& ch:input) {
        std::string c(&ch, &ch+1);
        auto it = my_cstats.find(c);
        if (it == my_cstats.end())
            my_cstats[c] = HuffVal(1,0.0);
        else
            it->second.first++;
    }
    compute_percentage();
}

void HuffmanStats::print()
{
    for (auto& pair : my_cstats) {
        int c = pair.first[0];
        switch(c) {
        case '\n':
            std::cout << "'\\n'";
            break;
        case '\r':
            std::cout << "'\\r'";
            break;
        case '\t':
            std::cout << "'\\t'";
            break;
        default:
            std::cout << "'" << pair.first << "'";
        };

        std::cout << "\t" << pair.second.first
                  << "\t" << pair.second.second
                  << std::endl;

    }
    std::cout << "sum = " << my_sum << "\tsum of fractions = "
              << my_fracsum << std::endl;
}

const std::map<std::string, HuffVal>& HuffmanStats::stats()const
{
    return my_cstats;
}

void HuffmanStats::compute_percentage()
{
    for (auto& pair : my_cstats)
        my_sum += pair.second.first;
    for (auto& pair : my_cstats) {
        pair.second.second = double(pair.second.first) / my_sum;
        my_fracsum += pair.second.second;
    }
}


