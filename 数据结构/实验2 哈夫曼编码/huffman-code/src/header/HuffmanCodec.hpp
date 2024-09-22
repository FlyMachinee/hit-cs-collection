#ifndef _HUFFMAN_CODEC_HPP_
#define _HUFFMAN_CODEC_HPP_

#include "HuffmanDecoder.hpp"
#include "HuffmanEncoder.hpp"

#include <iostream>

namespace huffman_code
{
    class HuffmanCodec: private HuffmanEncoder, private HuffmanDecoder
    {
    public:
    
        /**
         * @brief encode file to huffman-code file
         * @param input_filename the file path to be encoded
         * @param output_huffman_filename the output huffman-code file path, default: input_filename + ".huffman"
        */
        void encode(::std::string input_filename, ::std::string output_huffman_filename = "");

        /**
         * @brief decode huffman-code file to the original file
         * @param input_huffman_filename the huffman-code file path, must with the postfix ".huffman"
         * @param output_filename the output file path, default: input_huffman_filename - ".huffman"
        */
        void decode(::std::string input_huffman_filename, ::std::string output_filename = "");

        inline void show_freq_map(::std::ostream& out)
        {
            HuffmanEncoder::show_freq_map(out);
        }

        inline void show_code_map(::std::ostream& out)
        {
            HuffmanEncoder::show_code_map(out);
        }

        inline double avg_code_len()
        {
            return HuffmanEncoder::avg_code_len();
        }
    };
}

#endif