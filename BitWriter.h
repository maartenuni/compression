
#ifndef BIT_WRITER_H
#define BIT_WRITER_H

#include <cstdint>
#include <ostream>
#include <vector>

/**
 * Writes bits to internal buffer and subsequently write them
 * to am output stream.
 */
class BitWriter {

        friend std::ostream& operator<<(std::ostream&, const BitWriter&);
    public:

        BitWriter();

        /**
         * writes them bits in word to the buffer.
         * note caller must make sure length < 64.
         */
        void write(int64_t word, unsigned length);

    private:

        /**
         * Pushes my_bbuf to the end of my_bits and resets
         * my_bbuf and my_bpos.
         */
        void pushByte();

        /**
         * Writes a bit to my_bbuf when bit != 0.
         */
        void pushBit(int bit);

        int8_t                  my_bbuf;
        int8_t                  my_bpos;

        std::vector<uint8_t>    my_bits;
};

std::ostream& operator<<(std::ostream& stream, const BitWriter& bits);


#endif

