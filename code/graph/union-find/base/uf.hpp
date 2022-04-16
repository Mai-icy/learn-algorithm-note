#ifndef UF_HPP
#define UF_HPP

#include <iostream>
#include <random>
#include <ctime>

class UF
{
public:
    UF(int n);
    UF(const UF &uf);
    ~UF() { delete[] id; }

    virtual void connect(int w, int v);
    virtual int find(int v) const;
    bool connected(int w, int v) const { return find(w) == find(v); };
    int count() const { return _count; };

    UF &operator=(const UF &uf);
    friend std::ostream &operator<<(std::ostream &os, const UF &uf);

protected:
    int size;
    int _count;
    int *id = nullptr;
};

UF::UF(const UF &uf)
{
    id = new int[uf.size];
    size = uf.size;
    _count = uf._count;
    for (int i; i < size; i++)
    {
        id[i] = uf.id[i];
    }
}

UF &UF::operator=(const UF &uf)
{
    if (this == &uf)
        return *this;

    delete[] id;
    id = new int[uf.size];
    size = uf.size;
    _count = uf._count;
    for (int i; i < size; i++)
    {
        id[i] = uf.id[i];
    }
    return *this;
}

UF::UF(int n) : size(n), _count(n), id(new int[n])
{
    for (int i; i < n; i++)
        id[i] = i;
}

UF createRandomUF(int size, int connect_times = 0)
{
    using namespace std;
    UF new_uf(size);

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
        new_uf.connect(w, v);
    }
    return new_uf;
}

std::ostream &operator<<(std::ostream &os, const UF &uf)
{
    using namespace std;
    for (int i; i < uf.size; i++)
    {
        os << i << " " << uf.id[i] << endl;
    }
    return os;
}



#endif
