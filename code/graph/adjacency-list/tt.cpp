#include "base\\undirected-graph.hpp"
#include <typeinfo>
#include <iostream>
#include <string>

int main()
{
    using namespace std;
    Bag<int> test;
    test.add(1);
    test.add(2);

    cout << test << "\n";

    // Bag<int> test2(test);

    // cout << test2 << "\n";

    return 0;
}
