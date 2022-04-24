#ifndef EDGE_HPP
#define EDGE_HPP

#include <iostream>

class DirectedEdge
{
public:
    DirectedEdge() : v(0), w(0), weight_(0){};
    DirectedEdge(int v, int w, double wei) : v(v), w(w), weight_(wei){};

    double weight() const { return weight_; };
    int from() const { return v; };
    int to() const { return w; };

    friend std::ostream &operator<<(std::ostream &os, const DirectedEdge &edge);

private:
    int v;
    int w;
    double weight_;
};
std::ostream &operator<<(std::ostream &os, const DirectedEdge &edge)
{
    os << edge.from() << "->" << edge.to() << " w:" << edge.weight();
    return os;
}

#endif