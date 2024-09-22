#ifndef _BIT_MANIPULATOR_HPP_
#define _BIT_MANIPULATOR_HPP_

#include <iostream>

namespace bit_manipulate
{
    class BitManipulator
    {
    public:
        /**
         * @brief write a binary string to the stream
         * supplement some zeros in front of the binary string
         * if the string len is not divisible by 8
         * write the length of the supplement zero before writing the binary string
         * @param stream_dest the stream destination
         * @param bits_src the binary string source
        */
        void write_bits(::std::ostream& stream_dest, const ::std::string& bits_src);

        /**
         * @brief read binary string from the stream
         * the stream source must be written by "write_bits"
         * @param stream_src the stream source
         * @return the binary string
        */
        ::std::string read_bits(::std::istream& stream_src);

        /**
         * @brief convert a binary string byte to a char
         * i.e. a binary string with the length of 8
        */
        char byte_to_char(const ::std::string& bits_src, ::std::string::const_iterator& src_iter, int zero_supplement_len = 0);

        /**
         * @brief convert a char to a binary string byte
         * i.e. a binary string with the length of 8
        */
        ::std::string char_to_byte(char char_src, int zero_supplement_len = 0);
    };
}

#endif