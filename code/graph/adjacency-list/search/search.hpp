#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "..\\base\\undirected-graph.hpp"

class Search
{
public:
    Search(Graph G, int s);
    bool marked(int v) { return _marked[v]; };
    int count() const { return _count; };
    ~Search() { delete[] _marked; }

private:
    void dfs(Graph G, int s);
    void bfs(Graph G, int s);

    bool *_marked = nullptr;
    int _count = 0;
    int root_node;
};


int main(){
    using namespace std;
    Graph test = createRondomGraph(10);

    cout << test << endl;

    Search tt(test, 0);

    cout << tt.count() << endl;
    cout << tt.marked(9) << endl;

}


#endif
