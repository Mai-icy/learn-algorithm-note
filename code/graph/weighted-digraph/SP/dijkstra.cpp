#include "SP.hpp"
#include <queue>
#include <vector>
#include <functional>

typedef std::priority_queue<DirectedEdge, std::vector<DirectedEdge>, std::greater<DirectedEdge>> edge_pq;

class DijkstraSP
{
public:
    DijkstraSP(WeightedDigraph G, int s);

private:
    void relax(WeightedDigraph G, int v);
    double *distTo;
    DirectedEdge *edgeTo;
    edge_pq pq;
};

void DijkstraSP::relax(WeightedDigraph G, int v)
{
    for (DirectedEdge e : G.adj(v))
    {
        int w = e.to();
        if (distTo[w] > distTo[v] + e.weight())
        {
            distTo[w] = distTo[v] + e.weight();
            edgeTo[w] = e;
            if (contains(pq, e)){}
        }
    }
}

bool contains(edge_pq pq, DirectedEdge edge)
{
    while (!pq.empty())
    {
        DirectedEdge top = pq.top();
        if (edge == top)
            return true;
    }
    return false;
}

int main()
{
    return 0;
}