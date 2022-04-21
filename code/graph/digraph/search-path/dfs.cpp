#include "path.hpp"

Path::Path(Digraph G, int s) : _marked(new bool[G.V()]{false}), edgeTo(new int[G.V()]), root_node(s)
{
    dfs(G, s);
}

void Path::dfs(Digraph G, int s)
{
    _marked[s] = true;
    for (int v : G.adj(s))
    {
        if (!_marked[v]){
            edgeTo[v] = s;
            _count++;
            dfs(G, v);
        }
    }
}