#ifndef WEIGHT_GRAPH_HPP
#define WEIGHT_GRAPH_HPP

#include "base/basegraph.hpp"

class WeightedGraph : public BaseWeightedGraph
{
public:
    WeightedGraph(int v) : BaseWeightedGraph(v), _adj(new Bag<Edge>[v]){};
    WeightedGraph(const WeightedGraph &G);
    ~WeightedGraph() { delete[] _adj; }

    void addEdge(int v, int w, double weight);
    void addEdge(const Edge &e);
    Bag<Edge> adj(int v) const { return _adj[v]; };
    Bag<Edge> edges() const;

    WeightedGraph &operator=(const WeightedGraph &G);
    friend std::ostream &operator<<(std::ostream &os, const WeightedGraph &G);

private:
    Bag<Edge> *_adj;
};

Bag<Edge> WeightedGraph::edges() const
{
    Bag<Edge> res;
    for (int v = 0; v < vertex_num; v++)
        for (Edge e : _adj[v])
            if (e.other(v) > v)
                res.add(e);
    return res;
}

WeightedGraph::WeightedGraph(const WeightedGraph &G) : BaseWeightedGraph(G.V())
{
    vertex_num = G.vertex_num;
    edge_num = G.edge_num;
    _adj = new Bag<Edge>[vertex_num];

    for (int v = 0; v < vertex_num; v++)
        _adj[v] = G._adj[v];
}

WeightedGraph &WeightedGraph::operator=(const WeightedGraph &G)
{
    if (this == &G)
        return *this;

    delete[] _adj;
    vertex_num = G.vertex_num;
    edge_num = G.edge_num;
    _adj = new Bag<Edge>[vertex_num];
    for (int v = 0; v < vertex_num; v++)
        _adj[v] = G._adj[v];

    return *this;
}

inline std::ostream &operator<<(std::ostream &os, const WeightedGraph &G)
{
    using namespace std;
    for (int i = 0; i < G.vertex_num; i++)
        os << i << " " << G._adj[i] << endl;
    return os;
}

inline void WeightedGraph::addEdge(int v, int w, double weight)
{
    if (v == w)
        return;
    Edge edge(v, w, weight);
    _adj[v].add(edge);
    _adj[w].add(edge);
    edge_num++;
}

inline void WeightedGraph::addEdge(const Edge &e)
{
    int v = e.either(), w = e.other(v);
    _adj[w].add(e);
    _adj[v].add(e);
    edge_num++;
}

WeightedGraph createRondomGraph(int size)
{
    using namespace std;
    WeightedGraph new_graph(size);

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
