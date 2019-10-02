#include "stdio.h"
#include <string.h>
#include <iostream>
#include <gtest/gtest.h>
#include "glog/logging.h"

// ./ds_cpp --gtest_filter=Playground201910.TC02
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


class TC02Solution {
  // 一个链表，假设第一个节点我们定为下标为1，第二个为2，那么下标为
  // 奇数的结点是升序排序，偶数的结点是降序排序，如何让整个链表有序？
  //
  // 思路：分离链表，合并两个有序链表
public:
  class Node
  {
  public:
    Node *pNext;
    int value;
  };
  int singleNumber(std::vector<int>& nums) {
    int num = 0;
    for(int i=0; i<nums.size(); i++){
      num = num ^ nums[i];
    }
    return num;
  }

  Node* createLinklist(int *data, int num){
    if(num == 0)
      return nullptr;
    Node* pHead = new(Node);
    pHead->value = data[0];
    pHead->pNext = nullptr;
    Node* pTail = pHead;
    for(int i=1; i<num; i++){
      Node* pNew = new(Node);
      pNew->value = data[i];
      pNew->pNext = nullptr;
      pTail->pNext = pNew;
      pTail = pNew;
    }
    return pHead;
  }

  void printLinklist(Node* pHead){
    for(Node* pNode=pHead; pNode != nullptr; pNode = pNode->pNext){
      if(pNode != pHead)
        printf(", ");
      printf("%d", pNode->value);
    }
    printf("\n");
  }

  // 将混合链表拆成两个升序链表
  void splitLinklist(Node* pHead, Node* &p1, Node* &p2){
    p1 = p2 = nullptr;
    if(pHead == nullptr)
      return;

    p1 = pHead;
    p2 = p1->pNext;
    int curr = 2;
    if(p2 == nullptr)
      return;
    Node* pCurr = p2->pNext;
    p2->pNext = nullptr;  // 注意：断掉p2的pNext是防止产生循环链表

    for(; pCurr!=nullptr; ++curr){
      if(curr % 2 == 0){ // 升序节点
        p1->pNext = pCurr;
        p1 = p2;
        p2 = pCurr;
        pCurr = pCurr->pNext;
      }else{            // 降序节点
        Node* pTmp = pCurr;
        pCurr = pCurr->pNext;
        pTmp->pNext = p1;
        p1 = p2;
        p2 = pTmp;
      }
    }
    p1->pNext = nullptr;  // 注意：断掉p1->pNext防止再链到p2上去
    p1 = pHead;
  }

  // 归并两个升序链表
  Node* mergeLinklist(Node* p1, Node* p2){
    if(p1 == nullptr)
      return p2;
    if(p2 == nullptr)
      return p1;

    Node* pNode = p1;
    if(p1->value > p2->value){
      pNode = p2;
      p2 = p2->pNext;
    }else{
      p1 = p1->pNext;
    }
    Node* pHead = pNode;

    while(p1!=nullptr && p2!=nullptr){
      if(p1->value > p2->value){
        pNode->pNext = p2;
        p2 = p2->pNext;
      }else{
        pNode->pNext = p1;
        p1 = p1->pNext;
      }
      pNode = pNode->pNext;
    }
    return pHead;
  }
  
  void main(){
    int data[] = {1, 10, 5, 8, 9, 6, 14, 3};
    int num = sizeof(data) / sizeof(int);
    Node* pLinklist = createLinklist(data, num);
    printLinklist(pLinklist);
    Node *p1, *p2;
    splitLinklist(pLinklist, p1, p2);
    printLinklist(p1);
    printLinklist(p2);
    pLinklist = mergeLinklist(p1, p2);
    printLinklist(pLinklist);
  }
};

TEST_F(Playground201910, TC02){
  TC02Solution s;
  s.main();
}
