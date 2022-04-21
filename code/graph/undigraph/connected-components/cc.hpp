#ifndef CC_HPP
#define CC_HPP

#include "../base/undirected-graph.hpp"

class CC
{
public:
    CC(Graph G);
    ~CC() {delete [] marked, _id;}

    bool connect(int v, int w);
    int count() {return _count;};
    int id(int v) {return _id[v];};

private:
    void dfs(Graph G, int s);
    void bfs(Graph G, int s);

    int _count = 0;
    int *_id;
    bool *marked;
};

int main(){
    using namespace std;
    Graph test = createRondomGraph(20);

    cout << test << endl;

    CC tt(test);

    cout << "共有连通分量"<< tt.count() << "个."<< endl;
}


#endif