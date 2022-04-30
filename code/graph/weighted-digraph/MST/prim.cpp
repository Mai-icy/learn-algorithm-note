#include "MST.hpp"

class PrimMST
{
public:
    PrimMST(WeightedGraph G);
    ~PrimMST() { delete[] marked, distTo; }
    Bag<Edge> edges() const { return mst; }
    double weight() const;

private:
    point_pq pq;
    bool *marked;
    double *distTo;
    Edge *edgeTo;
    Bag<Edge> mst;

    void visit(WeightedGraph G, int v);
};

PrimMST::PrimMST(WeightedGraph G) : marked(new bool[G.V()]), distTo(new double[G.V()])
{
}

void PrimMST::visit(WeightedGraph G, int v)
{
    marked[v] = true;
    for (Edge e : G.adj(v))
    {
        int w = e.other(v);
        if (marked[w])
            continue;
        if (e.weight() < distTo[w])
        {
            edgeTo[w] = e;

            distTo[w] = e.weight();
            ele new_ele(w, distTo[w]);
            pq_update(pq,  new_ele);
        }
    }
}

void pq_update(point_pq &pq, const ele &new_data)
{
    point_pq temp;
    temp.swap(pq);
    while (!temp.empty())
    {
        ele top_edge = temp.top();
        temp.pop();
        if (new_data.first == top_edge.first)
        {
            pq.push(new_data);
            break;
        }
        else
            pq.push(top_edge);
    }
    while (!temp.empty())
    {
        ele top_edge = temp.top();
        temp.pop();
        pq.push(top_edge);
    }
}