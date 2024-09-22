#ifndef _HUFFMAN_DECODER_HPP_
#define _HUFFMAN_DECODER_HPP_

#include "./HuffmanTree.hpp"
#include <iostream>

namespace huffman_code
{
    class HuffmanDecoder
    {
    private:
        HuffmanTree tree;

        void create_tree(::std::istream& in, char placeholder);

        void _create(::std::istream& in, Node*& p, char placeholder);

    public:
        void decode_to_stream(::std::istream& huffman_stream_src, ::std::ostream& char_stream_dest);

        inline HuffmanTree& get_tree()
        {
            return tree;
        }
    };
}

#endif