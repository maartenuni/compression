

#include "BitWriter.h"
#include <cassert>

BitWriter::BitWriter()
    :
        my_bbuf(0),
        my_bpos(7)
{
}

void BitWriter::write(int64_t word, unsigned length)
{
    assert(length < 64);
    assert(my_bpos >= 0 && my_bpos < 8);
    int l(length);
    while (l >= 0) {
        if ((1 << l) & word)
            pushBit(1);
        else
            pushBit(0);
        l--;
    }
}

void BitWriter::pushBit(int i)
{
    if (i)
        my_bbuf |= (1 << my_bpos--);
    else
        my_bpos--;

    if (my_bpos < 0)
        pushByte();
}

void BitWriter::pushByte()
{
    my_bits.push_back(my_bbuf);
    my_bbuf = 0;
    my_bpos = 7;
}

std::ostream& operator<<(std::ostream& stream, const BitWriter& bits)
{
    stream.write((const char*)bits.my_bits.data(), bits.my_bits.size());
    if (bits.my_bpos < 7)
        stream.write((const char*)&(bits.my_bbuf), 1);

    return stream;
}
