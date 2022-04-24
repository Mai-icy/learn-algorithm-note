#ifndef CYCLE_HPP
#define CYCLE_HPP
#include "../base/digraph.hpp"
#include <stack>

class DirectedCycle
{
public:
    DirectedCycle(WeightedDigraph G);
    ~DirectedCycle(){ delete [] onStack, edgeTo;}
    bool hasCycle() { return !_cycle.isEmpty(); };
    Bag<int> cycle() { return _cycle; };

private:
    void dfs(WeightedDigraph G, int s);

    Bag<int> _cycle;
    bool *marked;
    bool *onStack;
    int *edgeTo;
};

DirectedCycle::DirectedCycle(WeightedDigraph G) : marked(new bool[G.V()]), onStack(new bool[G.V()]), edgeTo(new int[G.V()])
{
    for (int i = 0; i < G.V(); i++)
    {
        if (!marked[i])
        {
            dfs(G, i);
        }
    }
}

void DirectedCycle::dfs(WeightedDigraph G, int s)
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
// int main(){
//     using namespace std;
    
//     Digraph test = createRondomDigraph(10);
//     DirectedCycle test2(test);
//     cout << test<<endl;
//     if (test2.hasCycle())
//     {
//         cout << test2.cycle();
//     }
    
// }
#endif
