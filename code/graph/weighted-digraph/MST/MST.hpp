#include "../../base/weighted-graph.hpp"
#include <queue>
#include <vector>
#include <functional>

typedef std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> edge_pq;

class MST
{
public:
    MST(WeightedGraph G);
    Bag<Edge> edges();
    double weight();

private:
    ;
};

typedef std::pair<int, double> ele;
class greater_point
{
    bool operator()(const ele &__x, const ele &__y) const { return __x > __y; }
};

typedef std::priority_queue<ele, std::vector<ele>, greater_point> point_pq;
