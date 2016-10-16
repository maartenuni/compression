#ifndef BIT_READER_H
#define BIT_READER_H

#include <cstdint>
#include <ostream>
#include <vector>

/**
 * read bits from internal buffer and subsequently write them
 * to am output stream.
 */
class BitReader {

        friend std::istream& operator>>(std::istream&, const BitReader&);
    public:

        BitReader(const std::vector<uint8_t>& in);

        /**
         * pops one bit from the buffer
         *
         * \return 1 for a bit, 0 for a 0 and -1 when 
         * there are no more bits to read.
         */
        int readBit();

    private:

        int getBit();

        size_t                  my_bytepos;
        int8_t                  my_bitpos;

        std::vector<uint8_t>    my_bits;
};

std::ostream& operator<<(std::ostream& stream, const BitReader& bits);


#endif

