#include "./BitManipulator.hpp"

/**
 * @brief write a binary string to the stream
 * supplement some zeros in front of the binary string
 * if the string len is not divisible by 8
 * write the length of the supplement zero before writing the binary string
 * @param stream_dest the stream destination
 * @param bits_src the binary string source
*/
void bit_manipulate::BitManipulator::write_bits(::std::ostream& stream_dest, const ::std::string& bits_src)
{
    // calc and write the length of zeros to be supplemented
    int zero_supplement_len = 8 - bits_src.size() % 8;
    stream_dest << (char)zero_supplement_len;

    // write the binary string
    auto iter = bits_src.cbegin();
    while (iter != bits_src.cend())
    {
        stream_dest << byte_to_char(bits_src, iter, zero_supplement_len);

        // if the zeros have been supplemented
        if (zero_supplement_len > 0)
            // no need to supplement zeros
            zero_supplement_len = 0;
    }
}

/**
 * @brief read binary string from the stream
 * the stream source must be written by "write_bits"
 * @param stream_src the stream source
 * @return the binary string
*/
::std::string bit_manipulate::BitManipulator::read_bits(::std::istream& stream_src)
{
    // buffer for return value
    ::std::string ret;
    
    // get the zeros supplemented
    char zero_supplement_len = stream_src.get();

    char ch;
    /// int cnt = 0;
    while (ch = stream_src.get(), !stream_src.eof())
    {
        // append binary strings to the return value
        // byte by byte
        ret += char_to_byte(ch, (int)zero_supplement_len);

        if (zero_supplement_len > '\0')
            zero_supplement_len = '\0';
        
        /// cnt++;
    }
    /// ::std::cout << cnt << ::std::endl;

    return ret;
    // return ::std::move(ret);
}

/**
 * @brief convert a binary string byte to a char
 * i.e. a binary string with the length of 8
*/
char bit_manipulate::BitManipulator::byte_to_char(const ::std::string& bits_src, ::std::string::const_iterator& src_iter, int zero_supplement_len)
{
    char ret = 0;
    for (int i = 0; i < 8 - zero_supplement_len; ++i, ++src_iter)
    {
        ret <<= 1;
        if (*src_iter == '1')
            ret |= 1;
    }
    return ret;
}

/**
 * @brief convert a char to a binary string byte
 * i.e. a binary string with the length of 8
*/
::std::string bit_manipulate::BitManipulator::char_to_byte(char char_src, int zero_supplement_len)
{
    ::std::string ret;
    for (int i = (1 << (7 - zero_supplement_len)); i > 0; i >>= 1)
    {
        if ((i & char_src) != 0)
            ret += '1';
        else
            ret += '0';
    }
    // return ::std::move(ret);
    return ret;
}