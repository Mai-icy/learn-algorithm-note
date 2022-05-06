#include "SCC.hpp"
#include "../topological-sort/topological.hpp"

SCC::SCC(Digraph G) : _id(new int[G.V()]), marked(new bool[G.V()])
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

void SCC::dfs(Digraph G, int v)
{
    marked[v] = true;
    _id[v] = _count;
    for (int w : G.adj(v))
        if (!marked[w])
            dfs(G, w);
}
