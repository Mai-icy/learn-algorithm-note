#include "base/uf.hpp"

int WUF::find(int v) const
{
    while (v != id[v])
        v = id[v];
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

