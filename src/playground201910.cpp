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

class TC10Solution
{
  // 《剑指Offer》p44，定义并实现赋值运算函数
  class CMyString
  {
  public:
    CMyString(char *pData = nullptr){
      if(m_pData != nullptr)
        delete []m_pData;
      m_pData = pData;
    }
    CMyString(const CMyString &str){
      if(m_pData != nullptr)
        delete []m_pData;
      m_pData = new char[strlen(str.m_pData)];
      strcpy(m_pData, str.m_pData);
    }
    ~CMyString(void){
      if(m_pData != nullptr)
        delete []m_pData;
      m_pData = nullptr;
    }
    CMyString& operator=(const CMyString& obj){
      if(this != &obj){
        CMyString strTmp(obj);
        char* pTmp = strTmp.m_pData;
        strTmp.m_pData = m_pData;
        m_pData = pTmp;
      }
      return *this;
    }

  private:
    char *m_pData;
  };

public:
  void main()
  {
  }
};

TEST_F(Playground201910, TC10){
  TC10Solution s;
  s.main();
}

class TC11Solution {
  // 在长度为n的数组里，所有数字都∈[0, n-1]数组内某些数字是重复的，但不知道
  // 有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任一个重复的数字。
  // 《剑指Offer》题3
public:
  int getdup(int *data, int num){
    int pos = 0;
    while(pos<num){
      if(data[pos] != pos){
        int value = data[pos];
        if(data[value] == value){
          return value;
        }else{
          int tmp = data[value];
          data[value] = data[pos];
          data[pos] = tmp;
        }
      }else{
        pos++;
      }
    }
    return num;
  }
  void main(){
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 3};
    int num = sizeof(data);
    LOG(INFO)<<getdup(data, num);
  }
};

TEST_F(Playground201910, TC11){
  TC11Solution s;
  s.main();
}


class TC12Solution {
  // 在一个长度为n+1的数组里，所有数字都∈[1, n]，因此数组中至少有一个数字
  // 是重复的。请在不修改输入数组的情况下找出任意重复的数字
public:
  int getdup1(int *data, int num){ // 时间优先
    int *tmp = new int[num];
    int dup = num+1;
    for(int i=0; i<num; i++){
      tmp[i] = num+1;
    }
    for(int i=0; i<num; i++){
      int value = data[i];
      if(tmp[value] == value){
        dup = value;
        break;
      }else{
        tmp[value] = value;
      }
    }
    delete []tmp;
    return dup;
  }
  bool hasdup(int *data, int num, int start, int end){
    int count = 0;
    for(int i=0; i<num; i++){
      if(data[i]>=start && data[i]<end)
        count++;
      if(count > end-start)
        return true;
    }
    return false;
  }
  int getdup2(int *data, int num){ // 空间优先
    int start = 1;
    int end = num;
    while(end - start > 1){
      LOG(INFO)<<"["<<start<<","<<end<<")";
      int mid = (start + end) /2 ;
      if(hasdup(data, num, start, mid)){
        end = mid;
      }else{
        start = mid;
      }
    }
    return start;
  }
  void main(){
    int data[] = {1, 2, 3, 8, 4, 5, 6, 7, 8};
    int num = sizeof(data)/sizeof(int);
    LOG(INFO)<<getdup2(data, num);
  }
};

TEST_F(Playground201910, TC12){
  TC12Solution s;
  s.main();
}

class TC13Solution {
  // 把字符串中每个空格替换成"%20"，例如：输入"We are happy."
  // 输出"We%20are%20happy."
public:
  char* replaceSpace(char* data){
    if(data == nullptr)
      return nullptr;
    int cSpace = 0;
    for(char* p=data; *p!='\0'; p++){
      if(*p == ' ')
        cSpace++;
    }
    LOG(INFO)<<"space num:%d"<<cSpace;
    
    int len = strlen(data);
    char* p2 = data+len+2*cSpace;
    for(char* p1=data+len; p1>=data; p1--){
      if(*p1 != ' '){
        *p2 = *p1;
        p2--;
      }else{
        *p2-- = '0';
        *p2-- = '2';
        *p2-- = '%';
      }
    }
    return data;
  }
  void main(){
    char data[64] = {"We are not happy."};
    LOG(INFO)<<replaceSpace(data);
  }
};

TEST_F(Playground201910, TC13){
  TC13Solution s;
  s.main();
}

class TC14Solution {
  // 有两个排序数组A1和A2，内存在A1末尾有足够多的空间容纳A2，请实现一个函数
  // 把A2中所有数字插入A1，并确保数字是排序的。
public:
  void mergeArray(int* A1, int num1, int* A2, int num2){
    int *p1 = A1 + num1 - 1;
    int *p2 = A2 + num2 - 1;
    for(int *p = A1+num1+num2-1; p>=A1; ){
      if (p1 >= A1 && p2 >= A2){
        if (*p1 >= *p2){
          *p-- = *p1--;
        }else{
          *p-- = *p2--;
        }
      }else if(p1 < A1){
        *p-- = *p2--;
      }else if(p2 < A2){
        *p-- = *p1--;
      }
    }
  }

  void main(){
    int A[] = {0, 2, 6, 8, 10, 14, 20};
    int A2[] = {1, 3, 8, 17};
    int A1[64];
    memcpy(A1, A, sizeof(A));
    int num1 = sizeof(A) /sizeof(int);
    int num2 = sizeof(A2) / sizeof(int);
    mergeArray(A1, num1, A2, num2);
    LOG(INFO)<<"merge result:";
    for(int i=0; i<num1+num2; i++){
      printf(" %d", A1[i]);
    }
    printf("\n");
  }
};

TEST_F(Playground201910, TC14){
  TC14Solution s;
  s.main();
}

class TC15Solution {
  // 输入一个连表的头节点，从尾到头反过来打印每个节点的值
public:
  struct Node
  {
    Node *m_pNext;
    int m_value;
  };
  void printLinklist(Node* p){
    if(p->m_pNext != nullptr){
      printLinklist(p->m_pNext);
    }
    printf(" %d", p->m_value);
  }
  void main(){
    Node *pHead = nullptr;
    for(int i=0; i<10; i++){
      Node *pNode = new(Node);
      pNode->m_value = i;
      pNode->m_pNext = pHead;
      pHead = pNode;
    }
    LOG(INFO)<<"print link list:";
    for(Node* p=pHead; p!=nullptr; p=p->m_pNext){
      printf(" %d", p->m_value);
    }
    printf("\n");

    LOG(INFO)<<"reverse print link list:";
    printLinklist(pHead);
    printf("\n");
  }
};

TEST_F(Playground201910, TC15){
  TC15Solution s;
  s.main();
}

class TC16Solution {
  // 输入某二叉树前序遍历和中序遍历序列，构建该二叉树。
  // 例如前序序列：{1, 2, 4, 7, 3, 5, 6, 8}
  // 中序序列：{4, 7, 2, 1, 5, 3, 8, 6}
  // 思路：显然1为根节点，中序序列中{4, 7, 2}和{5, 3, 8, 6}分别在左子树和右子树
public:
  struct Node{
    int m_Value;
    Node *m_pLeft, *m_pRight;
  };
  Node* constructTree(int *preorder, int* inorder, int num){
    Node* root = new(Node);
    root->m_Value = *preorder;
    if(num == 1){
      if(*preorder != *inorder)
        return nullptr;
      return root;
    }
    int rootPosInOrder = 0;
    while(rootPosInOrder<num){
      if(inorder[rootPosInOrder] == *preorder)
        break;
      rootPosInOrder++;
    }
    if(rootPosInOrder >= num)
      return nullptr;
    Node* left = constructTree(preorder+1, inorder, rootPosInOrder);
    Node* right = constructTree(preorder+1+rootPosInOrder, 
    inorder+1+rootPosInOrder, num - rootPosInOrder - 1);
    root->m_pLeft = left;
    root->m_pRight = right;
    return root;
  }
  void preWalkthroughTree(Node* node){
    if(node == nullptr)
      return;
    printf(" %d", node->m_Value);
    preWalkthroughTree(node->m_pLeft);
    preWalkthroughTree(node->m_pRight);
  }
  void inWalkthroughTree(Node* node){
    if(node == nullptr)
      return;
    inWalkthroughTree(node->m_pLeft);
    printf(" %d", node->m_Value);
    inWalkthroughTree(node->m_pRight);
  }
  void printTree(Node* node){
    LOG(INFO)<<"pre order walk through:";
    preWalkthroughTree(node);
    printf("\n");
    LOG(INFO)<<"in order walk through:";
    inWalkthroughTree(node);
    printf("\n");
  }
  void main(){
    int preorder[] = {1, 2, 4, 7, 3, 5, 6, 8};
    int num = sizeof(preorder) / sizeof(int);
    int inorder[] = {4, 7, 2, 1, 5, 3, 8, 6};
    Node* root = constructTree(preorder, inorder, num);
    printTree(root);
  }
};

TEST_F(Playground201910, TC16){
  TC16Solution s;
  s.main();
}

class TC17Solution {
  // 给定一颗二叉树和其中一个节点，如何找出中序遍历的下一个节点？
  // 《剑指Offer》面试题8
public:
  struct Node
  {
    Node *m_pLeft, *m_pRight, *m_pParent;
    char m_Value;
    Node(char value, Node* l=nullptr, Node *r=nullptr, Node* p=nullptr):
    m_pLeft(l), m_pRight(r), m_pParent(p), m_Value(value){}
  };
  Node* nextNode(Node* node){
    if(node->m_pRight != nullptr){
      Node* result = node->m_pRight;
      while(result->m_pLeft != nullptr){
        result = result->m_pLeft;
      }
      return result;
    }else if(node->m_pParent != nullptr){
      Node* parent = node->m_pParent;
      while(parent != nullptr){
        if(parent->m_pLeft == node){
          return parent;
        }else{
          node = parent;
          parent = parent->m_pParent;
        }
      }
      return nullptr;
    }
    return nullptr;
  }
  void main(){
    Node* l = new Node('h');
    Node* r = new Node('i');
    Node* p = new Node('e', l, r);
    l->m_pParent = p;
    r->m_pParent = p;

    r = p;
    l = new Node('d');
    p = new Node('b', l, r);
    l->m_pParent = p;
    r->m_pParent = p;

    l = p;
    r = new Node('c');
    Node *root = new Node('a', l, r);
    l->m_pParent = root;
    r->m_pParent = root;

    p = r;
    l = new Node('f');
    r = new Node('g');
    Node* objNode = r;
    p->m_pLeft = l;
    p->m_pRight = r;
    l->m_pParent = p;
    r->m_pParent = p;

    Node* nextNode = this->nextNode(objNode);
    if(nextNode != nullptr){
      LOG(INFO)<<"Next node of "<<objNode->m_Value<<" is:"<<nextNode->m_Value;
    }else{
      LOG(INFO)<<"Next node NOT exists!";
    }
  }
};

TEST_F(Playground201910, TC17){
  TC17Solution s;
  s.main();
}

class TC18Solution {
  // 改进的斐波那契算法
public:
  int fibonacci(int n){
    if(n == 0)
      return 0;
    if(n == 1)
      return 1;

    int fib1 = 0;
    int fib2 = 1;
    int fib = 0;
    for(int i=2; i<n; i++){
      fib = fib1 + fib2;
      fib2 = fib1;
      fib1 = fib;
    }
    return fib;

  }
  void main(){
    int n = 10;
    LOG(INFO)<<"fibonacci "<<n<<" is:"<<fibonacci(n);
  }
};

TEST_F(Playground201910, TC18){
  TC18Solution s;
  s.main();
}

class TC19Solution {
  // 实现快速排序算法
public:

  void quickSort(int *data, int num){
    if(num <= 1)
      return;

    int iLeft = 0;
    int iRight = num - 1;
    while(iLeft < iRight){
      while(data[iRight]>=data[0] && iLeft < iRight)
        iRight--;
      while(data[iLeft]<=data[0] && iLeft < iRight)
        iLeft++;
      if(iLeft != iRight){
        int tmp = data[iLeft];
        data[iLeft] = data[iRight];
        data[iRight] = tmp;
      }
    }
    int tmp = data[iLeft];
    data[iLeft] = data[0];
    data[0] = tmp;
    quickSort(data, iLeft);
    quickSort(data+iLeft+1, num - iLeft - 1);
  }

  void main(){
    int data[] = {6, 1, 2, 7, 9, 3, 4, 5, 10, 8};
    int num = sizeof(data) / sizeof(int);

    LOG(INFO)<<"to sort:";
    for(int i=0; i<num; i++){
      printf(" %d", data[i]);
    }
    printf("\n");

    quickSort(data, num);

    LOG(INFO)<<"sorted:";
    for(int i=0; i<num; i++){
      printf(" %d", data[i]);
    }
    printf("\n");
  }
};

TEST_F(Playground201910, TC19){
  TC19Solution s;
  s.main();
}

class TC20Solution {
  // 把一个数组最开始的若干个元素搬到数组末尾，称为数组的旋转。
  // 输入：一个递增数组的旋转，求改递增数组的最小元素。
  // 例如：递增数组{1, 2, 3, 4, 5}，其旋转为{3, 4, 5, 1, 2}，最小值为1
public:
  int minValue(int *data, int num){
    int l = 0;
    int r = num - 1;
    while(data[l]>data[r]){
      if(r - l == 1)
        return data[r];

      int mid = (l + r) / 2;
      if(data[mid]<data[r]){
        r = mid;
      }else if(data[mid]>data[l]){
        l = mid;
      }
    }
  }
  void main(){
    int data[] = {5, 6, 7, 8, 3, 4};
    int num = sizeof(data) / sizeof(int);
    LOG(INFO)<<minValue(data, num);
  }
};

TEST_F(Playground201910, TC20){
  TC20Solution s;
  s.main();
}

class TC21Solution {
  // 设计一个函数，用来判断在一个矩阵中是否存在一条包含字符串所有字符的路径。
  // 路径可以从矩阵任一格开始，每一步可以在矩阵中向上下左右移动一格。如果一
  // 条路径经过了矩阵的某一格，则该路径不能再次进入该格子。
public:
  bool hasPathCore(char* matrix, int row, int col, int rpos, int cpos, 
  char* str, int pathlen, bool* visited){
    if(str[pathlen] == '\0')
      return true;

    if (rpos >= 0 && cpos >= 0 && rpos < row & cpos < col &&
        matrix[rpos * col + cpos] == str[pathlen] &&
        visited[rpos * col + cpos] == false)
    {
      pathlen++;
      visited[rpos * row + cpos] = true;
      bool hasPath = hasPathCore(matrix, row, col, rpos + 1, cpos,
                                 str, pathlen, visited) ||
                     hasPathCore(matrix, row, col, rpos - 1, cpos,
                                 str, pathlen, visited) ||
                     hasPathCore(matrix, row, col, rpos, cpos + 1,
                                 str, pathlen, visited) ||
                     hasPathCore(matrix, row, col, rpos, cpos - 1,
                                 str, pathlen, visited);
      if(!hasPath){
        visited[rpos*row +cpos] = false;
      }else{
        return true;
      }
    }
    return false;
  }

  bool hasPath(char* matrix, int row, int col, char* str){
    if(matrix == nullptr || row < 1 || col < 1 || str == nullptr)
      return false;

    bool *visited = new bool[row * col];
    memset(visited, 0, row * col);
    int pathlen = 0;
    for(int i=0; i<row; i++){
      for(int j=0; j<col; j++){
        if(hasPathCore(matrix, row, col, i, j, str, pathlen, visited)){
          return true;
        }
      }
    }
    return false;
  }
  void main(){
    char matrix[3][4] = {
      {'a', 'b', 't', 'g'},
      {'c', 'f', 'c', 's'},
      {'j', 'd', 'e', 'h'},
    };
    // LOG(INFO)<<"has path:"<<hasPath(&matrix[0][0], 3, 4, "bfce");
    LOG(INFO)<<"has path:"<<hasPath(&matrix[0][0], 3, 4, "bfcj");
    // LOG(INFO)<<"has path:"<<hasPath(&matrix[0][0], 3, 4, "acj");
  }
};

TEST_F(Playground201910, TC21){
  TC21Solution s;
  s.main();
}

class TC22Solution {
  // 地上有一个m行n列的方格。一个机器人从坐标(0, 0)的格子开始移动，他每次可以向上下左右
  // 移动一格，但不能进入行、列坐标数位之和大于k的格子。
  // 例如，当k=18时，机器人能进入(35, 37)，3+5+3+7=18，但不能进入方格(35, 38)，
  // 3+5+3+8=19。
  // 请问机器人能够到达多少个格子？
public:
  int movingCount(int threshold, int row, int col){
    if(threshold < 0 || row<=0 || col <=0)
      return 0;
    bool *visited = new bool[row*col];
    for(int i=0; i<row*col; i++)
      visited[i] = false;
    int count = movingCountCore(threshold, row, col, 0, 0, visited);
    delete []visited;
    return count;
  }

  int getDigitSum(int pos){
    int sum = 0;
    while(pos>0){
      sum += pos % 10;
      pos = pos / 10;
    }
    return sum;
  }

  bool checkPos(int rpos, int cpos, int row, int col, int threshold,
                bool *visited)
  {
    if (rpos >= 0 && cpos >= 0 && rpos < row && cpos < col &&
        !visited[rpos * col + cpos] &&
        getDigitSum(rpos) + getDigitSum(cpos) <= threshold)
      return true;
    return false;
  }

  int movingCountCore(int threshold, int row, int col,
                      int rpos, int cpos, bool *visited)
  {
    if (checkPos(rpos, cpos, row, col, threshold, visited))
    {
      LOG(INFO)<<"visit (" <<rpos<<","<<cpos<<")";
      visited[rpos * col + cpos] = true;
      return 1 + movingCountCore(threshold, row, col, 
      rpos, cpos + 1, visited) + 
      movingCountCore(threshold, row, col, 
      rpos + 1, cpos, visited) + 
      movingCountCore(threshold, row, col, 
      rpos, cpos - 1, visited) + 
      movingCountCore(threshold, row, col, 
      rpos - 1, cpos, visited);
    }

    return 0;
  }

  void main(){
    LOG(INFO)<<"moving count:"<<movingCount(5, 4, 4);
  }
};

TEST_F(Playground201910, TC22){
  TC22Solution s;
  s.main();
}

class TC23Solution {
  // 给你一根长度为n的绳子，请把绳子剪成m段（m、n都是整数，n>1,m>1），
  // 每段绳子的长度记为k[0], k[1], ..., k[m]。请问
  // k[0]×k[1]×...×k[m]可能的最大乘积是多少？
public:
  int maxProduct(int length){
    if(length < 2)
      return 0;
    if(length == 2)
      return 1;
    if(length == 3)
      return 2;
    int* product = new int[length+1];
    memset(product, sizeof(int), length+1);
    product[0] = 0;
    product[1] = 1;
    product[2] = 2;
    product[3] = 3;
    int max = 0;
    for(int i=4; i<=length; i++){
      max = 0;
      for(int j=1; j<=i/2; j++){
        int tmp = product[j]*product[i-j];
        if(tmp>max)
          max =tmp;
      }
      product[i] = max;
    }
    max = product[length];
    delete[] product;
    return max;
  }
  void main(){
    int length = 50;
    LOG(INFO)<<"max product of "<<length<<" is:"<<maxProduct(length);
  }
};

TEST_F(Playground201910, TC23){
  TC23Solution s;
  s.main();
}

class TC24Solution {
  // 请实现一个函数：输入一个整数，输出该整数中1的个数。
public:
  int CountOf1(int num){
    int count = 0;
    int flag = 1;
    while(flag){
      if(num&flag)
        count++;
      flag = flag<<1;
    }
    return count;
  }
  void main(){
    int x = -1;
    printf("----%X\n", (x));
    int num = 9;
    LOG(INFO)<<"The number "<<num<<"'s count 1 is:"<<CountOf1(num);
  }
};

TEST_F(Playground201910, TC24){
  TC24Solution s;
  s.main();
}

class TC25Solution {
  // 实现函数double Power(double base, int exponent)，
  // 求base的exponent次方。
public:
  int m_InvalidCalc;
  double PowerWithUnsignedExp(double base, unsigned int exponent){
    if(exponent == 0)
      return 1;
    if(exponent == 1)
      return base;
    double result = PowerWithUnsignedExp(base, exponent>>1);
    result *= result;
    if(exponent & 0x01 == 0x01)
      result *= base;
    return result;
  }
  double Power(double base, int exponent){
    m_InvalidCalc = 0;
    unsigned int unsignedExponent = exponent;
    if (exponent < 0)
    {
      if(base == 0){
        m_InvalidCalc = -1;
        return 0;
      }
      unsignedExponent = -exponent;
    }
    double result = PowerWithUnsignedExp(base, unsignedExponent);
    if(exponent<0)
      result = 1 / result;
    return result;
  }
  void main(){
    double base = 2.0;
    int exponent = 8;
    LOG(INFO)<<"base="<<base<<", exp="<<exponent<<", result="<<Power(base, exponent);
  }
};

TEST_F(Playground201910, TC25){
  TC25Solution s;
  s.main();
}

class TC26Solution {
  // 输入数字n，按顺序打印出从1到最大的n位十进制数
public:
  bool Inc(char* number){
    bool overflow = false;
    int takeover = 0;
    int length = strlen(number);
    for (int i = length - 1; i >= 0; i--)
    {
      int sum = number[i] - '0' + takeover;
      if (i == length - 1)
        sum++;
      if (sum >= 10)
      {
        if (i == 0)
          return true;
        else
        {
          sum -= 10;
          takeover = 1;
          number[i] = sum + '0';
        }
      }
      else
      {
        number[i] = sum + '0';
        break;
      }
    }
    return overflow;
  }
  void Print1ToMaxOfNDigits(int n){
    if(n<=0)
      return;
    char* number = new char[n+1];
    memset(number, '0', n);
    number[n] = '\0';
    while(!Inc(number)){
      printf(" %s", number);
      if(number[strlen(number)-1] == '0')
        printf("\n");
    }
    printf("\n");
  }
  void main(){
    Print1ToMaxOfNDigits(3);
  }
};

TEST_F(Playground201910, TC26){
  TC26Solution s;
  s.main();
}


class TC27Solution {
  // 请实现一个函数用来匹配包含'.'和'*'的正则表达式。
  // 模式中的'.'表示任意一个字符，'*'表示它前面的字符可以出现任意次
public:
  bool matchCore(char* str, char* pattern){
    if(*str == '\0' && *pattern == '\0')
      return true;
    if(*str != '\0' && *pattern == '\0')
      return false;

    if(*(pattern+1) == '*'){
      if (*pattern == *str || (*pattern == '.' && *str != '\0'))
      {
        return matchCore(str + 1, pattern + 2) ||
               matchCore(str + 1, pattern);
      }else{
        return matchCore(str, pattern+2);
      }
    }
    if(*str==*pattern || (*pattern=='.' && *str!= '\0'))
      return matchCore(str+1, pattern+1);
    return false;
  }
  bool match(char* str, char* pattern){
    if(str == nullptr || pattern == nullptr)
      return false;
    return matchCore(str, pattern);
  }
  void main(){
    char* str = "abbbbc";
    char* pattern = "ab*c";
    LOG(INFO)<<"str:"<<str<<" pattern:"<<pattern<<" matched("<<match(str, pattern)<<")";
  }
};

TEST_F(Playground201910, TC27){
  TC27Solution s;
  s.main();
}


class TC28Solution {
  // 输入两棵二叉树A和B，判断B是不是A的子结构。
  struct Node{
    int m_Value;
    Node *m_pLeft, *m_pRight;
    Node(int value, Node* pLeft=nullptr, Node* pRight=nullptr):
    m_Value(value), m_pLeft(pLeft), m_pRight(pRight){}
  };
public:
  bool hasSubTreeCore(Node* a, Node* b){
    if(b == nullptr)
      return true;
    if(a == nullptr)
      return false;
    if(a->m_Value != b->m_Value)
      return false;
    return hasSubTreeCore(a->m_pLeft, b->m_pLeft) &&
    hasSubTreeCore(a->m_pRight, b->m_pRight);
  }
  bool hasSubTree(Node* a, Node* b){
    bool result = false;
    if(a!=nullptr && b!=nullptr){
      if(a->m_Value==b->m_Value)
        result = hasSubTreeCore(a, b);
      if(!result)
        result = hasSubTree(a->m_pLeft, b);
      if(!result)
        result = hasSubTree(a->m_pRight, b);
    }
    return result;
  }
  void main(){
    Node* l = new Node(4);
    Node* r = new Node(7);
    Node* p = new Node(2, l, r);
    r = p;
    l = new Node(9);
    p = new Node(8, l, r);
    l = p;
    r = new Node(7);
    p = new Node(8, l, r);
    Node *A = p;

    l = new Node(9);
    r = new Node(2);
    p = new Node(8, l, r);
    Node *B = p;
    LOG(INFO)<<"====>"<<hasSubTree(A, B);
  }
};

TEST_F(Playground201910, TC28){
  TC28Solution s;
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
