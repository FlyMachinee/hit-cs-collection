#ifndef _HUFFMAN_TREE_HPP_
#define _HUFFMAN_TREE_HPP_

#include "./binary-tree/DynamicBinaryTree.hpp"
#include <iostream>
#include <map>

namespace huffman_code
{
    class HuffmanTreeNodeData
    {
    public:
        char ch;
        unsigned int weight;

        HuffmanTreeNodeData(): ch('\0'), weight(0){};

        HuffmanTreeNodeData(char _ch, unsigned int _weight): ch(_ch), weight(_weight){};

        friend ::std::ostream& operator<<(::std::ostream& out, const huffman_code::HuffmanTreeNodeData& data);

        friend ::std::istream& operator>>(::std::istream& in, huffman_code::HuffmanTreeNodeData& data);
    };

    // an alias
    using Node = BinaryTree::DynamicNode<HuffmanTreeNodeData>;

    class HuffmanTree: public BinaryTree::DynamicBinaryTree<HuffmanTreeNodeData>
    {
    public:
        void make_huffman_tree(::std::map<char, int>& freq_map);

        // a compare functor, which compares the weight in HuffmanTreeNodeData
        class greater
        {
        public:
            inline bool operator()(Node* p1, Node* p2)
            {
                return p1->data.weight > p2->data.weight;
            }
        };
    };
}

#endif