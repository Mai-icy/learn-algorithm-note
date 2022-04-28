#include "SP.hpp"

class DijkstraSP
{
public:
    DijkstraSP(WeightedDigraph G, int s);

private:
    void relax(WeightedDigraph G, int v);
    double *distTo;
    DirectedEdge *edgeTo;
};

void DijkstraSP::relax(WeightedDigraph G, int v)
{
    for (DirectedEdge e : G.adj(v))
    {int w = e.to();
    if(distTo[w] > distTo[v] + e.weight()){
        distTo[w] = distTo[v] + e.weight();
        edgeTo[w] = e;
        
    }
    }
}
