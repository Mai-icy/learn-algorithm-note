#include "search.hpp"

Search::Search(Graph G, int s) : root_node(s), _marked(new bool[G.V()]{false})
{
    dfs(G, s);
}

void Search::dfs(Graph G, int s)
{
    _marked[s] = true;
    for (int v : G.adj(s))
    {
        if (!_marked[s])
        {
            dfs(G, s);
            _count++;
        }
    }
}