#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "..\\base\\undirected-graph.hpp"

class Search{
    public:
        Search(Graph G, int s);
        bool marked(int v);
        int count();
        ~Search(){delete [] _marked;}
    private:
        void dfs(Graph G, int s);
        void bfs(Graph G, int s);

        bool* _marked = nullptr;
        int _count = 0;
        int root_node;
};

#endif
