#include "path.hpp"
#include <queue>

Path::Path(Graph G, int s) : _marked(new bool[G.V()]{false}), edgeTo(new int[G.V()]),root_node(s)
{
    bfs(G, s);
}

void Path::bfs(Graph G, int s)
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
            if (!_marked[w])
            {
                edgeTo[w] = v;
                _marked[w] = true;
                que_marked.push(w);
                _count++;
            }
        }
    }
}