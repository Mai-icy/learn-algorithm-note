#include "search.hpp"

Search::Search(Graph G, int s) : _marked(new bool[G.V()]{false}),  root_node(s)
{
    dfs(G, s);
}

void Search::dfs(Graph G, int s)
{
    _marked[s] = true;
    for (int v : G.adj(s))
    {
        if (!_marked[v])
        {
            dfs(G, v);
            _count++;
        }
    }
}

