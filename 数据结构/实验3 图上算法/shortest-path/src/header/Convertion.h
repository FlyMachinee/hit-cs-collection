#ifndef _CONVERTION_HPP_
#define _CONVERTION_HPP_

namespace MyGraph {

    class AdjacencyMatrixGraph;
    class AdjacencyListGraph;

    AdjacencyListGraph matrixToList(const AdjacencyMatrixGraph& G);

    AdjacencyMatrixGraph listToMatrix(const AdjacencyListGraph& G);

} // namespace MyGraph

#endif