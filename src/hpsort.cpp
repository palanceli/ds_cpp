
#include <stdio.h>

#include <gtest/gtest.h>
#include <algorithm>
#include "glog/logging.h"
class HPSortTest : public testing::Test{

protected:
  static void SetUpTestCase(){
    FLAGS_logtostderr = 1; // 输出到控制台
    setlocale(LC_ALL, "");
  }
  static void TearDownTestCase(){
  }
  
};

// 先建堆，再逐个从堆顶取出元素，从尾部补充上来，重建堆

// 题目：阅读如下代码，简述MainProc和SubProc的算法思想，并结合实例说明运算结果

void SubProc(int a[], int s, int m)
{
  int rc, j;
  rc = a[s];
  for (j = (s << 1) + 1; j < m; j <<= 1)
  {
    if (j + 1 < m && a[j] < a[j + 1])
      j++;
    if (rc > a[j])
      break;
    a[s] = a[j];
    s = j;
  }
  a[s] = rc;
}

void MainProc(int a[], int n)
{
  for (auto i = (n >> 1) - 1; i >= 0; i--)
    SubProc(a, i, n);
  
  for (auto i = n - 1; i >= 0; i--)
  {
    auto temp = a[0];
    a[0] = a[i];
    a[i] = temp;
    SubProc(a, 0, i);
  }
}

TEST_F(HPSortTest, TC01){
  int a[] = {1, 3, 2, 4, 7, 6, 4, 9};
  int cnt = sizeof(a) / sizeof(int);
  for (auto i = 0; i < cnt; i++)
  {
    printf("%d ", a[i]);
  }
  printf("\n");

  MainProc(a, cnt);

  for (auto i = 0; i < cnt; i++)
  {
    printf("%d ", a[i]);
  }
  printf("\n");
}

// 出自Knuth, D.E. 1973, Sorting and Searching,
// vol. 3 of The Art of Computer Programming
void hpsort(unsigned long n, int ra[])
{
  int rra;

  if (n < 2)
    return;
  auto l = (n >> 1) + 1;
  auto ir = n;

  for (;;)
  {
    if (l > 1)
      rra = ra[--l];
    else
    {
      rra = ra[ir];
      ra[ir] = ra[1];
      if (--ir == 1)
      {
        ra[1] = rra;
        break;
      }
    }
    auto i = l;
    auto j = l + 1;
    while (j <= ir)
    {
      if (j < ir && ra[j] < ra[j + 1])
        j++;
      if (rra < ra[j])
      {
        ra[i] = ra[j];
        i = j;
        j <<= 1;
      }
      else
        break;
    }
    ra[i] = rra;
  }
}

TEST_F(HPSortTest, TC02){
  int a[] = {0, 1, 3, 2, 4, 7, 6, 4, 9};
  int cnt = sizeof(a) / sizeof(int);
  for (auto i = 0; i < cnt; i++)
  {
    printf("%d ", a[i]);
  }
  printf("\n");

  hpsort(cnt-1, a);

  for (auto i = 0; i < cnt; i++)
  {
    printf("%d ", a[i]);
  }
  printf("\n");
}