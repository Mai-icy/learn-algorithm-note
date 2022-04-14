#include "base\\undirected-graph.hpp"
#include <typeinfo>
#include <iostream>
#include <string>

int main()
{
    using namespace std;

    Graph test(10);

    test.addEdge(1, 2);
    test.addEdge(4, 5);
    test.addEdge(1, 5);

    Graph test2(test);

    Graph test3(20);
    test3 = test;

    auto bag_test = test.adj(1);
    cout << bag_test;

    cout << test.adj(1);
    cout << "test" << endl;

    // Bag<int> test2(test);

    // cout << test2 << "\n";

    return 0;
}
