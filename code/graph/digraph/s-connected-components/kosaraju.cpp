#include "SCC.hpp"
#include "../topological-sort/topological.hpp"

SCC::SCC(WeightedDigraph G) : _id(new int[G.V()]), marked(new bool[G.V()])
{
    Topological ts(G.reverse());
    for (int s : ts.order())
    {
        if (!marked[s])
        {
            dfs(G, s);
            _count++;
        }
    }
}

void SCC::dfs(WeightedDigraph G, int v)
{
    marked[v] = true;
    _id[v] = _count;
    for (int w : G.adj(v))
        if (!marked[w])
            dfs(G, w);
}
