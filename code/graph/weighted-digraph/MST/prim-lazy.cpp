#include "MST.hpp"

class LazyPrimMST
{
public:
    LazyPrimMST(WeightedGraph G);

private:
    edge_pq pq;
    bool *marked;
    Bag<Edge> mst;

    void visit(WeightedGraph G, int v)
    {
        marked[v] = true;
        for (const Edge &e : G.adj(v))
            if (!marked[e.other(v)])
                pq.push(e);
        
    }
};
