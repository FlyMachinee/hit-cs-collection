#include "HuffmanCodec.hpp"
#include <fstream>

/**
 * @brief encode file to huffman-code file
 * @param input_filename the file path to be encoded
 * @param output_huffman_filename the output huffman-code file path
*/
void huffman_code::HuffmanCodec::encode(::std::string input_filename, ::std::string output_huffman_filename)
{
    if (output_huffman_filename.empty())
        output_huffman_filename = input_filename + ".huffman";

    ::std::ifstream in(input_filename, ::std::ios::binary);
    ::std::ofstream out(output_huffman_filename, ::std::ios::binary);

    get_freq(in);
    make_code_map();

    in.clear();
    in.seekg(0, ::std::ios::beg);

    encode_to_stream(in, out);
    
    out.close();
    in.close();
}

/**
 * @brief decode huffman-code file to the original file
 * @param input_huffman_filename the huffman-code file path, must with the postfix ".huffman"
 * @param output_filename the output file path, default: input_huffman_filename - ".huffman"
*/
void huffman_code::HuffmanCodec::decode(::std::string input_huffman_filename, ::std::string output_filename)
{
    auto pos = input_huffman_filename.find(".huffman");
    if (pos == ::std::string::npos)
        throw ::std::range_error("file postfix is not .huffman");

    if (output_filename == "")
    {
        output_filename = input_huffman_filename;
        output_filename.erase(output_filename.begin() + pos, output_filename.end());
    }

    ::std::ifstream in(input_huffman_filename, ::std::ios::binary);
    ::std::ofstream out(output_filename, ::std::ios::binary);

    decode_to_stream(in, out);

    out.close();
    in.close();
}