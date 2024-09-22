#include <iostream>
#include <fstream>

#include ".\src\MyGraph"
using namespace MyGraph;
using namespace std;

int main()
{
    system("chcp 65001"); // set terminal to UTF-8 mode, for showing Chinese characters currectly
    ifstream command("./graph_1.txt");

    AdjacencyListGraph G1;
    G1.commandSequence(command);

    /*
        do something here
    */

    // such as:
    G1.showList();
    cout << endl;

    return 0;
}