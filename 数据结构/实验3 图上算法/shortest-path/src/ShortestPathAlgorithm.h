#ifndef _SHORTEST_PATH_ALGORITHM_H_INCLUDED_
#define _SHORTEST_PATH_ALGORITHM_H_INCLUDED_

#include <iostream>
#include "./header/MyGraph"

namespace MyGraph {

	void dijkstra(const AdjacencyMatrixGraph& G, label label_from, ::std::ostream& out_dest = ::std::cout);

	void __dijkstra(const AdjacencyMatrixGraph& G, index u, ::std::vector<weight>& dist, ::std::vector<index>& pass);

	void __dijkstra_show_path(const AdjacencyMatrixGraph& G, index u, index v, ::std::vector<weight>& dist, ::std::vector<index>& pass, ::std::ostream& out_dest);

	void floyd(const AdjacencyMatrixGraph& G, ::std::ostream& out_dest = ::std::cout);

	void warshall(const AdjacencyMatrixGraph& G, ::std::ostream& out_dest = ::std::cout);

	void all_shortest_to(const AdjacencyMatrixGraph& G, label label_to, ::std::ostream& out_dest = ::std::cout);

	void shortest_pair(const AdjacencyMatrixGraph& G, label label_from, label label_to, ::std::ostream& out_dest = ::std::cout);

} // namespace MyGraph

#endif // _SHORTEST_PATH_ALGORITHM_H_INCLUDED_