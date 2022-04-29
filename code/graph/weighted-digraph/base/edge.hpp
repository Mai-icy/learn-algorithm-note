#ifndef EDGE_HPP
#define EDGE_HPP

#include <iostream>

class BaseEdge
{
public:
    BaseEdge() : v(-1), w(-1), weight_(0){};
    BaseEdge(int v, int w, double wei) : v(v), w(w), weight_(wei){};
    double weight() const { return weight_; };
    bool operator>(const BaseEdge &e) const { return e.weight() < this->weight_; }
    bool operator<(const BaseEdge &e) const { return e.weight() > this->weight_; }
    bool operator>=(const BaseEdge &e) const { return !(e > *this); }
    bool operator<=(const BaseEdge &e) const { return !(e < *this); }

protected:
    int v;
    int w;
    double weight_;
};

class DirectedEdge : public BaseEdge
{
public:
    DirectedEdge() : BaseEdge(){};
    DirectedEdge(int v, int w, double wei) : BaseEdge(v, w, wei){};

    int from() const { return v; };
    int to() const { return w; };

    bool operator==(const DirectedEdge &e) const
    {
        return e.weight() == this->weight() && e.from() == this->from() && e.to() == this->to();
    }

    friend std::ostream &operator<<(std::ostream &os, const DirectedEdge &edge);
};

class Edge : public BaseEdge
{
public:
    Edge() : BaseEdge(){};
    Edge(int v, int w, double wei) : BaseEdge(v, w, wei){};
    int either() const { return v; }
    int other(int ver) const;

    bool operator==(const Edge &edge) const { return edge.weight() == this->weight(); }

    friend std::ostream &operator<<(std::ostream &os, const Edge &edge);
};

int Edge::other(int ver) const
{
    if (ver == v)
        return w;
    else if (ver == v)
        return w;
    else
        throw std::runtime_error("edge error");
}

std::ostream &operator<<(std::ostream &os, const DirectedEdge &edge)
{
    os << edge.from() << "->" << edge.to() << " w:" << edge.weight();
    return os;
}

std::ostream &operator<<(std::ostream &os, const Edge &edge)
{
    int v = edge.either();
    os << v << "-" << edge.other(v) << " w:" << edge.weight();
    return os;
}

#endif