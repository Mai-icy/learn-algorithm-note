#include <iostream>
#include <random>
#include <ctime>

#ifndef BASE_HPP
#define BASE_HPP

class SortBase
{
private:
    int *arr;
    int size;
    void exch(int index_1, int index_2);

public:
    SortBase(int *ptr_val, int size_of_val) : arr(ptr_val), size(size_of_val){};
    void sort();
    friend std::ostream &operator<<(std::ostream &c_in, const SortBase &data);
};

std::ostream &operator<<(std::ostream &c_out, const SortBase &data)
{
    c_out << '[';
    for (int index = 0; index < data.size - 1; index++)
    {
        c_out << data.arr[index] << ",";
    }
    c_out << data.arr[data.size - 1] << ']';
    return c_out;
}

inline void SortBase::exch(int index_1, int index_2)
{
    int temp = arr[index_1];
    arr[index_1] = arr[index_2];
    arr[index_2] = temp;
}

int main()
{

    std::default_random_engine e(time(0));
    std::uniform_int_distribution<unsigned> u(0, 100);
    int test[20];
    for (size_t i = 0; i < 20; i++)
    {
        test[i] = u(e);
    }
    SortBase tt(test, 20);
    std::cout << tt << std::endl;
    tt.sort();
    std::cout << tt;
    return 0;
}
#endif
