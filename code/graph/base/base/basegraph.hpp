#ifndef BASEGRAPH_HPP
#define BASEGRAPH_HPP
 
#include "bag.hpp"
#include "edge.hpp"
#include <random>
#include <ctime>

class BaseGraph
{
public:
    BaseGraph(int v) : vertex_num(v){};
    int V() const { return vertex_num; };
    int E() const { return edge_num; };

protected:
    int vertex_num;
    int edge_num = 0;
};

class BaseUnweightedGraph : public BaseGraph
{
public:
    BaseUnweightedGraph(int v) : BaseGraph(v), _adj(new Bag<int>[v]) {}
    BaseUnweightedGraph(const BaseUnweightedGraph &G);
    ~BaseUnweightedGraph() { delete[] _adj; }

    virtual void addEdge(int v, int w) = 0;
    Bag<int> adj(int v) const { return _adj[v]; };

    BaseUnweightedGraph &operator=(const BaseUnweightedGraph &G);

protected:
    Bag<int> *_adj;
};

class BaseWeightedGraph : public BaseGraph
{
public:
    BaseWeightedGraph(int v) : BaseGraph(v) {}
    virtual void addEdge(int v, int w, double weight) = 0;
};

BaseUnweightedGraph::BaseUnweightedGraph(const BaseUnweightedGraph &G) : BaseGraph(G.vertex_num), _adj(new Bag<int>[G.vertex_num])
{
    vertex_num = G.vertex_num;
    edge_num = G.edge_num;
    for (int v = 0; v < vertex_num; v++)
        _adj[v] = G._adj[v];
}

BaseUnweightedGraph &BaseUnweightedGraph::operator=(const BaseUnweightedGraph &G)
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

#endif