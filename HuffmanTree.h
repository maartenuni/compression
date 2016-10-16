

#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H


#include <map>
#include <vector>
#include <memory>
#include "HuffmanStats.h"
#include "HuffmanNode.h"


class HuffmanTree {

public:

    HuffmanTree(const std::map<std::string, HuffVal>& values);
    HuffmanTree(const HuffmanStats& stats);

    std::vector<HNodePtr> codebook() const;

    const HNodePtr top() const;

    std::string decompress(const std::vector<uint8_t>& input);

private:

    void constructCodebook();

    HNodePtr my_tree;

    std::vector<HNodePtr>    my_codebook;
};

#endif
