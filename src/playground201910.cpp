#include "stdio.h"
#include <string.h>
#include <iostream>
#include <gtest/gtest.h>
#include <algorithm>
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

class TC03Solution {
  // 假设我们有一个队列，可能存放几千万上亿的数据，我们应该如何设计这个队列？
  // 写出来看看？
  // （提问：这个队列是只需要在头尾添加和删除吗？双向队列？答：是的） 
public:
  template <class V>
  class Node
  {
  public:
    Node *pNext;
    Node *pPre;
    V value;
  };

  template <class V>
  class DoubleLinkList{
    Node<V> *head;
    Node<V> *tail;
    public:
    DoubleLinkList(){
      head = nullptr;
      tail = nullptr;
    }
    void addHead(V value){
      Node<V> *pNode = new(Node<V>);
      pNode->value = value;
      if(head == nullptr){
        pNode->pNext = nullptr;
        pNode->pPre = nullptr;
        tail = pNode;
      }else{
        pNode->pNext = head;
        head->pPre = pNode;
      }
      head = pNode;
    }
    Node<V>* removeHead(){
      Node<V>* pNode = head;
      if(pNode == nullptr)
        return nullptr;
      if(head->pNext == nullptr){
        tail = nullptr;
      }else{
        head->pPre = nullptr;
      }
      head = pNode->pNext;
      return pNode;
    }
    void print(){
      for(Node<V>* node=head; node!=nullptr; node=node->pNext){
        LOG(INFO)<<node->value;
      }
    }
  };

  // 为什么不能偏特化？
  // template<>
  // class DoubleLinkList<int>{
  //   public:
  //   void print(){
  //     for(Node<int>* node=head; node!=nullptr; node=node->pNext){
  //       printf(" %d", node->value);
  //     }
  //     printf("\n");
  //     for(Node<int>* node=tail; node!=nullptr; node=node->pPre){
  //       printf(" %d", node->value);
  //     }
  //     printf("\n");
  //   }
  // };
  
  void main(){
    DoubleLinkList<int> dll;
    for(int i=0; i<8; i++){
      dll.addHead(i);
    }
    dll.print();
    LOG(INFO)<<"removing double link list...";
    Node<int>* pNode = dll.removeHead();
    while(pNode!=nullptr){
      LOG(INFO)<<pNode->value;
      delete pNode;
      pNode = dll.removeHead();
    }
  }
};
TEST_F(Playground201910, TC03){
  TC03Solution s;
  s.main();
}

class TC04Solution {
  // 在一个二维数组中，每一行都从左到右，每一列都从上到下都是递增的。
  // 请完成一个函数，输入该矩阵和一个整数，判断数组中是否含有该整数。
  // 思路：
  // 矩阵从左下角来看，向上递减，向右递增。因此从左下角开始查找，
  // 当要查找数字比左下角数字大时，右移
  // 当要查找数字比左下角数字小时，上移

public:
  bool find(std::vector<std::vector<int> > matrix, int obj){
    int row = matrix.size() - 1;
    int col = 0;
    int maxCol = matrix[0].size();
    while(row>=0 && col<maxCol){
      if(obj>matrix[row][col]){
        col++;
      }else if(obj<matrix[row][col]){
        row--;
      }else{
        return true;
      }
    }
    return false;
  }

  void main(){
    int data[4][6]={
      {0, 4, 7,  9,  12, 20},
      {3, 6, 10, 15, 17, 24},
      {5, 9, 12, 18, 21, 25},
      {7, 10,16, 20, 24, 30},
    };
    std::vector<std::vector<int> > matrix;
    for(int i=0; i<4; i++){
      std::vector<int> row;
      for(int j=0; j<6; j++){
        row.push_back(data[i][j]);
      }
      matrix.push_back(row);
    }
    LOG(INFO)<<find(matrix, 23);
  }
};
TEST_F(Playground201910, TC04){
  TC04Solution s;
  s.main();
}

class TC05Solution {
  // 翻转链表
  class Node
  {
  public:
    Node *m_pNext;
    int m_value;
    Node(int value, Node *pNext = nullptr) : m_pNext(pNext), m_value(value) {}
  };

public:
  void printLinklist(Node* pHead){
    for(Node* pNode=pHead; pNode!=nullptr; pNode=pNode->m_pNext){
      printf(" %d", pNode->m_value);
    }
    printf("\n");
  }

  Node* revertLinklist(Node* pHead){
    if(pHead == nullptr || pHead->m_pNext == nullptr)
      return pHead;
    Node *p1 = pHead;
    Node *p2 = pHead->m_pNext;
    p1->m_pNext = nullptr;
    while(p2 != nullptr){
      Node *pTmp = p2->m_pNext;
      p2->m_pNext = p1;
      p1 = p2;
      p2 = pTmp;
    }
    return p1;
  }

  void main(){
    Node* pHead = new Node(0);
    for(int i=1; i<10; i++){
      Node* pTmp = new Node(i, pHead);
      pHead = pTmp;
    }
    printLinklist(pHead);
    pHead = revertLinklist(pHead);
    printLinklist(pHead);
  }
};

TEST_F(Playground201910, TC05){
  TC05Solution s;
  s.main();
}

class TC06Solution {
  // 给出一棵二叉树，寻找一条路径使其路径和最大，路径可以在任一节点中开始和结束
  // 路径和为两个节点之间所在路径上的节点权值之和
  // 思路：
  // 对于任意节点root，经过它的最大路径是：
  //  （1）root->value + 以root->left为起点的最大路径
  //  （2）root->value + 以root->right为起点的最大路径
  //  （3）root->value
  //  （4）root->value + 以root->left为起点的最大路径 + 以root->right为起点的最大路径
  // max(1, 2, 3, 4)，这本身就是一个递归过程，记录下这个过程中的最大值，
  // 递归的返回值表示以root为起点的最大路径，因此不应包含（4）
  class TreeNode{
    public:
    TreeNode *mLeft, *mRight;
    int mValue;
    TreeNode(int value, TreeNode *left=nullptr, TreeNode *right=nullptr) : 
    mValue(value), mLeft(left), mRight(right) {}
  };
public:
  int res = -100000;
  int maxPathSum(TreeNode* root){
    helper(root);
    return res;
  }
  int helper(TreeNode* node){
    if(node == nullptr)
      return 0;
    int left = helper(node->mLeft);
    int right = helper(node->mRight);

    int maxSum = std::max(std::max(node->mValue+left, node->mValue+right), node->mValue);
    int maxCurrent = std::max(maxSum, node->mValue+left+right);

    res = std::max(res, maxCurrent);
    return maxSum;
  }

  void main(){
    TreeNode* l1 = new TreeNode(1);
    TreeNode* r1 = new TreeNode(50);
    TreeNode* p1 = new TreeNode(-100, l1, r1);
    TreeNode* l2 = new TreeNode(3);
    TreeNode* r2 = new TreeNode(4);
    TreeNode* p2 = new TreeNode(2, l2, r2);
    TreeNode* p = new TreeNode(10, p1, p2);
    LOG(INFO)<<maxPathSum(p);
  }
};

TEST_F(Playground201910, TC06){
  TC06Solution s;
  s.main();
}

class TC07Solution {
  // 求连续子数组的最大和
  // 一个整数数组中的元素有正有负，在该数组中找出一个连续子数组，要求该连续子
  // 数组中各元素的和最大。比如数组{2,4,-7,5,2,-1,2,-4,3}的最大连续子数组为
  // {5,2,-1,2}，最大连续子数组的和为5+2-1+2=8。
  // 问题输入就是一个数组，输出该数组的“连续子数组的最大和”。
  // 思路：
  // 从左到右遍历数组，计算以当前元素结尾的子数组的最大和，引入两个辅助变量：
  // res和sum，res是全局最大和，sum是以当前元素结尾的子数组最大和
public:
  int maxSubArray(int* array, int num){
    int res = array[0];
    int sum = 0;
    for(int i=0; i<num; i++){
      sum += array[i];
      if(sum > res){
        res = sum;
      }
      // 只要前面的和为正，就可以保留，否则抛弃
      if(sum < 0){
        sum = 0;
      }
    }
    return res;
  }

  void main(){
    // int data[] = {2, 4, -7, 5, 2, -1, 2, -4, 3};
    int data[] = {9, 3, -8, -9, 5, 7, 4, 1, -2};
    int num = sizeof(data) / sizeof(int);
    LOG(INFO)<<maxSubArray(data, num);
  }
};

TEST_F(Playground201910, TC07){
  TC07Solution s;
  s.main();
}

class TC08Solution {
  // 给定两个字符串数组s1和s2，求s2是由s1删除了哪些元素得到？
  // 例如s1={"a","b","c","d","e"}, s2={"a","e","c"}, 结果应该为{"b","d"}
public:
  void delChars(char* s1, int num1, char* s2, int num2){
    bool dict[256] = {0};
    for(int i=0; i<num2; i++){
      dict[s2[i]] = 1;
    }
    int wPos = 0;
    int rPos = 0;
    while(rPos < num1){
      if(dict[s1[rPos]] == 0){
        s1[wPos] = s1[rPos];
        wPos++;
      }
      rPos++;
    }
    s1[wPos] = '\0';
  }
  void main(){
    char s1[] = {"a1b2c3d4e5fg6h7i8j9kl0mn"};
    char s2[] = {"0123456789"};
    int num1 = strlen(s1);
    int num2 = strlen(s2);
    delChars(s1, num1, s2, num2);
    LOG(INFO)<<s1;
  }
};

TEST_F(Playground201910, TC08){
  TC08Solution s;
  s.main();
}

class TC09Solution {
  // 二分法求平方根
public:
  float mySqrt(int x){
    float EPSINON = 0.01;
    float l = 0;
    float r = x;
    while(true){
      float mid = (r + l) / 2;
      float diff = mid * mid - x;
      if((diff >= 0 && diff < EPSINON) || diff <= 0 && -diff <EPSINON){
        return mid;
      }
      if(diff > 0){
        r = mid;
      }else{
        l = mid;
      }
    }
  }
  void main(){
    LOG(INFO)<<mySqrt(13);
  }
};

TEST_F(Playground201910, TC09){
  TC09Solution s;
  s.main();
}


class TCXXSolution {
public:
  void main(){
  }
};

TEST_F(Playground201910, TCXX){
  TCXXSolution s;
  s.main();
}
