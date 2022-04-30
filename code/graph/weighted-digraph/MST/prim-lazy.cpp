#include "MST.hpp"

class LazyPrimMST
{
public:
    LazyPrimMST(WeightedGraph G);
    ~LazyPrimMST() { delete[] marked; }
    Bag<Edge> edges() const { return mst; }
    double weight() const;

private:
    edge_pq pq;
    bool *marked;
    Bag<Edge> mst;

    void visit(WeightedGraph G, int v);
};

LazyPrimMST::LazyPrimMST(WeightedGraph G) : marked(new bool[G.V()])
{
    visit(G, 0);
    while (!pq.empty())
    {
        Edge e = pq.top();
        pq.pop();
        int v = e.either(), w = e.other(v);
        if (marked[v] && marked[w])
            continue;
        mst.add(e);
        if (!marked[v])
            visit(G, v);
        if (!marked[w])
            visit(G, w);
    }
}

void LazyPrimMST::visit(WeightedGraph G, int v)
{
    marked[v] = true;
    for (Edge e : G.adj(v))
        if (!marked[e.other(v)])
            pq.push(e);
}
