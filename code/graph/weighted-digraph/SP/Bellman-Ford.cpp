#include "SP.hpp"

class BellmanFordSP
{
public:
    BellmanFordSP(WeightedDigraph G, int s);
    ~BellmanFordSP() { delete[] onQ, distTo_, edgeTo_; }

    double distTo(int v) const { return distTo_[v]; }
    bool hasPathTo(int v) const { return distTo_[v] < INFINITY; }
    Bag<DirectedEdge> pathTo(int v);

private:
    void relax(WeightedDigraph G, int v);
    bool hasNegativeCycle();
    void findNegativeCycle();
    Bag<DirectedEdge> negativeCycle() { return cycle;};

    int size;
    int cost = 0;
    bool *onQ;
    double *distTo_;
    DirectedEdge *edgeTo_;
    std::queue<int> que;
    Bag<DirectedEdge> cycle;
};

BellmanFordSP::BellmanFordSP(WeightedDigraph G, int s) : size(G.V()), onQ(new bool[G.V()]), distTo_(new double[G.V()]), edgeTo_(new DirectedEdge[G.V()])
{
    for (int i = 0; i < G.V(); i++)
        distTo_[i] = INFINITY;
    distTo_[s] = 0.0;
    que.push(s);
    onQ[s] = true;
    while (!que.empty() and !this->hasNegativeCycle())
    {
        int v = que.front();
        que.pop();
        onQ[v] = false;
        relax(G, v);
    }
}

void BellmanFordSP::relax(WeightedDigraph G, int v)
{
    for (DirectedEdge e : G.adj(v))
    {
        int w = e.to();
        if (distTo_[w] > distTo_[v] + e.weight())
        {
            distTo_[w] = distTo_[v] + e.weight();
            edgeTo_[w] = e;
            if (!onQ[w])
            {
                que.push(w);
                onQ[w] = true;
            }
        }
        if (cost++ % G.V() == 0)
        {
            findNegativeCycle();
        }
    }
}
void BellmanFordSP::findNegativeCycle()
{
    WeightedDigraph spt(size);
    for (int v = 0; v < size; v++)
        if (edgeTo_[v].from() != -1)
            spt.addEdge(edgeTo_[v]);

    // 寻找有向环判断是否负权重
}

bool BellmanFordSP::hasNegativeCycle()
{
    return !cycle.isEmpty();
}

