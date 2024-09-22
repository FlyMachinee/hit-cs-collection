#include "ShortestPathAlgorithm.h"

#include <vector>
#include <queue>

void MyGraph::all_shortest_to(const AdjacencyMatrixGraph& G, label label_to, ::std::ostream& out_dest) {
	using namespace std;

	if (!G.isVertex(label_to)) {
		cout << "Invalid label" << endl;
		return;
	}

	size n = G.countVertex(); // 图的顶点数
	index v = G.getIndex(label_to); // 终点的编号u

	vector<weight> dist(n); // dist[v]: 节点u到节点v的最短路径
	vector<index> pass(n); // pass[v]: 从节点u到节点v的最短路径中，节点v的直接前驱

	AdjacencyMatrixGraph G_T; // 图G的转置

	// 求G的转置
	for (index i = 0; i < n; ++i)
		G_T.addVertex(G.getLabel(i));
	for (index i = 0; i < n; ++i)
		for (index j = 0; j < n; ++j)
			if (G.isEdge(i, j))
				G_T.addEdge(j, i, G.getEdgeWeight(i, j));

	__dijkstra(G_T, v, dist, pass);

	// *****结果展示*****
	for (index u = 0; u < n; ++u) {
		if (v == u)
			continue;

		out_dest << G.getLabel(u) << "->" << label_to << ":\t";
		if (dist.at(u) >= infinity) {
			out_dest << "inf" << endl;
			continue;
		}
		else
			out_dest << dist.at(u) << "\tPath: ";

		index i = u;
		while (i != v) {
			out_dest << G.getLabel(i) << "->";
			i = pass.at(i);
		}
		out_dest << label_to << endl;
	}
}