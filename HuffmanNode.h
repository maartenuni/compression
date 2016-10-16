
#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

#include<memory>
#include<vector>
#include "HuffmanStats.h"

class HuffmanNode;
typedef std::shared_ptr<HuffmanNode> HNodePtr;

class HuffmanNode {
public:

    HuffmanNode(const HuffPair& value);
    HuffmanNode(HNodePtr left, HNodePtr right);

    int64_t sum() const;
    double  frac() const;
    std::string repr()const;
    int64_t bits() const;
    int64_t length() const;

    void setStats(int bits, int length);

    std::vector<HNodePtr> bottomLeaves() const;

    bool hasChildren() const;

    const HNodePtr left()const;
    const HNodePtr right()const;

private:

    HNodePtr my_left;
    HNodePtr my_right;

    std::string my_represents;
    int64_t     my_sum;
    double      my_frac;
    int64_t     my_bits;
    int         my_length;
};

#endif
