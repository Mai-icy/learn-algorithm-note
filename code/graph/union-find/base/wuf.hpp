#ifndef WUF_HPP
#define WUF_HPP

#include "uf.hpp"

class WUF : public UF
{
public:
    WUF(int n) : UF(n), sz(new int[n])
    {
        for (int i = 0; i < n; i++)
            sz[i] = 1;
    }
    ~WUF() { delete[] sz; }
    void connect(int w, int v);
    int find(int v) const;

    friend std::ostream &operator<<(std::ostream &os, const WUF &wuf);

protected:
    int *sz;
};

std::ostream &operator<<(std::ostream &os, const WUF &wuf)
{
    using namespace std;
    for (int i; i < wuf.size; i++)
    {
        os << i << " " << wuf.id[i] << endl;
    }
    return os;
}

WUF createRandomWUF(int size, int connect_times = 0)
{
    using namespace std;
    WUF new_wuf(size);
    default_random_engine e(time(0));
    uniform_int_distribution<unsigned> u(0, size - 1);
    if (connect_times == 0)
    {
        size_t max_connect_num = size * (size - 1) / 4;
        uniform_int_distribution<unsigned> connect_num_u(0, max_connect_num);
        connect_times = connect_num_u(e);
    }

    for (int i = 0; i < connect_times; i++)
    {
        int v = u(e);
        int w = u(e);
        new_wuf.connect(w, v);
    }
    return new_wuf;
}

#endif
