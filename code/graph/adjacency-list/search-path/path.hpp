#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "..\\base\\undirected-graph.hpp"

class Path
{
public:
    Path(Graph G, int s);
    ~Path() { delete[] _marked; }

    Bag<int> pathTo(int v);
    bool hasPathTo(int v) { return _marked[v]; };
    bool marked(int v) { return _marked[v]; };
    int count() const { return _count; };

private:
    void dfs(Graph G, int s);
    void bfs(Graph G, int s);

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
    
    Graph test = createRondomGraph(10);
    Path test2(test, 0);
    cout << test<<endl;
    cout << test2.pathTo(9);
    
}

#endif
