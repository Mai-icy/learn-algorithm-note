#include "../../digraph/topological-sort/topological.hpp"
#include "SP.hpp"

class AcyclicSP
{
public:
    AcyclicSP(WeightedDigraph G, int s);
    ~AcyclicSP() { delete[] distTo_, edgeTo_; }
    double distTo(int v) const { return distTo_[v]; }
    bool hasPathTo(int v) const { return distTo_[v] < INFINITY; }
    Bag<DirectedEdge> pathTo(int v);

private:
    void relax(WeightedDigraph G, int v);

    double *distTo_;
    DirectedEdge *edgeTo_;
};
void AcyclicSP::relax(WeightedDigraph G, int v)
{
    for (DirectedEdge e : G.adj(v))
    {
        int w = e.to();
        if (distTo_[w] > distTo_[v] + e.weight())
        {
            distTo_[w] = distTo_[v] + e.weight();
            edgeTo_[w] = e;
        }
    }
}

AcyclicSP::AcyclicSP(WeightedDigraph G, int s) : distTo_(new double[G.V()]), edgeTo_(new DirectedEdge[G.V()])
{
    for (int i = 0; i < G.V(); i++)
        distTo_[i] = INFINITY;
    distTo_[s] = 0.0;
    Topological top(remove_weight(G));
    for (int v : top.order())
    {
        relax(G, v);
    }
}

Digraph remove_weight(const WeightedDigraph &G)
{
    Digraph res(G.V());
    for (DirectedEdge e:G.edges())
        res.addEdge(e.from(), e.to());
    return res;
}
