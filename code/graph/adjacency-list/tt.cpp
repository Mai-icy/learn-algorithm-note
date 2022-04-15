#include "base\\undirected-graph.hpp"
#include <typeinfo>
#include <iostream>
#include <string>

int main()
{
    using namespace std;

    Graph test = createRondomGraph(10);

    

    cout << test;

    return 0;
}
