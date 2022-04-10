#include "base.hpp"

void SortBase::sort()
{
  for (int i = 1; i < size; i++)
  {
    for (int j = i; j > 0; j--)
    {
      if (arr[j] < arr[j - 1])
      {
        exch(j, j - 1);
      }
      else
      {
        break;
      }
    }
  }
}
