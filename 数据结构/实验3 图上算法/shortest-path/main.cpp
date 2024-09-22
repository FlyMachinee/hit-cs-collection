#include <iostream>
#include <fstream>

#include ".\src\header\MyGraph"
#include ".\src\ShortestPathAlgorithm"
using namespace MyGraph;
using namespace std;

int main()
{
    system("chcp 65001"); // set terminal to UTF-8 mode, for showing Chinese characters currectly
    ifstream command("./graph_2.txt");

    AdjacencyMatrixGraph G1;
    G1.commandSequence(command);

    dijkstra(G1, "A");

    return 0;
}