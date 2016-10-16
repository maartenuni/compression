

#include "HuffmanNode.h"
#include <algorithm>

HuffmanNode::HuffmanNode(const HuffPair& value)
    :
        my_represents(value.first),
        my_sum(value.second.first),
        my_frac(value.second.second),
        my_bits(0),
        my_length(0)
{
}

HuffmanNode::HuffmanNode(HNodePtr left, HNodePtr right)
    :
        my_left(left),
        my_right(right),
        my_represents(left->repr() + right->repr()),
        my_sum(left->sum() + right->sum()),
        my_frac(left->frac() + right->frac()),
        my_bits(0),
        my_length(0)
{
}

int64_t HuffmanNode::sum() const
{
    return my_sum;
}

double HuffmanNode::frac() const
{
    return my_frac;
}

std::string HuffmanNode::repr() const
{
    return my_represents;
}

int64_t HuffmanNode::bits() const
{
    return my_bits;
}

int64_t HuffmanNode::length() const
{
    return my_length;
}

const HNodePtr HuffmanNode::left()const
{
    return my_left;
}

const HNodePtr HuffmanNode::right()const
{
    return my_right;
}

void HuffmanNode::setStats(int bits, int length)
{
    my_bits     = bits;
    my_length   = length;
    if (my_left)
        my_left->setStats((bits << 1) + 0, length + 1);
    if (my_right)
        my_right->setStats((bits << 1) + 1, length + 1);
}

std::vector<HNodePtr> HuffmanNode::bottomLeaves() const
{
    std::vector<HNodePtr> leaves;
    if(my_left) {
        if (!my_left->hasChildren())
            leaves.push_back(my_left);
        else {
            std::vector<HNodePtr> temp = my_left->bottomLeaves();
            leaves.insert(leaves.end(), temp.begin(), temp.end());
        }
    }
    if(my_right) {
        if (!my_right->hasChildren())
            leaves.push_back(my_right);
        else {
            std::vector<HNodePtr> temp = my_right->bottomLeaves();
            leaves.insert(leaves.end(), temp.begin(), temp.end());
        }
    }
    return leaves;
}

bool HuffmanNode::hasChildren() const
{
    return my_left != nullptr && my_right != nullptr;
}


