#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include "SP.hpp"

int main()
{
    using namespace std;

    priority_queue<DirectedEdge, vector<DirectedEdge>, greater<DirectedEdge>> pq;

    DirectedEdge e1(1, 2, 123);
    DirectedEdge e2(1, 2, 1);
    DirectedEdge e3(1, 2, 6);
    DirectedEdge e4(1, 2, 678);

    pq.push(e1);
    pq.push(e2);
    pq.push(e3);
    pq.push(e4);

    cout << pq.top();


    return 0;
}
