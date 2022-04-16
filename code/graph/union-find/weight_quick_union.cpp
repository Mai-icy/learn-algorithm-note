#include "base/wuf.hpp"

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

int WUF::find(int v) const
{
    int ori_p = v;
    while (v != id[v])
        v = id[v];
    id[ori_p] = v; // 路径压缩
    return v;
}

void WUF::connect(int w, int v)
{
    int w_id = find(w);
    int v_id = find(v);
    if (w_id == v_id)
        return;
    if (sz[w] < sz[v])
    {
        id[w] = v;
        sz[v] += sz[w];
    }
    else
    {
        id[v] = w;
        sz[w] += sz[v];
    }
    _count--;
}

int main()
{
    using namespace std;
    WUF test = createRandomWUF(20, 4);
    cout << test;
    return 0;
}
