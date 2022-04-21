#include "path.hpp"
#include <queue>

Path::Path(Digraph G, int s) : _marked(new bool[G.V()]{false}), edgeTo(new int[G.V()]), root_node(s)
{
    bfs(G, s);
}

void Path::bfs(Digraph G, int s)
{
    using namespace std;
    queue<int> b_que;
    _marked[s] = true;
    b_que.push(s);
    while (!b_que.empty())
    {
        int v = b_que.front();
        b_que.pop();
        for (int w : G.adj(v))
        {
            if (!_marked[w])
            {
                _marked[w] = true;
                edgeTo[w] = v;
                b_que.push(w);
                _count++;
            }
        }
    }
}
