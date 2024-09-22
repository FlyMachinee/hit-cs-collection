#include "ShortestPathAlgorithm.h"

#include <vector>

void MyGraph::warshall(const AdjacencyMatrixGraph& G, ::std::ostream& out_dest) {
	using namespace std;

	size n = G.countVertex(); // 图的顶点数

	vector<vector<char>> reachable(n, vector<char>(n, 0)); // dist[u][v]: u到v的最短距离

	for (index i = 0; i < n; ++i)
		for (index j = 0; j < n; ++j) {
			if (i == j)
				reachable[i][j] = 1;
			else
				reachable[i][j] = G.getEdgeWeight(i, j) >= infinity ? 0 : 1;
		}

	for (index k = 0; k < n; ++k)
		for (index i = 0; i < n; ++i)
			for (index j = 0; j < n; ++j)
				reachable[i][j] |= reachable[i][k] & reachable[k][j];
				
	// *****结果展示*****

	out_dest << "可达矩阵:" << endl;
	for (index i = 0; i < n; ++i)
		out_dest << '\t' << G.getLabel(i);
	out_dest << endl;

	for (index i = 0; i < n; ++i) {
		out_dest << G.getLabel(i) << '\t';

		for (index j = 0; j < n; ++j)
			out_dest << reachable[i][j] + 0 << '\t';

		out_dest << endl;
	}
}