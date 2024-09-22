#include "Convertion.h"
#include "AdjacencyListGraph.h"
#include "AdjacencyMatrixGraph.h"

MyGraph::AdjacencyListGraph MyGraph::matrixToList(const AdjacencyMatrixGraph& G) {
    AdjacencyListGraph ret;
    ret.m_labelVector = G.m_labelVector;
    ret.m_labelMap = G.m_labelMap;
    ret.m_edgeCount = G.m_edgeCount;
    size n = G.m_labelVector.size();

    for (int i = 0; i < n; ++i) {
        ret.m_list.emplace_back(::std::vector<AdjacencyListGraph::pair>());

        for (int j = 0; j < n; ++j) {
            if (G.m_matrix[i][j] != infinity)
                ret.m_list[i].emplace_back(j, G.m_matrix[i][j]);
        }
    }
    return ret;
}

MyGraph::AdjacencyMatrixGraph MyGraph::listToMatrix(const AdjacencyListGraph& G) {
    AdjacencyMatrixGraph ret;
    ret.m_labelVector = G.m_labelVector;
    ret.m_labelMap = G.m_labelMap;
    ret.m_edgeCount = G.m_edgeCount;
    size n = G.m_labelVector.size();

    while (ret.m_matrix.size() < n)
        ret.extendMatrix();

    for (int i = 0; i < n; ++i) {
        for (const auto& p : G.m_list[i]) {
            ret.m_matrix[i][p.first] = p.second;
        }
    }

    return ret;
}