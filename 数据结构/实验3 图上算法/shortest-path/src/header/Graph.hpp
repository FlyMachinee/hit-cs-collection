#ifndef _GRAPH_HPP_INCLUDED_
#define _GRAPH_HPP_INCLUDED_

#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <iostream>

namespace MyGraph {

    using label = ::std::string;
    using index = int;
    using size = size_t;
    using weight = int;
    enum { infinity = 0x3fffffff };

    template <class _adjIterator>
    class Graph {

    protected:
        size m_edgeCount = 0;

        // 用于方便地从编号获取对应标签
        ::std::vector<label> m_labelVector;

        // 用于快速地从查询标签对应编号
        ::std::map<label, index> m_labelMap;

    public:
        virtual void addVertex(label vertex_add) = 0;

        virtual void addEdge(index vertex_from, index vertex_to, weight w) = 0;

        virtual weight getEdgeWeight(index vertex_from, index vertex_to) const = 0;

        virtual void removeVertex(index vertex_index) = 0;

        virtual void removeEdge(index vertex_from, index vertex_to) = 0;

        bool isVertex(label vertex_label) const {
            return m_labelMap.count(vertex_label) != 0; 
        }

        index getIndex(label vertex_label) const {
            return isVertex(vertex_label) ? m_labelMap.at(vertex_label) : -1;
        }

        label getLabel(index vertex_idx) const {
            return (vertex_idx >= 0 && vertex_idx < m_labelVector.size()) ? m_labelVector[vertex_idx] : "";
        }

        void addEdge(label vertex_from, label vertex_to, weight w) {
            addEdge(getIndex(vertex_from), getIndex(vertex_to), w);
        }

        bool isEdge(index vertex_from, index vertex_to) const {
            return getEdgeWeight(vertex_from, vertex_to) != infinity;
        }

        bool isEdge(label vertex_from, label vertex_to) const {
            return getEdgeWeight(getIndex(vertex_from), getIndex(vertex_to)) != infinity;
        }

        size countVertex() const {
            return m_labelVector.size();
        }

        size countEdge() const {
            return m_edgeCount;
        }

        weight getEdgeWeight(label vertex_from, label vertex_to) const {
            return getEdgeWeight(getIndex(vertex_from), getIndex(vertex_to));
        }

        void removeVertex(label vertex_label) {
            removeVertex(getIndex(vertex_label));
        }

        void removeEdge(label label_from, label label_to) {
            removeEdge(getIndex(label_from), getIndex(label_to));
        }

        bool isEmpty() const {
            return m_labelVector.empty();
        }

        // 获取该图中以idx为编号的节点的 首邻接迭代器
        virtual _adjIterator beginAdjacentIterOf(index idx) = 0;

        // 获取该图中以idx为编号的节点的 尾邻接迭代器
        virtual _adjIterator endAdjacentIterOf(index idx) = 0;

        void commandSequence(::std::istream& command_src) {
            ::std::string command, label1, label2;
            weight w;

            while (command_src >> command, command_src.good()) {
                if (command == "+v") {
                    command_src >> label1;
                    addVertex(label1);
                }
                else if (command == "-v") {
                    command_src >> label1;
                    removeVertex(label1);
                }
                else if (command == "+e") {
                    command_src >> label1 >> label2 >> w;
                    addEdge(label1, label2, w);
                }
                else if (command == "-e") {
                    command_src >> label1 >> label2;
                    removeEdge(label1, label2);
                }
                else {
                    command_src.ignore(1024, '\n');
                }
            }
        }

    protected:
        
        bool _checkIndex(index idx) const {
            return idx >= 0 && idx < countVertex();
        }

        bool _checkIndexPair(index idx1, index idx2) const {
            return _checkIndex(idx1) && _checkIndex(idx2);
        }

        void _add_label_to_vec_and_map(label vertex_label) {
            m_labelVector.push_back(vertex_label);
            m_labelMap.emplace(vertex_label, countVertex() - 1);
        }

        void _del_label_from_vec_and_map(index vertex_index) {
            if (_checkIndex(vertex_index)) {
                auto iter = m_labelVector.begin() + vertex_index;
                m_labelMap.erase(*iter);
                iter = m_labelVector.erase(iter);

                for (; iter != m_labelVector.end(); ++iter) {
                    --m_labelMap.at(*iter);
                }
            }
        }

    public:

        void dfs(::std::ostream& out = ::std::cout) {
            int n = (int)countVertex();

            bool* vst = new bool[n](); // 判断节点是否被遍历
            int* forest = new int[n](); // 存储每个节点在遍历生成森林中的父节点
            int* idx = new int[n](); // 存储每个节点的深度优先编号
            int cnt = 0;

            out << "===================================" << ::std::endl;

            out << "深度优先序列: ";
            for (int i = 0; i < n; ++i) {
                if (!*(vst + i)) {
                    forest[i] = -1;
                    idx[i] = cnt++;
                    _dfs_rec(out, i, vst, forest, idx, cnt);
                }
            }
            out << ::std::endl;
            delete[] vst;

            out << "深度优先编号 及 深度优先生成森林信息:" << ::std::endl;

            out << "标签\t";
            for (const label& str: m_labelVector)
                out << str << '\t';
            out << ::std::endl;

            out << "编号\t";
            for (int i = 0; i < n; ++i)
                out << idx[i] << '\t';
            out << ::std::endl;
            delete[] idx;

            out << "父节点\t";
            for (int i = 0; i < n; ++i) {
                if (forest[i] == -1)
                    out << "null";
                else
                    out << getLabel(forest[i]);
                out << '\t';
            }
            out << ::std::endl << "===================================";

            delete[] forest;
        }

        void dfs_no_rec(::std::ostream& out = ::std::cout) {
            int n = (int)countVertex();

            bool* vst = new bool[n](); // 判断节点是否被遍历
            int* forest = new int[n](); // 存储每个节点在遍历生成森林中的父节点
            int* idx = new int[n](); // 存储每个节点的深度优先编号
            int cnt = 0;

            ::std::stack<index> st;

            out << "===================================" << ::std::endl;
            out << "深度优先序列(非递归): ";
            for (int i = 0; i < n; ++i) {
                if (!*(vst + i)) {
                    st.push(i);
                    vst[i] = true;

                    forest[i] = -1;
                    idx[i] = cnt++;
                    out << getLabel(i) << ' ';

                    while (!st.empty())
                    {
                        index u = st.top();

                        bool find_flag = false;
                        for (auto iter = beginAdjacentIterOf(u); iter != endAdjacentIterOf(u); ++iter) {
                            index v = (*iter).first;
                            if (!vst[v]) {
                                find_flag = true;
                                st.push(v);

                                vst[v] = true;
                                forest[v] = u;
                                idx[v] = cnt++;
                                out << getLabel(v) << ' ';
                                break;
                            }
                        }
                        if (!find_flag)
                            st.pop();
                    }
                }
            }
            out << ::std::endl;
            delete[] vst;

            out << "深度优先编号 及 深度优先生成森林信息:" << ::std::endl;

            out << "标签:\t";
            for (const label& str : m_labelVector)
                out << str << '\t';
            out << ::std::endl;

            out << "编号:\t";
            for (int i = 0; i < n; ++i)
                out << idx[i] << '\t';
            out << ::std::endl;
            delete[] idx;

            out << "父节点:\t";
            for (int i = 0; i < n; ++i) {
                if (forest[i] == -1)
                    out << "null";
                else
                    out << getLabel(forest[i]);
                out << '\t';
            }
            out << ::std::endl << "===================================";

            delete[] forest;
        }

        void bfs(::std::ostream& out = ::std::cout) {
            int n = (int)countVertex();

            bool* vst = new bool[n](); // 判断节点是否被遍历
            int* forest = new int[n](); // 存储每个节点在遍历生成森林中的父节点
            int* idx = new int[n](); // 存储每个节点的广度优先编号
            int cnt = 0;
            ::std::queue<index> queue;

            out << "===================================" << ::std::endl;
            out << "广度优先序列: ";
            for (int i = 0; i < n; ++i) {
                if (!*(vst + i)) {
                    queue.push(i);

                    vst[i] = true;
                    forest[i] = -1;
                    idx[i] = cnt++;

                    while (!queue.empty())
                    {
                        index u = queue.front();
                        queue.pop();
                        out << getLabel(u) << ' ';

                        for (auto iter = beginAdjacentIterOf(u); iter != endAdjacentIterOf(u); ++iter) {
                            index v = (*iter).first;
                            if (!vst[v]) {
                                queue.push(v);

                                vst[v] = true;
                                forest[v] = u;
                                idx[v] = cnt++;
                            }
                        }
                    }
                }
            }
            out << ::std::endl;
            delete[] vst;

            out << "广度优先编号 及 深度优先生成森林信息:" << ::std::endl;

            out << "标签:\t";
            for (const label& str : m_labelVector)
                out << str << '\t';
            out << ::std::endl;

            out << "编号:\t";
            for (int i = 0; i < n; ++i)
                out << idx[i] << '\t';
            out << ::std::endl;
            delete[] idx;

            out << "父节点:\t";
            for (int i = 0; i < n; ++i) {
                if (forest[i] == -1)
                    out << "null";
                else
                    out << getLabel(forest[i]);
                out << '\t';
            }
            out << ::std::endl << "===================================";

            delete[] forest;
        }

    private:

        void _dfs_rec(::std::ostream& out, index u, bool* vst, int* forest, int* idx, int& cnt) {
            vst[u] = true;
            out << getLabel(u) << ' ';
            for (auto iter = beginAdjacentIterOf(u); iter != endAdjacentIterOf(u); ++iter) {
                index v = (*iter).first;
                if (!vst[v]) {
                    forest[v] = u;
                    idx[v] = cnt++;
                    _dfs_rec(out, v, vst, forest, idx, cnt);
                }
            }
        }

    }; // class Graph

} // namespace MyGraph

#endif // _GRAPH_HPP_INCLUDED_