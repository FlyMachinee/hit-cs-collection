#include "ShortestPathAlgorithm.h"

#include <vector>
#include <stack>
#include <queue>

void MyGraph::__dijkstra(const AdjacencyMatrixGraph& G, index u, ::std::vector<weight>& dist, ::std::vector<index>& pass) {
	using namespace std;

	// dist[v]: 节点u到节点v的最短路径长度
	// pass[v]: 从节点u到节点v的最短路径中，节点v的直接前驱

	size n = G.countVertex(); // 图的顶点数

	vector<char> done(n, 0); // done[u]: 节点是否被贪心选取

	using pair = pair<weight, index>;
	priority_queue<pair, vector<pair>, greater<pair>> heap; // 小根堆，对dijkstra算法的优化

	// ***** 初始化工作 *****
	for (index v = 0; v < n; ++v) {
		dist.at(v) = G.getEdgeWeight(u, v); // dist数组初始化为u至v的弧长
		pass.at(v) = u;
		heap.emplace(dist.at(v), v); // 将<权值，标号>数值对压入堆中，将自动将这些数值对按照weight优先，index其次进行排序
	}
	done.at(u) = 1; // 显然u已经完成计算

	while (!heap.empty()) {
		pair p = heap.top(); // 取出堆顶
		heap.pop();

		index v = p.second; // 当前未选取的节点中节点u到其距离最短的那个节点

		if (done.at(v)) // 如果已经被贪心选取
			continue; // 抛弃这个节点
		else {
			done.at(v) = 1;

			for (index w = 0; w < n; ++w) // 通过这个贪心选取的节点，去更新其他节点最短路径
				if (!done.at(w))
					if (dist.at(w) > dist.at(v) + G.getEdgeWeight(v, w)) {
						dist.at(w) = dist.at(v) + G.getEdgeWeight(v, w);
						heap.emplace(dist.at(w), w);
						pass.at(w) = v;
					}
		}
	}
}

void MyGraph::__dijkstra_show_path(const AdjacencyMatrixGraph& G, index u, index v, ::std::vector<weight>& dist, ::std::vector<index>& pass, ::std::ostream& out_dest) {
	using namespace std;

	static stack<index> st; // 栈，用于输出路径
	
	if (v == u)
		return;

	out_dest << G.getLabel(u) << "->" << G.getLabel(v) << ":\t";
	if (dist.at(v) >= infinity) {
		out_dest << "inf" << endl; // 不可达
		return;
	}
	else
		out_dest << dist.at(v) << "\tPath: "; // 可达，先输出路径长度，再输出路径

	index i = v;
	while (i != u) {
		st.push(i);
		i = pass.at(i);
	}

	out_dest << G.getLabel(u);
	while (!st.empty()) {
		out_dest << "->" << G.getLabel(st.top());
		st.pop();
	}

	out_dest << endl;
}

void MyGraph::dijkstra(const AdjacencyMatrixGraph& G, label label_from, ::std::ostream& out_dest) {
	using namespace std;

	if (!G.isVertex(label_from)) {
		cout << "Invalid label" << endl;
		return;
	}

	size n = G.countVertex(); // 图的顶点数
	index u = G.getIndex(label_from); // 起点的编号u
	
	vector<weight> dist(n); // dist[v]: 节点u到节点v的最短路径长度
	vector<index> pass(n); // pass[v]: 从节点u到节点v的最短路径中，节点v的直接前驱

	__dijkstra(G, u, dist, pass);

	// ***** 结果展示 *****
	stack<index> st; // 栈，用于输出路径

	for (index v = 0; v < n; ++v) // 对每个节点，输出节点u到其的最短路径
		__dijkstra_show_path(G, u, v, dist, pass, cout);
}