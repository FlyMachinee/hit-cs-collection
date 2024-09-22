#include "Graph.hpp"
#include "AdjacencyMatrixGraph.h"
#include <iostream>
#include <algorithm>

void MyGraph::AdjacencyMatrixGraph::extendMatrix() {
    const ::std::vector<weight> suffix(extendMatrixSize, infinity);

    size newSize = m_matrix.size() + extendMatrixSize;

    for (auto& vec: m_matrix) {
        vec.insert(vec.end(), suffix.begin(), suffix.end());
    }
    for (int i = 0; i < 5; ++i) {
        m_matrix.emplace_back(newSize, infinity);
    }
}

MyGraph::AdjacencyMatrixGraph::AdjacencyMatrixGraph() {
    for (int i = 0; i < initialMatrixSize; ++i) {
        m_matrix.emplace_back(20, infinity);
    }
}

void MyGraph::AdjacencyMatrixGraph::addVertex(label vertex_add) {
    if (countVertex() >= m_matrix.size()) {
        extendMatrix();
    }
    if (!isVertex(vertex_add)) {
        _add_label_to_vec_and_map(vertex_add);
    }
}

void MyGraph::AdjacencyMatrixGraph::addEdge(index vertex_from, index vertex_to, weight w) noexcept {
    if (_checkIndexPair(vertex_from, vertex_to)) {
        if (m_matrix[vertex_from][vertex_to] == infinity) {
            ++m_edgeCount;
            m_matrix[vertex_from][vertex_to] = w;
        }
    }
}

MyGraph::weight MyGraph::AdjacencyMatrixGraph::getEdgeWeight(index vertex_from, index vertex_to) const noexcept {
    if (_checkIndexPair(vertex_from, vertex_to))
        return m_matrix[vertex_from][vertex_to];
    else
        return infinity;
}

void MyGraph::AdjacencyMatrixGraph::removeVertex(index vertex_index) noexcept {
    if (_checkIndex(vertex_index)) {
        for (int j = 0; j < countVertex(); ++j)
            if (m_matrix[vertex_index][j] != infinity)
                removeEdge(vertex_index, j);

        for (int i = 0; i < countVertex(); ++i)
            if (m_matrix[i][vertex_index] != infinity)
                removeEdge(i, vertex_index);
                
        m_matrix.erase(m_matrix.begin() + vertex_index);
        for (auto& vec: m_matrix) {
            vec.erase(vec.begin() + vertex_index);
        }

        _del_label_from_vec_and_map(vertex_index);
    }
}

void MyGraph::AdjacencyMatrixGraph::removeEdge(index vertex_from, index vertex_to) noexcept {
    if (_checkIndexPair(vertex_from, vertex_to) && m_matrix[vertex_from][vertex_to] != infinity) {
        m_matrix[vertex_from][vertex_to] = infinity;
        --m_edgeCount;
    }
}

MyGraph::AdjacencyMatrixGraph::adjIterator MyGraph::AdjacencyMatrixGraph::beginAdjacentIterOf(index idx) {
    return adjIterator(*this, idx, false);
}

MyGraph::AdjacencyMatrixGraph::adjIterator MyGraph::AdjacencyMatrixGraph::endAdjacentIterOf(index idx) {
    return adjIterator(*this, idx, true);
}

void MyGraph::AdjacencyMatrixGraph::showMatrix(::std::ostream& out) const {
    const size n = countVertex();

    if (!n)
        out << "This graph is empty!" << ::std::endl;
    else {
        for (int i = 0; i < n; ++i)
            out << '\t' << getLabel(i);
        out << ::std::endl;

        for (int i = 0; i < n; ++i) {
            out << getLabel(i) << '\t';

            for (int j = 0; j < n; ++j) {
                if (m_matrix[i][j] == infinity)
                    out << "inf";
                else
                    out << m_matrix[i][j];

                out << '\t';
            }
            out << '\n';
        }
    }
}

MyGraph::matrixAdjIter::matrixAdjIter(AdjacencyMatrixGraph& _matrixGraph, index _idx, bool is_end)
    : m_matrixGraph(_matrixGraph), m_idx(_idx) {
    if (is_end) {
        it = m_matrixGraph.m_matrix[m_idx].cend();
    }
    else {
        it = ::std::find_if(
            m_matrixGraph.m_matrix[m_idx].cbegin(),
            m_matrixGraph.m_matrix[m_idx].cend(),
            [](weight w) { return w != infinity; }
        );
    }
}

MyGraph::matrixAdjIter& MyGraph::matrixAdjIter::operator++() {
    it = ::std::find_if(
        it + 1,
        m_matrixGraph.m_matrix[m_idx].cend(),
        [](weight w) { return w != infinity; }
    );
    return *this;
}

MyGraph::matrixAdjIter::pair MyGraph::matrixAdjIter::operator*() {
    return ::std::make_pair(it - m_matrixGraph.m_matrix[m_idx].cbegin(), *it);
}

bool MyGraph::matrixAdjIter::operator==(const matrixAdjIter& rhs) const {
    return ((&m_matrixGraph) == (&rhs.m_matrixGraph)) && (m_idx == rhs.m_idx) && (it == rhs.it);
}

bool MyGraph::matrixAdjIter::operator!=(const matrixAdjIter& rhs) const {
    return ((&m_matrixGraph) != (&rhs.m_matrixGraph)) || (m_idx != rhs.m_idx) || (it != rhs.it);
}
