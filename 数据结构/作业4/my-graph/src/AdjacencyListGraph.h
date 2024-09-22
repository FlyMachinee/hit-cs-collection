#ifndef _ADJ_LIST_GRAPH_HPP_INCLUDED_
#define _ADJ_LIST_GRAPH_HPP_INCLUDED_

#include "Graph.hpp"
#include "AdjacencyMatrixGraph.h"
#include <iostream>

namespace MyGraph {

    class listAdjIter;
    class AdjacencyMatrixGraph;

    class AdjacencyListGraph: public Graph<listAdjIter> {

        friend class listAdjIter;
        friend AdjacencyListGraph matrixToList(const AdjacencyMatrixGraph& G);
        friend AdjacencyMatrixGraph listToMatrix(const AdjacencyListGraph& G);

    public:
        using adjIterator = listAdjIter;

    private:
        using pair = ::std::pair<index, weight>;
        using list = ::std::vector<::std::vector<pair>>;
        list m_list;

    public:
        virtual void addVertex(label vertex_add);

        virtual void addEdge(index vertex_from, index vertex_to, weight w);

        virtual weight getEdgeWeight(index vertex_from, index vertex_to) const;

        virtual void removeVertex(index vertex_index);

        virtual void removeEdge(index vertex_from, index vertex_to);

        virtual adjIterator beginAdjacentIterOf(index idx);

        virtual adjIterator endAdjacentIterOf(index idx);

        void showList(::std::ostream& out = ::std::cout) const;

        void showDegree(::std::ostream& out = ::std::cout) const;

    }; // class AdjacencyListGraph

    class listAdjIter {

    public:
        using pair = ::std::pair<index, weight>;

    private:
        AdjacencyListGraph& m_listGraph;
        index m_idx;

        using iter = ::std::vector<pair>::const_iterator;
        iter it;

    public:
        listAdjIter(AdjacencyListGraph& _listGraph, index _idx, bool is_end);

        // 将该迭代器指向下一个邻接节点，若无则为空
        // 对空迭代器自增为未定义行为
        listAdjIter& operator++();

        // 获取该迭代器指向的 邻接节点信息对
        // 包括：邻接节点的编号，以及 由 [以m_idx为编号的节点 指向 邻接节点] 的弧 的 权重
        pair operator*();

        bool operator==(const listAdjIter& rhs) const;

        bool operator!=(const listAdjIter& rhs) const;

    }; // class listAdjIter
    
} // namespace MyGraph

#endif // _ADJ_LIST_GRAPH_HPP_INCLUDED_