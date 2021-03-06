#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include "base/basegraph.hpp"

class Digraph : public BaseUnweightedGraph

{
public:
    Digraph(int v) : BaseUnweightedGraph(v){};
    void addEdge(int v, int w);
    Digraph reverse();

    friend std::ostream &operator<<(std::ostream &os, const Digraph &G);
};

void Digraph::addEdge(int v, int w)
{
    for (int temp : adj(v))
        if (temp == w)
            return;
    if (v == w)
        return;
    _adj[v].add(w); // 有向图只加一边
    edge_num++;
}

Digraph Digraph::reverse()
{
    Digraph reverse_digraph(vertex_num);
    for (int i = 0; i < vertex_num; i++)
        for (int v : _adj[i])
            reverse_digraph.addEdge(v, i);
    return reverse_digraph;
}

inline std::ostream &operator<<(std::ostream &os, const Digraph &G)
{
    using namespace std;
    for (int i = 0; i < G.vertex_num; i++)
        os << i << " " << G._adj[i] << endl;
    return os;
}

Digraph createRondomDigraph(int size)
{
    using namespace std;
    Digraph new_graph(size);

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