#include "cc.hpp"

CC::CC(Graph G) : _id(new int[G.V()]), marked(new bool[G.V()]{false})
{
    for (int p = 0; p < G.V(); p++)
    {
        if (!marked[p])
        {
            dfs(G, p);
            _count++;
        }
    }
}

void CC::dfs(Graph G, int v)
{
    marked[v] = true;
    _id[v] = _count;
    for (int p : G.adj(v))
    {
        if (!marked[p])
            dfs(G, p);
    }
}