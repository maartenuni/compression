
#include "BitReader.h"

BitReader::BitReader(const std::vector<uint8_t>& input)
    :
        my_bytepos(0),
        my_bitpos(7),
        my_bits(input)
{
}

int BitReader::readBit() {
    if (my_bytepos >= my_bits.size())
        return -1;
    else
        return getBit();
}

int BitReader::getBit()
{
    int bit = my_bits[my_bytepos] & (1 << my_bitpos--);
    if (my_bitpos < 0)
        my_bytepos++, my_bitpos = 7;
    return bit ? 1 : 0;
}
