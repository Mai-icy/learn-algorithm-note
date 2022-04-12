#include "search.hpp"
#include <queue>

Search::Search(Graph G, int s) : root_node(s), _marked(new bool[G.V()]{false})
{
    bfs(G, s);
}

void Search::bfs(Graph G, int s)
{
    std::queue<int> que_marked;
    _marked[s] = true;
    que_marked.push(s);
    while (!que_marked.empty())
    {
        int v = que_marked.front();
        que_marked.pop();
        for (int w : G.adj(v))
        {
            _marked[w] = true;
            que_marked.push(w);
        }
    }
}