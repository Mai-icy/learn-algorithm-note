#ifndef CYCLE_HPP
#define CYCLE_HPP
#include "../base/digraph.hpp"
#include <stack>

class DirectedCycle
{
public:
    DirectedCycle(Digraph G);
    ~DirectedCycle(){ delete [] onStack, edgeTo;}
    bool hasCycle() { return !_cycle.isEmpty(); };
    Bag<int> cycle() { return _cycle; };

private:
    void dfs(Digraph G, int s);

    Bag<int> _cycle;
    bool *marked;
    bool *onStack;
    int *edgeTo;
};

int main(){
    using namespace std;
    
    Digraph test = createRondomDigraph(10);
    DirectedCycle test2(test);
    cout << test<<endl;
    if (test2.hasCycle())
    {
        cout << test2.cycle();
    }
    
}
#endif
