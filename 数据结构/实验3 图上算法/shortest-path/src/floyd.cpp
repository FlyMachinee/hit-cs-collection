#include "ShortestPathAlgorithm.h"

#include <vector>

void __show_path(const ::MyGraph::AdjacencyMatrixGraph& G, ::std::vector<::std::vector<::MyGraph::index>>& pass, ::MyGraph::index u, ::MyGraph::index v) {
	using namespace std;
	using namespace MyGraph;

	index k = pass[u][v];

	if (k != -1) {
		__show_path(G, pass, u, k);
		cout << G.getLabel(k) << "->";
		__show_path(G, pass, k, v);
	}
}

void MyGraph::floyd(const AdjacencyMatrixGraph& G, ::std::ostream& out_dest) {
	using namespace std;

	size n = G.countVertex(); // 图的顶点数

	vector<vector<weight>> dist(n, vector<weight>(n, 0)); // dist[u][v]: u到v的最短距离
	vector<vector<index>> pass(n, vector<index>(n, -1)); // pass[u][v]: u到v的路径中包含的点, -1为没有包含

	for (index i = 0; i < n; ++i) // 初始化距离矩阵
		for (index j = 0; j < n; ++j) {
			if (i == j)
				dist[i][j] = 0;
			else
				dist[i][j] = G.getEdgeWeight(i, j);
		}

	// floyd算法核心
	for (index k = 0; k < n; ++k)
		for (index i = 0; i < n; ++i)
			for (index j = 0; j < n; ++j)
				if (dist[i][j] > dist[i][k] + dist[k][j] && dist[i][k] < infinity && dist[k][j] < infinity) { // 动态规划
					dist[i][j] = dist[i][k] + dist[k][j];
					pass[i][j] = k;
				}

	// ***** 结果展示 *****

	out_dest << "最短距离矩阵:" << endl;
	for (index i = 0; i < n; ++i)
		out_dest << '\t' << G.getLabel(i);
	out_dest << endl;

	for (index i = 0; i < n; ++i) {
		out_dest << G.getLabel(i) << '\t';

		for (index j = 0; j < n; ++j)
			if (dist[i][j] >= infinity)
				out_dest << "inf" << '\t';
			else
				out_dest << dist[i][j] << '\t';

		out_dest << endl;
	}
	out_dest << endl;

	out_dest << "最短路径矩阵:" << endl;
	for (index i = 0; i < n; ++i)
		out_dest << '\t' << G.getLabel(i);
	out_dest << endl;

	for (index i = 0; i < n; ++i) {
		out_dest << G.getLabel(i) << '\t';

		for (index j = 0; j < n; ++j)
			out_dest << G.getLabel(pass[i][j]) << '\t';

		out_dest << endl;
	}
	out_dest << endl;
	
	out_dest << "最短路径展示:" << endl;
	for (index i = 0; i < n; ++i) // 对任意两个不相同的节点，都输出二者之间的最短路径
		for (index j = 0; j < n; ++j) {
			if (i == j)
				continue;

			out_dest << G.getLabel(i) << "->" << G.getLabel(j) << ":\t";
			if (dist[i][j] >= infinity)
				out_dest << "inf" << endl; // 不可达
			else {
				out_dest << dist[i][j] << "\tPath: " << G.getLabel(i) << "->";
				__show_path(G, pass, i, j);
				out_dest << G.getLabel(j) << endl;
			}
		}
}