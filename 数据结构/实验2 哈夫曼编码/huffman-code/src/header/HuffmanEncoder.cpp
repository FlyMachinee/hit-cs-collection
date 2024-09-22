#include "./HuffmanEncoder.hpp"
#include "./BitManipulator.hpp"
#include <iomanip>

void huffman_code::HuffmanEncoder::get_freq(::std::istream& stream_src)
{
    freq_map.clear();

    char ch;
    while (ch = stream_src.get(), !stream_src.eof())
    {
        auto it = freq_map.find(ch);
        if (it != freq_map.end())
        {
            ++(it->second);
        }
        else
        {
            freq_map.insert(::std::make_pair(ch, 1));
        }
    }

    _calc_freq();
}

void huffman_code::HuffmanEncoder::make_code_map()
{
    tree.make_huffman_tree(freq_map);

    code_map.clear();

    _rec_make_code_map(tree.root(), "");
}

void huffman_code::HuffmanEncoder::encode_to_str(::std::istream& stream_src, ::std::string& bits_dest)
{
    char ch;
    while (ch = stream_src.get(), !stream_src.eof())
    {
        bits_dest += code_map[ch];
    }
}

void huffman_code::HuffmanEncoder::encode_to_stream(::std::istream& stream_src, ::std::ostream& code_dest)
{
    // get the encoded binary string
    ::std::string bits;
    encode_to_str(stream_src, bits);
    
    // save the tree structure
    tree.for_each(
        BinaryTree::PRE_ORDER,
        [&](HuffmanTreeNodeData e){code_dest << e.ch;},
        [&](){code_dest << (char)0b00001111;},
        tree.root()
    );

    // write binary string to stream
    bit_manipulate::BitManipulator bit_manip;
    bit_manip.write_bits(code_dest, bits);
}

void huffman_code::HuffmanEncoder::_rec_make_code_map(Node* p_node, ::std::string code)
{
    if (p_node != nullptr)
    {
        if (p_node->lchild == nullptr && p_node->rchild == nullptr)
        // if is a leaf node
        {
            // a recursion exit
            code_map.insert(::std::make_pair(p_node->data.ch, code));
        }
        else
        // is not a leaf node
        {
            _rec_make_code_map(p_node->lchild, code + '0');
            _rec_make_code_map(p_node->rchild, code + '1');
        }
    }
}

void huffman_code::HuffmanEncoder::_calc_freq()
{
    // calc total frequency
    size_t total = 0;
    for (auto& key_val: freq_map)
    {
        total += key_val.second;
    }

    r_freq_vec.clear();

    for (auto& key_val: freq_map)
    {
        r_freq_vec.push_back((double)(key_val.second) / total);
    }
}

double huffman_code::HuffmanEncoder::avg_code_len()
{
    double ret = 0;
    int i = 0;
    for (auto& key_val: code_map)
    {
        ret += r_freq_vec.at(i++) * key_val.second.size();
    }
    
    return ret;
}

void huffman_code::HuffmanEncoder::show_freq_map(::std::ostream& out)
{
    out << "char | frequency  | relative freq" << ::std::endl;
    int i = 0;
    for (auto key_val: freq_map)
    {
        if (key_val.first == '\r')
            out << "\\r   | ";
        else if (key_val.first == '\n')
            out << "\\n   | ";
        else if (key_val.first == '\t')
            out << "\\t   | ";
        else if (key_val.first == ' ')
            out << "space| ";
        else if (!::std::isprint(key_val.first))
            out << ::std::setw(5) << ::std::left << (int)(key_val.first) << "| ";
        else
            out << key_val.first << "    | ";

        out << ::std::setw(10) << ::std::left << key_val.second
            << " | " 
            << ::std::fixed << ::std::setprecision(4)
            << r_freq_vec.at(i++) * 100
            << '%'
            << ::std::endl;
    }    
}

void huffman_code::HuffmanEncoder::show_code_map(::std::ostream& out)
{
    out << "char | code" << ::std::endl;
    for (auto key_val: code_map)
    {
        if (key_val.first == '\r')
            out << "\\r   | ";
        else if (key_val.first == '\n')
            out << "\\n   | ";
        else if (key_val.first == '\t')
            out << "\\t   | ";
        else if (key_val.first == ' ')
            out << "space| ";
        else if (!::std::isprint(key_val.first))
            out << ::std::setw(5) << ::std::left << (int)(key_val.first) << "| ";
        else
            out << key_val.first << "    | ";

        out << key_val.second << ::std::endl;
    }    
}