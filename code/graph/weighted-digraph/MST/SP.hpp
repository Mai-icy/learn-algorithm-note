#include "../base/weighted-digraph.hpp"

class SP
{
public:
    SP(WeightedDigraph G, int s);
    double distTo(int v) { return distTo_[v]; }
    bool hasPathTo(int v) { return distTo_[v] < INFINITY; }
    Bag<DirectedEdge> pathTo(int v);

private:
    int *distTo_;
    DirectedEdge *edgeTo_;
};

Bag<DirectedEdge> SP::pathTo(int v)
{
    Bag<DirectedEdge> res_bag;
    if (!hasPathTo(v))
        return res_bag;
    for (DirectedEdge e = edgeTo_[v]; e.from() != -1; e = edgeTo_[e.from()])
        res_bag.add(e);
    return res_bag;
}