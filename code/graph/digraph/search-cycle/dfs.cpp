#include "cycle.hpp"

DirectedCycle::DirectedCycle(Digraph G) : marked(new bool[G.V()]), onStack(new bool[G.V()]), edgeTo(new int[G.V()])
{
    for (int i = 0; i < G.V(); i++)
    {
        if (!marked[i])
        {
            dfs(G, i);
        }
    }
}

void DirectedCycle::dfs(Digraph G, int s)
{
    onStack[s] = true;
    marked[s] = true;
    for (int v : G.adj(s))
    {
        if (hasCycle())
            return;
        else if (!marked[v])
        {
            edgeTo[v] = s;
            dfs(G, v);
        }
        else if (onStack[v])
        {
            Bag<int> cc;
            for (int x = s; x != v; x = edgeTo[x])
                cc.add(x);
            cc.add(v);
            cc.add(s);
            _cycle = cc;
        }
    }
    onStack[s] = false;
}
