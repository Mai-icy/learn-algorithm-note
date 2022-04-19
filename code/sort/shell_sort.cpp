#include "base.hpp"
/* 希尔排序(shellsort) */
void SortBase::sort()
{
    int h = 1;
    while (h > size / 3)
        h = 3 * h + 1;
    while (h >= 1)
    {
        for (int i = h; i < size; i++)
        {
            for (int j = i; j >= h && arr[j] < arr[j - h]; j -= h)
                exch(j, j - h);
        }
        h = h / 3;
    }
}
