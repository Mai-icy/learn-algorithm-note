#ifndef PATH_HPP
#define PATH_HPP

#include "..\\base\\digraph.hpp"

class Path
{
public:
    Path(WeightedDigraph G, int s);
    ~Path() { delete[] _marked; }

    Bag<int> pathTo(int v);
    bool hasPathTo(int v) { return _marked[v]; };
    bool marked(int v) { return _marked[v]; };
    int count() const { return _count; };

private:
    void dfs(WeightedDigraph G, int s);
    void bfs(WeightedDigraph G, int s);

    bool *_marked = nullptr;
    int *edgeTo = nullptr;
    int _count = 0;
    int root_node;
};

Bag<int> Path::pathTo(int v)
{
    if (!hasPathTo(v))
        return Bag<int>();
    Bag<int> path;
    for (int x = v; x != root_node; x = edgeTo[x])
    {
        path.add(x);
    }
    path.add(root_node);
    Bag<int> reserve(path);
    return reserve;
}

int main(){
    using namespace std;
    
    WeightedDigraph test = createRondomDigraph(10);
    Path test2(test, 0);
    cout << test<<endl;
    cout << test2.pathTo(9);
    
}

#endif
