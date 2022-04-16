#include "base/uf.hpp"

int UF::find(int v) const
{
    while (v != id[v])
        v = id[v];
    return v;
}

void UF::connect(int w, int v)
{
    int w_id = find(w);
    int v_id = find(v);
    if (w_id == v_id)
        return;
    id[w] = v;
    _count--;
}

int main()
{
    using namespace std;
    UF test = createRandomUF(20, 4);
    cout << test;
    return 0;
}