#ifndef _HUFFMAN_ENCODER_HPP_
#define _HUFFMAN_ENCODER_HPP_

#include "./HuffmanTree.hpp"
#include <iostream>
#include <map>
#include <vector>

namespace huffman_code
{
    class HuffmanEncoder
    {
    private:
        HuffmanTree tree;

        // a map from char to the char's frequency
        ::std::map<char, int> freq_map;

        // a map from char to the char's huffman-code
        ::std::map<char, ::std::string> code_map;

        // the vector relative frequency
        ::std::vector<double> r_freq_vec;

        // create code map by recursion
        void _rec_make_code_map(Node* p_node, ::std::string code);

        // calculate the relative frequency
        void _calc_freq();

    public:
        // calculate the frequency
        void get_freq(::std::istream& stream_src);

        // make code map by huffman tree
        void make_code_map();

        // encode the source stream to binary string
        void encode_to_str(::std::istream& stream_src, ::std::string& bits_dest);
        
        // encode the source stream to binary string, and output to a stream destination
        void encode_to_stream(::std::istream& stream_src, ::std::ostream& code_dest);
        
        void show_freq_map(::std::ostream& out);

        void show_code_map(::std::ostream& out);
        
        double avg_code_len();
    };
}

#endif