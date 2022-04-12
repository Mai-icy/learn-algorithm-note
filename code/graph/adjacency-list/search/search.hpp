#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "..\\base\\undirected-graph.hpp"

class Search{
    public:
        Search(Graph G, int s);
        bool marked(int v);
        int count();
    private:
        int* _marked = nullptr;
        int _count;
};

#endif
