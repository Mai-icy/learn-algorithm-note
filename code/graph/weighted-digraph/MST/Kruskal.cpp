#include "MST.hpp"
#include "../../union-find/base/uf.hpp"

class KurskaiMST
{
public:
    KurskaiMST(WeightedGraph G);
    Bag<Edge> edges() const { return mst; }
    double weight() const;

private:
    Bag<Edge> mst;
};

KurskaiMST::KurskaiMST(WeightedGraph G)
{
    edge_pq pq;
    for (Edge e : G.edges())
        pq.push(e);

    UF uf(G.V());
    while (!pq.empty() and mst.size() < G.V() - 1)
    {
        Edge e = pq.top();
        pq.pop();
        int v = e.either(), w = e.other(v);
        if (uf.connected(w, v))
            continue;
        uf.connect(w, v);
        mst.add(e);
    }
}

double KurskaiMST::weight() const
{
    double total = 0.0;
    for (Edge e : mst)
    {
        total += e.weight();
    }
    return total;
}
