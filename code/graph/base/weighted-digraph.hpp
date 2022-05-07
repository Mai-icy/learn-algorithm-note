#ifndef WEIGHT_DIGRAPH_HPP
#define WEIGHT_DIGRAPH_HPP

#include "base/basegraph.hpp"

class WeightedDigraph : public BaseWeightedGraph
{
public:
    WeightedDigraph(int v) : BaseWeightedGraph(v), _adj(new Bag<DirectedEdge>[v]){};
    WeightedDigraph(const WeightedDigraph &G);

    void addEdge(int v, int w, double weight);
    void addEdge(DirectedEdge e);
    Bag<DirectedEdge> adj(int v) const { return _adj[v]; };
    Bag<DirectedEdge> edges() const;

    WeightedDigraph reverse() const;

    WeightedDigraph &operator=(const WeightedDigraph &G);
    friend std::ostream &operator<<(std::ostream &os, const WeightedDigraph &G);

private:
    Bag<DirectedEdge> *_adj;
};

Bag<DirectedEdge> WeightedDigraph::edges() const
{
    Bag<DirectedEdge> res;
    for (int v = 0; v < vertex_num; v++)
        for (DirectedEdge e : _adj[v])
            res.add(e);
    return res;
}

WeightedDigraph::WeightedDigraph(const WeightedDigraph &G) : BaseWeightedGraph(G.V())
{
    vertex_num = G.vertex_num;
    edge_num = G.edge_num;
    _adj = new Bag<DirectedEdge>[vertex_num];

    for (int v = 0; v < vertex_num; v++)
        _adj[v] = G._adj[v];
}

WeightedDigraph &WeightedDigraph::operator=(const WeightedDigraph &G)
{
    if (this == &G)
        return *this;

    delete[] _adj;
    vertex_num = G.vertex_num;
    edge_num = G.edge_num;
    _adj = new Bag<DirectedEdge>[vertex_num];
    for (int v = 0; v < vertex_num; v++)
        _adj[v] = G._adj[v];

    return *this;
}

inline std::ostream &operator<<(std::ostream &os, const WeightedDigraph &G)
{
    using namespace std;
    for (int i = 0; i < G.vertex_num; i++)
        os << i << " " << G._adj[i] << endl;
    return os;
}

inline void WeightedDigraph::addEdge(int v, int w, double weight)
{
    if (v == w)
        return;
    DirectedEdge edge(v, w, weight);
    _adj[v].add(edge); // 有向图只加一边
    edge_num++;
}

inline void WeightedDigraph::addEdge(DirectedEdge e)
{
    _adj[e.from()].add(e);
    edge_num++;
}

WeightedDigraph WeightedDigraph::reverse() const
{
    WeightedDigraph reverse_digraph(vertex_num);
    for (int i = 0; i < vertex_num; i++)
        for (DirectedEdge v : _adj[i])
            reverse_digraph.addEdge(v.to(), v.from(), v.weight());
    return reverse_digraph;
}

WeightedDigraph createRondomWeightedDigraph(int size)
{
    using namespace std;
    WeightedDigraph new_graph(size);

    default_random_engine e(time(0));
    uniform_int_distribution<unsigned> u(0, size - 1);
    // uniform_real_distribution<double> ue(0.0, 5.0);
    uniform_int_distribution<unsigned> ue(101, 500);
    size_t max_edge_num = size * (size - 1) / 2;
    uniform_int_distribution<unsigned> edge_num_u(0, max_edge_num);

    int edge_num = edge_num_u(e);
    for (int i = 0; i < edge_num; i++)
    {
        int v = u(e);
        int w = u(e);
        double wt = ue(e);
        wt = wt / 100;
        new_graph.addEdge(w, v, wt);
    }
    return new_graph;
}
#endif
