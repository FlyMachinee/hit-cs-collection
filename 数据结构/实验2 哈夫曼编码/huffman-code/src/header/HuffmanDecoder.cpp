#include "./HuffmanDecoder.hpp"
#include "./BitManipulator.hpp"

void huffman_code::HuffmanDecoder::decode_to_stream(::std::istream& stream_src, ::std::ostream& char_stream_dest)
{
    create_tree(stream_src, (char)0b00001111);

    // ::std::cout << stream_src.peek() << ::std::endl;
    // ::std::cout << stream_src.eof() << ::std::endl;
    
    // tree.for_each(
    //     BinaryTree::PRE_ORDER,
    //     [&](HuffmanTreeNode e){::std::cout << e.ch;},
    //     [&](){::std::cout << (char)0b00001111;},
    //     tree.root()
    // );

    bit_manipulate::BitManipulator bit_manip;

    // ::std::string bits(::std::move(bit_manip.read_bits(stream_src)));
    ::std::string bits(bit_manip.read_bits(stream_src));

    // ::std::cout << bits.size() << ::std::endl;

    Node* p_node = tree.root();

    for (char bit: bits)
    {
        if (bit == '0')
        {
            p_node = p_node->lchild;
        }
        else
        // bit == '1'
        {
            p_node = p_node->rchild;
        }

        if (p_node->lchild == nullptr && p_node->rchild == nullptr)
        // reach a leaf node
        {
            char_stream_dest << p_node->data.ch;
            p_node = tree.root();
        }
    }
}

void huffman_code::HuffmanDecoder::create_tree(::std::istream& in, char placeholder)
{
    if (!tree.empty())
        tree.delete_tree(tree.root());

    _create(in, tree.root(), placeholder);
}

void huffman_code::HuffmanDecoder::_create(::std::istream& in, Node*& p, char placeholder)
{
    // prevent dead loop
    if (in.eof())
        return;

    if (in.peek() != placeholder)
    {
        char data = in.get();
        p = tree.new_node();

        p->data = HuffmanTreeNodeData(data, 0);
        _create(in, p->lchild, placeholder);
        _create(in, p->rchild, placeholder);
    }
    else
    {
        in.get();
        p = nullptr;
    }   
}