#include "ShortestPathAlgorithm.h"

#include <vector>

void MyGraph::shortest_pair(const AdjacencyMatrixGraph& G, label label_from, label label_to, ::std::ostream& out_dest) {
	using namespace std;

	if (!G.isVertex(label_from) || !G.isVertex(label_to) || label_from == label_to) {
		cout << "Invalid label" << endl;
		return;
	}

	size n = G.countVertex(); // 图的顶点数
	index u = G.getIndex(label_from), v = G.getIndex(label_to);

	vector<weight> dist_u_to(n), dist_v_to(n);
	vector<index> pass_u_to(n), pass_v_to(n);

	// 使用两次dijkstra算法，求出u到v的最短路径，以及v到u的最短路径
	__dijkstra(G, u, dist_u_to, pass_u_to);
	__dijkstra(G, v, dist_v_to, pass_v_to);

	// ***** 结果展示 *****

	// 输出u到v的路径
	__dijkstra_show_path(G, u, v, dist_u_to, pass_u_to, cout);
	
	// 输出v到u的路径
	__dijkstra_show_path(G, v, u, dist_v_to, pass_v_to, cout);
}