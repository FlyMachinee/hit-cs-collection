#include "./HuffmanTree.hpp"
#include <queue>
#include "HuffmanTree.hpp"

::std::ostream& operator<<(::std::ostream& out, const huffman_code::HuffmanTreeNodeData& data)
{
    // out.write(&(data.ch), 1);
    out << data.ch <<  ' ' << data.weight;
    return out;
} 

::std::istream& operator>>(::std::istream& in, huffman_code::HuffmanTreeNodeData& data)
{
    data.ch = in.get();
    in >> data.weight;
    return in;
}

void huffman_code::HuffmanTree::make_huffman_tree(::std::map<char, int>& freq_map)
{
    // a small root heap
    ::std::priority_queue<Node*, ::std::vector<Node*>, greater> heap;

    // create tree for every single term in freq_map
    for (auto key_val: freq_map)
    {
        Node* p = new_node();
        p->data.ch = key_val.first;
        p->data.weight = key_val.second;
        heap.push(p);
    }

    if (!empty())
        delete_tree(root());

    // create huffman tree
    while (heap.size() > 1)
    {
        // get two smallest tree
        // "smallest" means the data.weight are smallest
        Node* node_1 = heap.top();
        heap.pop();
        Node* node_2 = heap.top();
        heap.pop();

        // using the two to make a new tree
        Node* root = new_node();
        root->lchild = node_1;
        root->rchild = node_2;
        root->data = HuffmanTreeNodeData('\0', node_1->data.weight + node_2->data.weight);

        // push the new tree into the heap
        heap.push(root);
    }

    this->root() = heap.top();
}