#include "base.hpp"

void SortBase::sort()
{
  for (int start_index = 0; start_index < size; start_index++)
  {
    int min_index = size - 1;
    for (int now_index = start_index; now_index < size; now_index++)
    {
      if (arr[min_index] > arr[now_index])
      {
        min_index = now_index;
      }
    }
    exch(start_index, min_index);
  }
}
