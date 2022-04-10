#include "base.hpp"

/* 逐一选择元素，插入到前面有序的数列中 */
void SortBase::sort()
{
  for (int i = 1; i < size; i++)
  { //遍历列表
    for (int j = i; j > 0; j--)
    {
      if (arr[j] < arr[j - 1])
      // 不断前移找到合适的位置
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
