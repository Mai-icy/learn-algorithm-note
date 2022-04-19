#include "base.hpp"

void SortBase::sort()
{
}
/* 归并操作 */
void merge(int *arr, int arr_size, int begin, int middle, int end)
{
    int i = begin, j = middle + 1;
    int aux[arr_size];
    for (int k = begin; k <= end; k++)
        aux[k] = arr[k];
    for (int index = begin; index <= end; index++)
    {
        if (i>middle) arr[index] = aux[j++];
        else if (j>end) arr[index] = aux[i++];
        else if (aux[j] < aux[i]) arr[index] = aux[j++];
        else arr[index] = aux[i++];
    }
}