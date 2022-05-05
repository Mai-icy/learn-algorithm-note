#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <iostream>
#include <random>
#include <ctime>
#include "bag.hpp"

class WeightedDigraph
{
public:
    WeightedDigraph(int v);
    WeightedDigraph(const WeightedDigraph &G);
    ~WeightedDigraph() { delete[] _adj; }

    int V() { return vertex_num; };
    int E() { return edge_num; };

    void addEdge(int v, int w);
    Bag<int> adj(int v) { return _adj[v]; };

    WeightedDigraph reverse();

    WeightedDigraph &operator=(const WeightedDigraph &G);
    friend std::ostream &operator<<(std::ostream &os, const WeightedDigraph &G);

private:
    int vertex_num;
    int edge_num;
    Bag<int> *_adj;
};

WeightedDigraph::WeightedDigraph(int v) : vertex_num(v), edge_num(0), _adj(new Bag<int>[v]) {}

WeightedDigraph::WeightedDigraph(const WeightedDigraph &G)
{
    vertex_num = G.vertex_num;
    edge_num = G.edge_num;
    _adj = new Bag<int>[vertex_num];

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
    _adj = new Bag<int>[vertex_num];
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

inline void WeightedDigraph::addEdge(int v, int w)
{
    for (int temp : adj(v))
        if (temp == w)
            return;
    if (v == w)
        return;
    _adj[v].add(w); // 有向图只加一边
    edge_num++;
}

WeightedDigraph WeightedDigraph::reverse()
{
    WeightedDigraph reverse_digraph(vertex_num);
    for (int i = 0; i < vertex_num; i++)
        for (int v : _adj[i])
            reverse_digraph.addEdge(v, i);
    return reverse_digraph;
}

WeightedDigraph createRondomDigraph(int size)
{
    using namespace std;
    WeightedDigraph new_graph(size);

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
