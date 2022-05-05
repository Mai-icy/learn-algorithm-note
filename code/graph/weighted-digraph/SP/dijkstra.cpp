#include "SP.hpp"
#include <queue>
#include <vector>
#include <functional>

typedef std::pair<int, double> ele;
typedef std::priority_queue<ele, std::vector<ele>, std::greater<ele>> edge_pq;

class DijkstraSP
{
public:
    DijkstraSP(WeightedDigraph G, int s);
    ~DijkstraSP() { delete[] distTo_, edgeTo_; }

    double distTo(int v) const { return distTo_[v]; }
    bool hasPathTo(int v) const { return distTo_[v] < INFINITY; }
    Bag<DirectedEdge> pathTo(int v);

private:
    void relax(WeightedDigraph G, int v);
    double *distTo_;
    DirectedEdge *edgeTo_;
    edge_pq pq;
};

void DijkstraSP::relax(WeightedDigraph G, int v)
{
    for (DirectedEdge e : G.adj(v))
    {
        int w = e.to();
        if (distTo_[w] > distTo_[v] + e.weight())
        {
            distTo_[w] = distTo_[v] + e.weight();
            edgeTo_[w] = e;
            pq_update(pq, ele(w, distTo_[w]));
        }
    }
}

DijkstraSP::DijkstraSP(WeightedDigraph G, int s) : distTo_(new double[G.V()]), edgeTo_(new DirectedEdge[G.V()])
{
    for (int i = 0; i < G.V(); i++)
        distTo_[i] = INFINITY;
    distTo_[s] = 0;
    pq.push(ele(s, 0.0));
    while (!pq.empty())
    {
        relax(G, pq.top().first);
        pq.pop();
    }
}

Bag<DirectedEdge> DijkstraSP::pathTo(int v)
{
    Bag<DirectedEdge> res;
    if (!hasPathTo(v))
        return res;
    for (DirectedEdge e = edgeTo_[v]; e.from() != -1; e = edgeTo_[e.from()])
        res.add(e);
    return res;
}

void pq_update(edge_pq &pq, const ele &new_data)
{
    edge_pq temp;
    temp.swap(pq);
    bool has_new = false;
    while (!temp.empty())
    {
        ele top_ele = temp.top();
        temp.pop();
        if (top_ele.first == new_data.first)
        {
            pq.push(new_data);
            has_new = true;
        }
        else
            pq.push(top_ele);
    }
    if (has_new)
    {
        pq.push(new_data);
    }
}
