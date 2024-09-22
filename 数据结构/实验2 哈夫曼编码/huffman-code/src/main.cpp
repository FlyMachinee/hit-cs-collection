#include <iostream>
#include "./header/HuffmanCodec.hpp"

#include <cstring>

using namespace std;
using namespace huffman_code;

int main(int argc, const char *argv[])
{
    HuffmanCodec codec;

    if (argc > 2) 
    {
        if (strcmp(argv[1], "-e") == 0)
        {
            if (argc == 3)
                codec.encode(argv[2]);
            else
                codec.encode(argv[2], argv[3]);

            codec.show_freq_map(cout);
            cout << "==================================" << endl;
            codec.show_code_map(cout);
            cout << "Average code len: " << codec.avg_code_len() << endl; 
        }
        else
        {
            if (argc == 3)
                codec.decode(argv[2]);
            else
                codec.decode(argv[2], argv[3]);
        }
    }
    return 0;
}