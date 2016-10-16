
#include "HuffmanTree.h"
#include "BitReader.h"
#include <algorithm>
#include <cassert>

HuffmanTree::HuffmanTree(const std::map<std::string, HuffVal>& values)
{
    std::vector<HNodePtr> nodes;
    for (const auto& pair: values)
        nodes.push_back(std::make_shared<HuffmanNode>(pair));

    auto greater = [](HNodePtr n1, HNodePtr n2) {
        return n1->sum() > n2->sum();
    };

    while(nodes.size() > 1) {
        std::sort(nodes.begin(), nodes.end(), greater);
        HNodePtr n = std::make_shared<HuffmanNode>(
                nodes[nodes.size() - 1],
                nodes[nodes.size() - 2]
                );
        nodes.resize(nodes.size()-1);
        nodes[nodes.size()-1] = n;
    }
    if (nodes.size() > 0) {
        assert(nodes.size() == 1);
        my_tree = nodes[0];
        constructCodebook();
    }
}

HuffmanTree::HuffmanTree(const HuffmanStats& stats)
    : HuffmanTree(stats.stats())
{
}

std::vector<HNodePtr> HuffmanTree::codebook() const
{
    return my_codebook;
}

const HNodePtr HuffmanTree::top() const
{
    return my_tree;
}

std::string HuffmanTree::decompress(const std::vector<uint8_t>& in)
{
    std::string out;
    BitReader reader(in);

    HNodePtr n = my_tree;
    assert(my_tree);
    while(1) {
        int bit = reader.readBit();
        if (bit < 0) break;

        if (bit) // turn right
            n = n->right();
        else
            n = n->left();

        if (!n->hasChildren()){
            out += n->repr();
            n = my_tree;
        }
    }
    return out;
}

void HuffmanTree::constructCodebook()
{
    my_codebook.clear();
    my_tree->setStats(0,0);
    std::vector<HNodePtr> codes = my_tree->bottomLeaves();
    for (const auto& leaf: codes) {
        my_codebook.push_back(leaf);
    }

    auto lesser = [](HNodePtr lhs, HNodePtr rhs) {
        return lhs->repr() < rhs->repr();
    };

    std::sort(my_codebook.begin(),
              my_codebook.end(),
              lesser
              );
}

