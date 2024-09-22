#ifndef _ADJ_MATRIX_GRAPH_HPP_INCLUDED_
#define _ADJ_MATRIX_GRAPH_HPP_INCLUDED_

#include "Graph.hpp"
#include "AdjacencyListGraph.h"
#include <iostream>

namespace MyGraph {

    class matrixAdjIter;
    class AdjacencyListGraph;

    class AdjacencyMatrixGraph: public Graph<matrixAdjIter> {

        friend class matrixAdjIter;
        friend AdjacencyListGraph matrixToList(const AdjacencyMatrixGraph& G);
        friend AdjacencyMatrixGraph listToMatrix(const AdjacencyListGraph& G);

    public:
        using adjIterator = matrixAdjIter;

    private:
        using matrix = ::std::vector<::std::vector<weight>>;
        matrix m_matrix;

        static constexpr int initialMatrixSize = 20;
        static constexpr int extendMatrixSize = 5;

    private:
        void extendMatrix();

    public:
        AdjacencyMatrixGraph();

        virtual void addVertex(label vertex_add);

        virtual void addEdge(index vertex_from, index vertex_to, weight w) noexcept;

        virtual weight getEdgeWeight(index vertex_from, index vertex_to) const noexcept;

        virtual void removeVertex(index vertex_index) noexcept;

        virtual void removeEdge(index vertex_from, index vertex_to) noexcept;

        virtual adjIterator beginAdjacentIterOf(index idx);

        virtual adjIterator endAdjacentIterOf(index idx);

        void showMatrix(::std::ostream& out = ::std::cout) const;

    }; // class AdjacencyMatrixGraph

    class matrixAdjIter {

    public:
        using pair = ::std::pair<index, weight>;

    private:
        AdjacencyMatrixGraph& m_matrixGraph;
        index m_idx;

        using iter = ::std::vector<weight>::const_iterator;
        iter it;

    public:
        matrixAdjIter(AdjacencyMatrixGraph& _matrixGraph, index _idx, bool is_end);

        // 将该迭代器指向下一个邻接节点，若无则为空
        // 对空迭代器自增为未定义行为
        matrixAdjIter& operator++();

        // 获取该迭代器指向的 邻接节点信息对
        // 包括：邻接节点的编号，以及 由 [以m_idx为编号的节点 指向 邻接节点] 的弧 的 权重
        pair operator*();

        bool operator==(const matrixAdjIter& rhs) const;

        bool operator!=(const matrixAdjIter& rhs) const;

    }; // class matrixAdjIter

} // namespace MyGraph

#endif // _ADJ_MATRIX_GRAPH_HPP_INCLUDED_