#include <string.h>
#include <stdio.h>

#include <gtest/gtest.h>
#include <algorithm>
#include "glog/logging.h"

// 输入数字n，按顺序打印出从1到最大的n位八进制数
// 阅读如下代码，说明MainProc的处理逻辑
bool SubProc(char *number, int system)
{
    int takeover = 0;
    int length = strlen(number);
    for (int i = length - 1; i >= 0; i--)
    {
        int sum = number[i] - '0' + takeover;
        if (i == length - 1)
            sum++;
        if (sum >= system)
        {
            if (i == 0)
                return true;
            else
            {
                takeover = 1;
                number[i] = '0';
            }
        }
        else
        {
            number[i] = sum + '0';
            break;
        }
    }
    return false;
}

void MainProc(int n, int s)
{
    if (n <= 0 || s > 10)
        return;
    char *number = new char[n + 1];
    memset(number, '0', n);
    number[n] = '\0';
    while (!SubProc(number, s))
        printf(" %s", number);
    printf("\n");
    delete []number;
}

class PrintNumberTest : public testing::Test{

protected:
  static void SetUpTestCase(){
    FLAGS_logtostderr = 1; // 输出到控制台
    setlocale(LC_ALL, "");
  }
  static void TearDownTestCase(){
  }
  
};

TEST_F(PrintNumberTest, TC01){
    MainProc(3, 8);
    printf("\n");
}

