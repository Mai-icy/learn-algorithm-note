#ifndef SCC_HPP
#define SCC_HPP

#include "..\\base\\digraph.hpp"

class SCC
{
public:
    SCC(WeightedDigraph G);
    ~SCC() { delete[] _id, marked; }

    bool stronglyConnected(int v, int w) const { return _id[w] == _id[v]; };
    int count() const { return _count; };
    int id(int v) const { return _id[v]; };

private:
    void dfs(WeightedDigraph G, int s);

    int *_id;
    bool *marked;
    int _count = 0;
};

#endif