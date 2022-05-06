#include "cc.hpp"
#include <queue>

CC::CC(Graph G) : _id(new int[G.V()]), marked(new bool[G.V()]{false})
{
    for (int p = 0; p < G.V(); p++)
    {
        if (!marked[p])
        {
            bfs(G, p);
            _count++;
        }
    }
}

void CC::bfs(Graph G, int s)
{
    std::queue<int> que_marked;
    que_marked.push(s);
    while (!que_marked.empty())
    {
        int ele = que_marked.front();
        que_marked.pop();
        marked[ele] = true;
        _id[ele] = _count;
        for (int v : G.adj(ele))
        {
            if (!marked[v])
                que_marked.push(v);
        }
    }
}