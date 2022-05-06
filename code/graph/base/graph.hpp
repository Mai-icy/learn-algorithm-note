#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "base/basegraph.hpp"

class Graph : public BaseUnweightedGraph
{
public:
    Graph(int v) : BaseUnweightedGraph(v){};
    void addEdge(int v, int w);

    friend std::ostream &operator<<(std::ostream &os, const Graph &G);
};

void Graph::addEdge(int v, int w)
{
    for (int temp : adj(v))
        if (temp == w)
            return;
    if (v == w)
        return;
    _adj[v].add(w);
    _adj[w].add(v);
    edge_num++;
}

inline std::ostream &operator<<(std::ostream &os, const Graph &G)
{
    using namespace std;
    for (int i = 0; i < G.vertex_num; i++)
        os << i << " " << G._adj[i] << endl;
    return os;
}

Graph createRondomGraph(int size)
{
    using namespace std;
    Graph new_graph(size);

    default_random_engine e(time(0));
    uniform_int_distribution<unsigned> u(0, size - 1);
    size_t max_edge_num = size * (size - 1) / 2;
    uniform_int_distribution<unsigned> edge_num_u(0, max_edge_num);

    int edge_num = edge_num_u(e);
    for (int i = 0; i < edge_num; i++)
    {
        int v = u(e);
        int w = u(e);
        new_graph.addEdge(w, v);
    }
    return new_graph;
}
#endif