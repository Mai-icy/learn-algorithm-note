#include "../base/weighted-graph.hpp"
#include <queue>
#include <vector>
#include <functional>

typedef std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> edge_pq;

class MST
{
public:
    MST();
    Bag<DirectedEdge> edges();
    double weight();
private:
    ;
};
