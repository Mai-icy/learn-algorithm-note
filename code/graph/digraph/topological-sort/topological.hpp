#ifndef TOPOLOGICAL_HPP
#define TOPOLOGICAL_HPP

#include "../../base/digraph.hpp"
#include "../search-cycle/cycle.hpp"

class Topological
{
public:
    Topological(Digraph G);
    ~Topological() { delete[] marked, onStack; }

    bool isDAG() const { return !resOrder.isEmpty(); };
    Bag<int> order() const { return resOrder; };

private:
    bool *marked;
    bool *onStack;
    Bag<int> resOrder;

    void dfs(Digraph G, int v);
};

Topological::Topological(Digraph G) : marked(new bool[G.V()]), onStack(new bool[G.V()])
{
    DirectedCycle dc(G);
    if (!dc.hasCycle())
    {
        dfs(G, 0);
    }
}
void Topological::dfs(Digraph G, int v)
{
    marked[v] = true;
    for (int w : G.adj(v))
    {
        if(!marked[w])
            dfs(G, w);
    }
    resOrder.add(v);
}

#endif