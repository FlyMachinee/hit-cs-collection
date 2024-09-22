#include "Graph.hpp"
#include "AdjacencyListGraph.h"
#include <iostream>
#include <algorithm>
#include <iomanip>


void MyGraph::AdjacencyListGraph::addVertex(label vertex_add) {
    if (!isVertex(vertex_add)) {
        _add_label_to_vec_and_map(vertex_add);
        m_list.emplace_back(::std::vector<pair>());
    }
}

void MyGraph::AdjacencyListGraph::addEdge(index vertex_from, index vertex_to, weight w) {
    if (_checkIndexPair(vertex_from, vertex_to)) {
        if (getEdgeWeight(vertex_from, vertex_to) == infinity) {
            ++m_edgeCount;
            m_list[vertex_from].emplace_back(vertex_to, w);
        }
    }
}

MyGraph::weight MyGraph::AdjacencyListGraph::getEdgeWeight(index vertex_from, index vertex_to) const {
    if (_checkIndexPair(vertex_from, vertex_to)) {
        auto iter = ::std::find_if(
            m_list[vertex_from].cbegin(),
            m_list[vertex_from].cend(),
            [vertex_to](const pair& p) { return p.first == vertex_to; }
        );
        if (iter == m_list[vertex_from].cend())
            return infinity;
        else
            return (*iter).second;
    }
    else
        return infinity;
}

void MyGraph::AdjacencyListGraph::removeVertex(index vertex_index) {
    if (_checkIndex(vertex_index)) {
        m_list.erase(m_list.begin() + vertex_index);
                
        for (auto& line : m_list) {
            for (auto iter = line.begin(); iter != line.end();) {
                if ((*iter).first == vertex_index) {
                    iter = line.erase(iter);
                }
                else if ((*iter).first > vertex_index) {
                    --(*iter).first;
                    ++iter;
                }
                else
                    ++iter;
            }
        }

        _del_label_from_vec_and_map(vertex_index);
    }
}

void MyGraph::AdjacencyListGraph::removeEdge(index vertex_from, index vertex_to) {
    if (_checkIndexPair(vertex_from, vertex_to)) {
        auto iter = ::std::find_if(
            m_list[vertex_from].begin(),
            m_list[vertex_from].end(),
            [vertex_to](const pair& p) { return p.first == vertex_to; }
        );
        if (iter == m_list[vertex_from].end())
            return;
        else
            m_list[vertex_from].erase(iter);
    }
}

MyGraph::AdjacencyListGraph::adjIterator MyGraph::AdjacencyListGraph::beginAdjacentIterOf(index idx) {
    return adjIterator(*this, idx, false);
}

MyGraph::AdjacencyListGraph::adjIterator MyGraph::AdjacencyListGraph::endAdjacentIterOf(index idx) {
    return adjIterator(*this, idx, true);
}

void MyGraph::AdjacencyListGraph::showList(::std::ostream& out) const {
    const size n = countVertex();

    if (!n)
        out << "This graph is empty!" << ::std::endl;
    else
        for (int i = 0; i < n; ++i) {
            out << getLabel(i) << " -> ";

            for (const pair& p : m_list[i]) {
                out << "[" << getLabel(p.first) << "|";
                        
                if (p.second == infinity)
                    out << "inf";
                else
                    out << p.second;

                out << "] -> ";
            }

            out << "end" << ::std::endl;
        }
}

void MyGraph::AdjacencyListGraph::showDegree(::std::ostream& out) const
{
    int n = (int)countVertex();

    int* in_deg = new int[n]();
    int* out_deg = new int[n]();

    for (int i = 0; i < n; ++i) {
        for (const pair& p : m_list[i]) {
            ++out_deg[i];
            ++in_deg[p.first];
        }
    }
    
    out << "标签\t";
    for (const label& str : m_labelVector)
        out << str << '\t';
    out << ::std::endl;

    out << "入度\t";
    for (int i = 0; i < n; ++i)
        out << in_deg[i] << '\t';
    out << ::std::endl;

    out << "出度\t";
    for (int i = 0; i < n; ++i)
        out << out_deg[i] << '\t';
    out << ::std::endl;

    out << "度\t";
    for (int i = 0; i < n; ++i)
        out << in_deg[i] + out_deg[i] << '\t';
}

MyGraph::listAdjIter::listAdjIter(AdjacencyListGraph& _listGraph, index _idx, bool is_end)
    : m_listGraph(_listGraph), m_idx(_idx) {
    if (is_end) {
        it = m_listGraph.m_list[m_idx].cend();
    }
    else {
        it = m_listGraph.m_list[m_idx].cbegin();
    }
}

MyGraph::listAdjIter& MyGraph::listAdjIter::operator++() {
    ++it;
    return *this;
}

MyGraph::listAdjIter::pair MyGraph::listAdjIter::operator*() {
    return *it;
}

bool MyGraph::listAdjIter::operator==(const listAdjIter& rhs) const {
    return ((&m_listGraph) == (&rhs.m_listGraph)) && (m_idx == rhs.m_idx) && (it == rhs.it);
}

bool MyGraph::listAdjIter::operator!=(const listAdjIter& rhs) const {
    return ((&m_listGraph) != (&rhs.m_listGraph)) || (m_idx != rhs.m_idx) || (it != rhs.it);
}
