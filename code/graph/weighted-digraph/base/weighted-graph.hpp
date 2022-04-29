#ifndef WEIGHTED_DIGRAPH_HPP
#define WEIGHTED_DIGRAPH_HPP

#include "bag.hpp"
#include <iostream>
#include <random>
#include <ctime>
#include "edge.hpp"

class WeightedDigraph
{
public:
    WeightedDigraph(int v);
    WeightedDigraph(const WeightedDigraph &G);
    ~WeightedDigraph() { delete[] _adj; }

    int V() const { return vertex_num; };
    int E() const { return edge_num; };

    void addEdge(int v, int w, double weight);
    Bag<DirectedEdge> adj(int v) const  { return _adj[v]; };

    WeightedDigraph reverse() const;

    WeightedDigraph &operator=(const WeightedDigraph &G);
    friend std::ostream &operator<<(std::ostream &os, const WeightedDigraph &G);

private:
    int vertex_num;
    int edge_num;
    Bag<DirectedEdge> *_adj;
};

class WeightedGraph
{
public:
    WeightedGraph(int v);
    WeightedGraph(const WeightedGraph &G);
    ~WeightedGraph() { delete[] _adj; }

    int V() { return vertex_num; };
    int E() { return edge_num; };

    void addEdge(int v, int w, double weight);
    Bag<Edge> adj(int v) { return _adj[v]; };

    WeightedGraph &operator=(const WeightedGraph &G);
    friend std::ostream &operator<<(std::ostream &os, const WeightedGraph &G);

private:
    int vertex_num;
    int edge_num;
    Bag<Edge> *_adj;
};

WeightedDigraph::WeightedDigraph(int v) : vertex_num(v), edge_num(0), _adj(new Bag<DirectedEdge>[v]) {}

WeightedDigraph::WeightedDigraph(const WeightedDigraph &G)
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

WeightedDigraph WeightedDigraph::reverse()const
{
    WeightedDigraph reverse_digraph(vertex_num);
    for (int i = 0; i < vertex_num; i++)
        for (DirectedEdge v : _adj[i])
            reverse_digraph.addEdge(v.to(), v.from(), v.weight());
    return reverse_digraph;
}


WeightedGraph::WeightedGraph(int v) : vertex_num(v), edge_num(0), _adj(new Bag<Edge>[v]) {}

WeightedGraph::WeightedGraph(const WeightedGraph &G)
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


WeightedDigraph createRondomDigraph(int size)
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