#include "base/uf.hpp"

inline int UF::find(int v) const { return id[v]; }

void UF::connect(int w, int v)
{
    int w_id = id[w];
    int v_id = id[v];

    if (w_id == v_id)
        return;

    for (int i = 0; i < size; i++)
    {
        if (id[i] == w_id)
            id[i] = v;
        _count--;
    }
}


int main()
{
    using namespace std;
    UF test = createRandomUF(20, 4);
    cout << test;
    return 0;
}


