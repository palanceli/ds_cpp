#include "stdio.h"
#include <string.h>
#include <iostream>
#include <gtest/gtest.h>
#include "glog/logging.h"

class Playground201910 : public testing::Test{
  
protected:
  static void SetUpTestCase(){
    FLAGS_logtostderr = 1; // 输出到控制台
    setlocale(LC_ALL, "");
  }
  static void TearDownTestCase(){
  }
  
};


class TC01Solution {
  // 给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
  // 说明： 你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？
  //
  // 示例 1:
  //  输入: [2,2,1]
  //  输出: 1
  //
  // 示例 2:
  //  输入: [4,1,2,1,2]
  //  输出: 4
  //
  // 思路：通过异或操作（相同为0，相异为1）对所有元素运算一轮，最终运算结果就是要求的数。
public:
  int singleNumber(std::vector<int>& nums) {
    int num = 0;
    for(int i=0; i<nums.size(); i++){
      num = num ^ nums[i];
    }
    return num;
  }
  
  void main(){
    std::vector<int> nums = {2, 2, 9, 3, 4, 6, 4, 6, 3};
    LOG(INFO) << singleNumber(nums);
  }
  
};

TEST_F(Playground201910, TC01){
  TC01Solution s;
  s.main();
}
