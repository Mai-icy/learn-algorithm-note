#ifndef BASE_GRAPH_HPP
#define BASE_GRAPH_HPP

#include <iostream>
#include <random>
#include <ctime>
#include "bag.hpp"

class Graph
{
public:
    Graph(int v);
    Graph(const Graph &G);
    ~Graph() { delete[] _adj; }

    int V() { return vertex_num; };
    int E() { return edge_num; };

    void addEdge(int v, int w);
    Bag<int> adj(int v);

    Graph &operator=(const Graph &G);
    friend std::ostream &operator<<(std::ostream &os, const Graph &G);

private:
    int vertex_num;
    int edge_num;
    Bag<int> *_adj;
};

Graph::Graph(const Graph &G)
{
    vertex_num = G.vertex_num;
    edge_num = G.edge_num;
    _adj = new Bag<int>[vertex_num];

    for (int v = 0; v < vertex_num; v++)
    {
        _adj[v] = G._adj[v];
    }
}

Graph &Graph::operator=(const Graph &G)
{
    if (this == &G)
    {
        return *this;
    }
    delete[] _adj;
    vertex_num = G.vertex_num;
    edge_num = G.edge_num;
    _adj = new Bag<int>[vertex_num];
    for (int v = 0; v < vertex_num; v++)
    {
        _adj[v] = G._adj[v];
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Graph &G)
{
    using namespace std;
    for (int i = 0; i < G.vertex_num; i++)
    {
        os << i << " ";
        os << G._adj[i] << endl;
    }
    return os;
}

Graph::Graph(int v) : vertex_num(v), edge_num(0), _adj(new Bag<int>[v]) {}

inline void Graph::addEdge(int v, int w)
{
    for (int temp : adj(v))
    {
        if (temp == w)
            return;
    }
    if (v == w)
    {
        return;
    }
    _adj[v].add(w);
    _adj[w].add(v);
    edge_num++;
}

Bag<int> Graph::adj(int v)
{
    return _adj[v];
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
