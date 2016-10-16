
#ifndef HUFFMAN_STATS_H
#define HUFFMAN_STATS_H

#include <stdint.h>
#include <map>
#include <iostream>
#include <string>

typedef std::pair<int, double> HuffVal;
typedef std::pair<std::string, HuffVal> HuffPair;

class HuffmanStats {

public:

    HuffmanStats(const std::string& input);

    void print();

    const std::map<std::string, HuffVal>& stats() const;

private:

    void compute_percentage();

    std::map<std::string, HuffVal>  my_cstats;  //character stats.
    int64_t                         my_sum;     // total character count
    double                          my_fracsum; // total of all fractions (1.0)
};

#endif
