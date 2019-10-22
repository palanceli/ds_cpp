#include "stdio.h"
#include <string.h>
#include <iostream>
#include <gtest/gtest.h>
#include <algorithm>
#include "glog/logging.h"
#include <deque>
#include <stack>
#include <climits>

// ./ds_cpp --gtest_filter=JZOffer.TC02
class JZOffer : public testing::Test{
  
protected:
  static void SetUpTestCase(){
    FLAGS_logtostderr = 1; // 输出到控制台
    setlocale(LC_ALL, "");
  }
  static void TearDownTestCase(){
  }
  
};

class TC01Solution
{
  // 定义并实现赋值运算函数
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

TEST_F(JZOffer, TC01){
  TC01Solution s;
  s.main();
}

class TC03Solution {
  // 在长度为n的数组里，所有数字都∈[0, n-1]数组内某些数字是重复的，但不知道
  // 有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任一个重复的数字。
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

TEST_F(JZOffer, TC03){
  TC03Solution s;
  s.main();
}


class TC03BSolution {
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

TEST_F(JZOffer, TC03B){
  TC03BSolution s;
  s.main();
}

class TC05Solution {
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

TEST_F(JZOffer, TC05){
  TC05Solution s;
  s.main();
}

class TC05BSolution {
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

TEST_F(JZOffer, TC05B){
  TC05BSolution s;
  s.main();
}

class TC06Solution {
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

TEST_F(JZOffer, TC06){
  TC06Solution s;
  s.main();
}

class TC07Solution {
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

TEST_F(JZOffer, TC07){
  TC07Solution s;
  s.main();
}

class TC08Solution {
  // 给定一颗二叉树和其中一个节点，如何找出中序遍历的下一个节点？
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

TEST_F(JZOffer, TC08){
  TC08Solution s;
  s.main();
}

class TC10Solution {
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

TEST_F(JZOffer, TC10){
  TC10Solution s;
  s.main();
}

class TC11ASolution {
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

TEST_F(JZOffer, TC11A){
  TC11ASolution s;
  s.main();
}

class TC11Solution {
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

TEST_F(JZOffer, TC11){
  TC11Solution s;
  s.main();
}

class TC12Solution {
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

TEST_F(JZOffer, TC12){
  TC12Solution s;
  s.main();
}

class TC13Solution {
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

TEST_F(JZOffer, TC13){
  TC13Solution s;
  s.main();
}

class TC14Solution {
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

TEST_F(JZOffer, TC14){
  TC14Solution s;
  s.main();
}

class TC15Solution {
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

TEST_F(JZOffer, TC15){
  TC15Solution s;
  s.main();
}

class TC16Solution {
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

TEST_F(JZOffer, TC16){
  TC16Solution s;
  s.main();
}

class TC17Solution {
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

TEST_F(JZOffer, TC17){
  TC17Solution s;
  s.main();
}


class TC19Solution {
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

TEST_F(JZOffer, TC19){
  TC19Solution s;
  s.main();
}


class TC26Solution {
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

TEST_F(JZOffer, TC26){
  TC26Solution s;
  s.main();
}

template <typename T>
struct BinaryTreeNode
{
  BinaryTreeNode *m_pLeft, *m_pRight;
  T m_Value;
  BinaryTreeNode(T value, BinaryTreeNode *left = nullptr,
                 BinaryTreeNode *right = nullptr) : m_Value(value),
                                                    m_pLeft(left),
                                                    m_pRight(right)
  {
  }

  static void preorderCore(BinaryTreeNode<T> *node, std::ostringstream &oss)
  {
    if(node == nullptr)
      return;
    oss<<" "<<node->m_Value;
    preorderCore(node->m_pLeft, oss);
    preorderCore(node->m_pRight, oss);
  }
  static void PrintPreOrder(BinaryTreeNode<T> *root, std::string &preorder)
  {
    std::ostringstream oss;
    preorderCore(root, oss);
    LOG(INFO)<<"Pre order:"<< oss.str();
  }
};

// 请完成一个函数，输入一棵二叉树，该函数输出它的镜像
class TC27Solution {
  typedef BinaryTreeNode<int> Node;

public:
  void mirrorTree(Node* root){
    if(root == nullptr)
      return;
    Node* tmp = root->m_pLeft;
    root->m_pLeft = root->m_pRight;
    root->m_pRight = tmp;
    mirrorTree(root->m_pLeft);
    mirrorTree(root->m_pRight);
  }
  void main(){
    Node* l = new Node(5);
    Node* r = new Node(7);
    Node* root = new Node(6, l, r);
    l = new Node(9);
    r = new Node(11);
    Node* p = new Node(10, l, r);
    l = root;
    r = p;
    root = new Node(8, l, r);
    std::string preorder;
    Node::PrintPreOrder(root, preorder);

    mirrorTree(root);
    Node::PrintPreOrder(root, preorder);
  }
};

TEST_F(JZOffer, TC27){
  TC27Solution s;
  s.main();
}

// 如果二叉树和它的镜像一样，则该二叉树是对称的。请实现一个函数，用来判断一颗二叉树是不是对称的。
class TC28Solution {
  typedef BinaryTreeNode<int> Node;
public:
  bool isSymmetrical(Node* root)
  {
    return isSymmetrical(root, root);
  }
  bool isSymmetrical(Node *p1, Node *p2)
  {
    if (p1 == nullptr && p2 == nullptr)
      return true;
    if (p1 == nullptr || p2 == nullptr)
      return false;
    if (p1->m_Value != p2->m_Value)
      return false;
    return isSymmetrical(p1->m_pLeft, p2->m_pRight) &&
           isSymmetrical(p1->m_pRight, p2->m_pLeft);
  }
  void tree1(){
    Node* l = new Node(5);
    Node* r = new Node(7);
    Node* p = new Node(6, l, r);
    Node* root = p;
    l = new Node(7);
    r = new Node(5);
    p = new Node(6, l, r);
    l = root;
    r = p;
    root = new Node(8, l, r);
    LOG(INFO)<<"is symetrical:"<<isSymmetrical(root);
  }
  void tree2(){
    Node* l = new Node(5);
    Node* r = new Node(7);
    Node* p = new Node(6, l, r);
    Node* root = p;
    l = new Node(7);
    r = new Node(5);
    p = new Node(9, l, r);
    l = root;
    r = p;
    root = new Node(8, l, r);
    LOG(INFO)<<"is symetrical:"<<isSymmetrical(root);
  }
  void tree3(){
    Node* l = new Node(7);
    Node* r = new Node(7);
    Node* p = new Node(7, l, r);
    Node* root = p;
    l = new Node(7);
    p = new Node(7, l, nullptr);
    l = root;
    r = p;
    root = new Node(7, l, r);
    LOG(INFO)<<"is symetrical:"<<isSymmetrical(root);
  }
  void main(){
    tree1();
    tree2();
    tree3();
  }
};

TEST_F(JZOffer, TC28){
  TC28Solution s;
  s.main();
}

// 输入一个矩阵，按照从外向里以顺时针的顺序依次打印每个数字
class TC29Solution {
public:
  void printMatrixCicle(int *data, int row, int col, int start){
    int endX = col - start;
    int endY = row - start;
    // →
    for (int i = start; i < endX; i++)
    {
      printf(" %d", data[start * col + i]);
    }
    // ↓
    for (int i = start + 1; i < endY; i++)
    {
      printf(" %d", data[i * col + endX - 1]);
    }
    // ←
    for (int i = endX - 2; i >= start; i--)
    {
      printf(" %d", data[(endY - 1) * col + i]);
    }
    // ↑
    for (int i = endY - 2; i > start; i--)
    {
      printf(" %d", data[i * col + start]);
    }

    printf("\n");
  }
  void printMatrixClockwisly(int *data, int row, int col){
    if(data == nullptr)
      return;
    int start = 0;
    while(col > start *2 && row > start *2 )
      printMatrixCicle(data, row, col, start++);
  }
  void matrix1(){
    int data[4][5] = {
      {1,   2,  3,  4,  5},
      {14, 15, 16, 17,  6},
      {13, 20, 19, 18,  7},
      {12, 11,  10, 9,  8},
    };
    printMatrixClockwisly(&data[0][0], 4, 5);
  }
  void matrix2(){
    int data[5][5] = {
      {1,   2,  3,  4,  5},
      {16, 17, 18, 19,  6},
      {15, 24, 25, 20,  7},
      {14, 23, 22, 21,  8},
      {13, 12, 11, 10,  9},
    };
    printMatrixClockwisly(&data[0][0], 5, 5);
  }
  void main(){
    matrix1();
    matrix2();
  }
};

TEST_F(JZOffer, TC29){
  TC29Solution s;
  s.main();
}

// 输入两个整数序列，第一个表示栈的压入顺序，请判断第二个序列是否为该栈
// 的弹出序列。
class TC31Solution {
  template<typename T>
  class Stack
  {
    private:
      T *m_data;
      int m_size;
      int m_top;
    public:
      Stack():m_size(128),m_top(0)
      {
        m_data = new T[m_size];
      }
      T Top()
      {
        if(m_top<=0){
          return T();
        }
        return m_data[m_top-1];
      }
      T Pop()
      {
        if(m_top<=0){
          return T();
        }
        return m_data[--m_top];
      }
      void Push(T t)
      {
        if(m_top>=m_size)
          return;
        m_data[m_top++] = t;
      }
      bool Empty()
      {
        return m_top == 0;
      }
  };
public:
  bool isPopOrder(const int* push, const int* pop, int len)
  {
    Stack<int> stack;
    if(push==nullptr || pop==nullptr || len <= 0)
      return false;
    int pushPos = 0;
    int popPos = 0;
    while(popPos<len){
      while(stack.Empty() || stack.Top() != pop[popPos]){
        if(pushPos >= len)
          return false;
        stack.Push(push[pushPos++]);
      }
      stack.Pop();
      popPos++;
    }
    if(pushPos == len && popPos== len)
      return true;
    
    return false;
  }
  void main(){
    int push[] = {1, 2, 3, 4, 5};
    int pop[] = {3, 4, 2, 1, 5};
    int num = sizeof(push) / sizeof(int);
    LOG(INFO)<<"is pop order:"<<isPopOrder(push, pop, num);
  }
};

TEST_F(JZOffer, TC31){
  TC31Solution s;
  s.main();
}

// 从上到下打印出二叉树每层节点，每层节点按照从左到右的顺序打印。
class TC32Solution {
  typedef BinaryTreeNode<int> Node;
public:
  void printTopDown(Node* root){
    if(root == nullptr)
      return;
    std::deque<Node*> deque;
    deque.push_back(root);
    while(!deque.empty()){
      Node* node = deque.front();
      deque.pop_front();
      printf(" %d", node->m_Value);
      if(node->m_pLeft != nullptr)
        deque.push_back(node->m_pLeft);
      if(node->m_pRight != nullptr)
        deque.push_back(node->m_pRight);
    }
    printf("\n");
  }

  // 打印一层之后换行
  void printTopDownWithWrap(Node* root){
    if(root == nullptr)
      return;
    std::deque<Node*> deque;
    deque.push_back(root);
    int cCurrentLine = 1;
    int cNextLine = 0;
    while(!deque.empty()){
      Node* node = deque.front();
      deque.pop_front();
      cCurrentLine--;

      printf(" %d", node->m_Value);
      if(node->m_pLeft != nullptr){
        deque.push_back(node->m_pLeft);
        cNextLine++;
      }
      if(node->m_pRight != nullptr){
        deque.push_back(node->m_pRight);
        cNextLine++;
      }
      if(cCurrentLine == 0){
        cCurrentLine = cNextLine;
        cNextLine = 0;
        printf("\n");
      }
    }
    printf("\n");
  }

  // Z字型打印
  void printTopDownForZ(Node* root){
    if(root == nullptr)
      return;
    std::stack<Node*> stack1, stack2;
    stack2.push(root);
    int cCurrentLine = 1;
    int cNextLine = 0;
    bool left2rigth = true;
    while(!stack1.empty() || !stack2.empty()){
      Node* node = nullptr;
      if(left2rigth){
        node = stack2.top();
        stack2.pop();
      }
      else{
        node = stack1.top();
        stack1.pop();
      }
      cCurrentLine--;

      printf(" %d", node->m_Value);
      if (left2rigth)
      {
        if (node->m_pLeft != nullptr)
        {
          stack1.push(node->m_pLeft);
          cNextLine++;
        }
        if (node->m_pRight != nullptr)
        {
          stack1.push(node->m_pRight);
          cNextLine++;
        }
      }else{
        if (node->m_pRight != nullptr)
        {
          stack2.push(node->m_pRight);
          cNextLine++;
        }
        if (node->m_pLeft != nullptr)
        {
          stack2.push(node->m_pLeft);
          cNextLine++;
        }
      }
      if(cCurrentLine == 0){
        cCurrentLine = cNextLine;
        cNextLine = 0;
        printf("\n");
        left2rigth = !left2rigth;
      }
    }
    printf("\n");
  }

  void main(){
    Node* l = new Node(4);
    Node* r = new Node(5);
    Node* root = new Node(2, l, r);
    l = new Node(6);
    r = new Node(7);
    Node* p = new Node(3, l, r);
    l = root;
    r = p;
    root = new Node(1, l, r);
    printTopDownForZ(root);
  }
};

TEST_F(JZOffer, TC32){
  TC32Solution s;
  s.main();
}

// 输入整数数组，判断该数组是不是某二叉搜索树后序遍历的结果。
class TC33Solution {
public:
  bool verifySquenceOfBST(int *data, int num){
    if(data == nullptr || num == 0)
      return false;
    int root = data[num - 1];
    int pos = 0;
    for(; pos<num-1; pos++){
      if(data[pos]>root)
        break;
    }
    for(int j=pos; j<num-1; j++){
      if(data[j]<root)
        return false;
    }
    bool left = true;
    if(pos>0){
      left = verifySquenceOfBST(data, pos);
    }
    bool right = true;
    if(pos<num -1){
      right = verifySquenceOfBST(data+pos, num-pos-1);
    }

    return (left && right);
  }
  void main(){
    // int data[] = {5, 7, 9, 11, 10, 8};
    int data[] = {7, 4, 6, 5};
    int num = sizeof(data) / sizeof(int);
    LOG(INFO)<<"squence of BST:"<<verifySquenceOfBST(data, num);
  }
};

TEST_F(JZOffer, TC33){
  TC33Solution s;
  s.main();
}

// 输入一棵二叉树和一个整数，打印二叉树中节点值的和为整数的所有路径。
class TC34Solution {
  typedef BinaryTreeNode<int> Node;
public:
  void FindPath(Node* root, int expectSum, int currSum, std::vector<int> &path)
  {
    currSum += root->m_Value;
    path.push_back(root->m_Value);
    
    bool isLeaf = (root->m_pLeft == nullptr && root->m_pRight == nullptr);
    if(isLeaf && currSum == expectSum){
      for(std::vector<int>::iterator itor=path.begin(); itor!=path.end(); itor++){
        printf(" %d", *itor);
      }
      printf("\n");
    }
    if(root->m_pLeft != nullptr)
      FindPath(root->m_pLeft, expectSum, currSum, path);
    if(root->m_pRight != nullptr)
      FindPath(root->m_pRight, expectSum, currSum, path);
    
    path.pop_back();
  }

  void FindPath(Node* root, int sum){
    if(root == nullptr|| sum == 0)
      return;
    std::vector<int> path;
    int currSum = 0;
    FindPath(root, sum, currSum, path);
  }
  void main(){
    Node* l = new Node(4);
    Node* r = new Node(7);
    Node* root = new Node(5, l, r);
    l = root;
    r = new Node(12);
    root = new Node(10, l, r);
    int sum = 22;
    FindPath(root, sum);
  }
};

TEST_F(JZOffer, TC34){
  TC34Solution s;
  s.main();
}

// 实现函数克隆一个复杂链表，该复杂链表除了每个节点有一个pNext指针指向下一个
// 节点，还有一个pSibling指针指向链表的任意节点。
class TC35Solution {
  struct ComplexListNode
  {
    int m_Value;
    ComplexListNode* m_pNext;
    ComplexListNode* m_pSibling;
    ComplexListNode(int value, ComplexListNode* pNext =nullptr, 
    ComplexListNode* pSibling=nullptr):m_Value(value), 
    m_pNext(pNext), m_pSibling(pSibling){}
  };
public:
  void printList(ComplexListNode* head){
    for(; head!=nullptr; head = head->m_pNext){
      if(head->m_pSibling != nullptr){
        printf(" %d(%d)", head->m_Value, head->m_pSibling->m_Value);
      }else{
        printf(" %d", head->m_Value);
      }
    }
    printf("\n");
  }
  ComplexListNode* cloneList(ComplexListNode* head){
    if(head == nullptr)
      return nullptr;
    ComplexListNode* node = head;
    while(node != nullptr){
      ComplexListNode* nodeShadow = new ComplexListNode(
        node->m_Value, node->m_pNext, node->m_pSibling);
      node->m_pNext = nodeShadow;
      node = nodeShadow->m_pNext;
    }
    ComplexListNode* headShadow = head->m_pNext;
    node = head;
    while(node != nullptr){
      ComplexListNode* nodeShadow = node->m_pNext;
      node->m_pNext = nodeShadow->m_pNext;

      if(nodeShadow->m_pNext != nullptr)
        nodeShadow->m_pNext = nodeShadow->m_pNext->m_pNext;
      if(nodeShadow->m_pSibling != nullptr)
        nodeShadow->m_pSibling = nodeShadow->m_pSibling->m_pNext;
      
      node = node->m_pNext;
    }
    return headShadow;
  }
  void main(){
    ComplexListNode* e = new ComplexListNode(5);
    ComplexListNode* d = new ComplexListNode(4, e);
    ComplexListNode* c = new ComplexListNode(3, d);
    ComplexListNode* b = new ComplexListNode(2, c, e);
    ComplexListNode* a = new ComplexListNode(1, b, c);
    d->m_pSibling = b;
    printList(a);
    ComplexListNode* a2 = cloneList(a);
    printList(a2);
  }
};

TEST_F(JZOffer, TC35){
  TC35Solution s;
  s.main();
}

// 输入一颗二叉搜索树，将该树转换成一个排序的双向链表。
// 要求不能创建新节点。
class TC36Solution {
  typedef BinaryTreeNode<int> Node;
public:
  void convert(Node* node, Node** lastNode){
    if(node == nullptr)
      return;
    if(node->m_pLeft != nullptr)
      convert(node->m_pLeft, lastNode);

    if(*lastNode != nullptr){
      (*lastNode)->m_pRight = node;
    }
    *lastNode = node;
    if(node->m_pRight != nullptr)
      convert(node->m_pRight, lastNode);
  }
  Node* Convert(Node* root){
    if(root == nullptr)
      return nullptr;
    Node* lastnode = nullptr;
    convert(root, &lastnode);
    Node* head = root;
    while(head->m_pLeft != nullptr){
      head = head->m_pLeft;
    }
    return head;
  }
  void main(){
    Node *l = new Node(4);
    Node *r = new Node(8);
    Node *root = new Node(6, l, r);
    l = new Node(12);
    r = new Node(16);
    Node *p = new Node(14, l, r);
    l = root;
    r = p;
    root = new Node(10, l, r);
    Node *head = Convert(root);
    for(; head!=nullptr; head= head->m_pRight){
      printf(" %d", head->m_Value);
    }
    printf("\n");
  }
};

TEST_F(JZOffer, TC36){
  TC36Solution s;
  s.main();
}

// 实现两个函数分别用来序列化和反序列化二叉树
class TC37Solution {
  typedef BinaryTreeNode<char> Node;
public:
  void Serialize(Node* root){
    if(root == nullptr)
      return;
    printf(" %c", root->m_Value);
    if(root->m_pLeft != nullptr)
      Serialize(root->m_pLeft);
    else
      printf(" $");

    if(root->m_pRight != nullptr)
      Serialize(root->m_pRight);
    else
      printf(" $");
  }
  void ProcSerialize(){
    Node *l = new Node('4');
    Node *root = new Node('2', l);
    l = new Node('5');
    Node *r = new Node('6');
    Node *p = new Node('3', l, r);
    l = root;
    r = p;
    root = new Node('1', l, r);
    Serialize(root);
    printf("\n");
  }
  void Deserialize(Node **node, char* data, int &pos){
    if(pos>= strlen(data) || data[pos] == '$')
      return;
    *node = new Node(data[pos]);
    Deserialize(&(*node)->m_pLeft, data, ++pos);
    Deserialize(&(*node)->m_pRight, data, ++pos);
  }
  void ProcDeserialize(){
    char* data = "124$$$35$$6$$";
    Node *head;
    int pos = 0;
    Deserialize(&head, data, pos);
    LOG(INFO)<<"OK";
  }
  void main(){
    ProcSerialize();
    ProcDeserialize();
  }
};

TEST_F(JZOffer, TC37){
  TC37Solution s;
  s.main();
}

// 输入一个字符串，打印出该字符串中所有字符的全排列
class TC38Solution {
public:
  void Permutation(char* pstr, char* begin){
    if(*begin == '\0'){
      printf("%s\n", pstr);
      return;
    }
    for(char* ch=begin; *ch!='\0'; ch++){
      char tmp = *ch;
      *ch = *begin;
      *begin = tmp;
      
      Permutation(pstr, begin+1);
      
      tmp = *ch;
      *ch = *begin;
      *begin = tmp;
    }
  }
  void Permutation(char* pstr){
    if(pstr == nullptr)
      return;
    Permutation(pstr, pstr);
  }
  void main(){
    char data[] = "abcde";
    Permutation(data);
  }
};

TEST_F(JZOffer, TC38){
  TC38Solution s;
  s.main();
}

// 数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字
class TC39Solution {
public:
  int moreThanHalfNum(int *data, int cnt){
    if(data == nullptr || cnt == 0)
      return 0;
    int num = data[0];
    int times = 1;
    for(int i=1; i<cnt; i++){
      if(data[i] == num)
        times++;
      else
        times--;
    }
    return num;
  }
  void main(){
    int data[] = {1, 2, 1, 3, 1, 4, 1, 1, 5, 1, 1, 5, 7};
    int cnt = sizeof(data) / sizeof(int);
    LOG(INFO)<<"more than half num is: "<<moreThanHalfNum(data, cnt);
  }
};

TEST_F(JZOffer, TC39){
  TC39Solution s;
  s.main();
}

// 输入一个整形数组，里面有正数也有负数，求所有子数组的和的最大值。
class TC42Solution {
public:
  int findMaxSumOfSubArray(int *array, int num){
    if(array == nullptr || num == 0)
      return 0;
    int maxSum = LONG_MIN;
    int currSum = 0;
    for(int i=0; i<num; i++){
      if(currSum < 0){
        currSum = array[i];
      }else{
        currSum += array[i];
        if(maxSum < currSum)
          maxSum = currSum;
      }
    }
    return maxSum;
  }
  void main(){
    int data[] = {1, -2, 3, 10, -4, 7, 2, -5};
    int cnt = sizeof(data) / sizeof(int);
    LOG(INFO)<<"greatest sum of sub array is:"<<findMaxSumOfSubArray(data, cnt);
  }
};

TEST_F(JZOffer, TC42){
  TC42Solution s;
  s.main();
}

// 给定一个数字，按照如下规则把它翻译为字符串：
// 0->a, 1->b, 2->c, ..., 11->l, ..., 25->z
// 一个数字可能有多个翻译，如12258有5中不同的翻译，分别是：
// bccfi, bwfi, bczi, mcfi和mzi。
// 请实现一个函数，用来计算一个数字有多少种不同的翻译方法。
class TC46Solution {
public:
  int getTranslationCount(const char* str){
    if(str == nullptr)
      return 0;
    int len = strlen(str);
    if(len == 0)
      return 0;

    int *counts = new int[len];
    for(int i=len-1; i>=0; i--){
      if(i==len-1)
        counts[i] = 1;
      else{
        int count = counts[i+1];
        int num = (str[i] - '0') * 10 + (str[i+1] - '0');
        if(num >= 10 && num <= 25){
          if(i<len-2)
            count += counts[i+2];
          else
            count += 1;
        }
        counts[i] = count;
      }
    }
    int result = counts[0];
    delete [] counts;
    return result;
  }
  int getTranslationCount(int num)
  {
    if(num < 0)
      return 0;
    char str[64] = {0};
    sprintf(str, "%d", num);
    return getTranslationCount(str);
  }
  void main(){
    int num = 12258;
    LOG(INFO)<<num<<" translation num="<<getTranslationCount(num);
  }
};

TEST_F(JZOffer, TC46){
  TC46Solution s;
  s.main();
}

// 在一个m×n的棋盘的每一格都放一个礼物，每个礼物有一定的价值。你可以从棋盘的左上角
// 开始拿礼物，每次向右或向下移动一格，直到到达棋盘右下角。给定一个棋盘及上面的礼物，
// 请计算最多能拿到多少价值的礼物。
class TC47Solution {
public:
  int getMaxValue(int *values, int row, int col){
    int *maxValue = new int[row * col];
    for(int i=0; i<row; i++){
      for(int j=0; j<col; j++){
        if(i == 0 && j == 0){
          maxValue[i * col + j] = values[i * col + j];
        }else if(i == 0){
          maxValue[i * col + j] = values[i * col + j] + maxValue[i * col + j - 1];
        }else if(j== 0){
          maxValue[i * col + j] = values[i * col + j] + maxValue[(i - 1) * col + j];
        }else{
          int up = maxValue[(i-1) * col + j];
          int left = maxValue[i * col + j - 1];
          maxValue[i * col + j] = values[i * col + j] + std::max(up, left);
        }
      }
    }
    int result = maxValue[row * col - 1];
    delete [] maxValue;
    return result;
  }
  void main(){
    int values[4][4] = {
      { 1, 10,  3,  8},
      {12,  2,  9,  6},
      { 5,  7,  4, 11},
      { 3,  7, 16,  5},
    };
    int result = getMaxValue(&values[0][0], 4, 4);
    LOG(INFO)<<"max value="<<result;
    EXPECT_EQ(53, result);
  }
};

TEST_F(JZOffer, TC47){
  TC47Solution s;
  s.main();
}

// 请从字符串中找出一个最长的不包含重复字符的子串，计算该子串的长度。假设
// 字符串中只包含a~z的字符。例如：arabcacfr中，该子串是acfr，长度为4。
class TC48Solution {
public:
  int longestSubStrLengthWithouDup(const char* str){
    int position[26] = {-1};
    int maxLength = 0;
    int currLength = 0;
    for(int i=0; i<strlen(str); i++){
      int prevPos = position[str[i] - 'a'];
      if(prevPos == -1 || (i - prevPos) > currLength)
        currLength++;
      else{
        currLength = i - prevPos;
      }
      position[str[i] - 'a'] = i;
      if(maxLength < currLength)
        maxLength = currLength;
    }
    return maxLength;
  }
  void main(){
    char *data = "arabcacfr";
    LOG(INFO)<<"longest sub string length without dup is:"<<longestSubStrLengthWithouDup(data);
  }
};

TEST_F(JZOffer, TC48){
  TC48Solution s;
  s.main();
}

class TC49Solution {
public:
  int getUglyNum(int index){
    int *uglyNums = new int[index];
    uglyNums[0] = 1;
    int *uglyNum2 = uglyNums;
    int *uglyNum3 = uglyNums;
    int *uglyNum5 = uglyNums;
    int nextIndex = 1;
    while(nextIndex<index){
      int min = std::min(std::min(*uglyNum2*2, *uglyNum3*3), *uglyNum5*5);
      uglyNums[nextIndex] = min;
      while(*uglyNum2 * 2 <= uglyNums[nextIndex])
        uglyNum2++;
      while(*uglyNum3 * 3 <= uglyNums[nextIndex])
        uglyNum3++;
      while(*uglyNum5 * 5 <= uglyNums[nextIndex])
        uglyNum5++;
      nextIndex++;
    }
    int result = uglyNums[index - 1];
    delete []uglyNums;
    return result;
  }

  void main(){
    int index = 1400;
    int uglyNum = getUglyNum(index);
    LOG(INFO)<<"the "<<index<<" ugly num is:"<< uglyNum;
    ASSERT_EQ(516560652, uglyNum);
  }
};

TEST_F(JZOffer, TC49){
  TC49Solution s;
  s.main();
}

// 在字符串中找到第一个只出现一次的字符。
class TC50Solution {
public:
  char findNotRepeatedChar(const char* str){
    char hash[256] = {0};
    for(const char *ch=str; *ch!='\0'; ch++){
      hash[*ch]++;
    }
    for(const char *ch=str; *ch!='\0'; ch++){
      if(hash[*ch] == 1)
        return *ch;
    }
    return 0;
  }
  void main(){
    char *str = "abaccdeff";
    char ch = findNotRepeatedChar(str);
    ASSERT_EQ('b', ch);
    LOG(INFO)<<"Not repeated char is:"<<ch;
  }
};

TEST_F(JZOffer, TC50){
  TC50Solution s;
  s.main();
}

// 在数组中的两个数字，如果前面的一个数字大于后面的一个数字，则称这两个数字为逆序对。
// 输入一个数组，求数组中逆序对的总数。例如：数组{7, 5, 6, 4}，共存在5个逆序对：
// (7, 5), (7, 6), (7, 4), (5, 4), (6, 4)
class TC51Solution {
public:
  int inversePairCountCore(int* data, int* copy, int start, int end){
    if(start >= end)
      return 0;
    int mid = (start + end) / 2;
    int left = inversePairCountCore(data, copy, start, mid);
    int right = inversePairCountCore(data, copy, mid+1, end);
    int lend = mid;
    int rend = end;
    int count = 0;
    int index = end;

    while(lend>=start && rend>=mid+1){
      if(data[lend] > data[rend]){
        count += rend-mid;
        copy[index--] = data[lend--];
      }else{
        copy[index--] = data[rend--];
      }
    }
    while(lend>=start){
      copy[index--] = data[lend--];
    }
    while(rend>=mid+1){
      copy[index--] = data[rend--];
    }
    memcpy(data+start, copy+start, (end-start+1)*sizeof(int));
    return left + right + count;
  }

  int inversePairCount(int* data, int len){
    if(data == nullptr)
      return 0;
    int *copy = new int[len];
    memcpy(copy, data, sizeof(int)*len);
    int cnt = inversePairCountCore(data, copy, 0, len-1);
    delete []copy;
    return cnt;
  }

  void main(){
    int data[] = {7, 5, 6, 4, 3};
    int len = sizeof(data) / sizeof(int);
    int result = inversePairCount(data, len);
    LOG(INFO)<<"inverse pair count is:"<<result;
    ASSERT_EQ(9, result);
  }
};

TEST_F(JZOffer, TC51){
  TC51Solution s;
  s.main();
}

template<typename T>
struct LinkListNode{
  T m_Value;
  LinkListNode<T>* m_pNext;
  LinkListNode(T value, LinkListNode<T>* pNext=nullptr):m_Value(value), m_pNext(pNext){}
};

// 输入两个链表，找出他们第一个公共节点。
class TC52Solution {
  typedef LinkListNode<int> Node;
public:
  Node* findFirstCommonNode(Node* root1, Node* root2){
    if(root1 == nullptr || root2 == nullptr)
      return nullptr;
    int len1 = 0;
    int len2 = 0;
    for(Node* node=root1; node!=nullptr; node=node->m_pNext)
      len1++;
    for(Node* node=root2; node!=nullptr; node=node->m_pNext)
      len2++;

    if(len1 > len2){
      for(int i=0; i<(len1-len2); i++)
        root1=root1->m_pNext;
    }else if(len1 < len2){
      for(int i=0; i<(len2-len1); i++)
        root2=root2->m_pNext;
    }

    while(root1!=nullptr && root2!=nullptr){
      if(root1 == root2)
        return root1;
      root1=root1->m_pNext;
      root2=root2->m_pNext;
    }
    return nullptr;
  }
  void main(){
    Node *p1 = new Node(7);
    Node *p2 = new Node(6, p1);
    p1 = p2;
    p2 = new Node(5, p1);
    Node *p3 = new Node(3, p1);
    p1 = p2;
    p2 = new Node(4, p1);
    p1 = new Node(2, p3);
    p3 = p1;
    p1 = new Node(1, p3);
    Node *firstCommonNode = findFirstCommonNode(p1, p2);
    ASSERT_NE(nullptr, firstCommonNode);
    ASSERT_EQ(6, firstCommonNode->m_Value);
  }
};

TEST_F(JZOffer, TC52){
  TC52Solution s;
  s.main();
}

// 统计一个数字在排序数组中出现的次数。例如给定数组{1, 2, 3, 3, 3, 3, 4, 5}
// 和数字3，输出4
class TC53Solution {
public:
  int getFirstK(int *data, int num, int start, int end, int k){
    if(data == nullptr || num == 0 || start > end)
      return -1;
    while(start <= end){
      int mid = (start + end) / 2;
      if(data[mid] > k){
        end = mid - 1;
      }else if(data[mid] < k){
        start = mid + 1;
      }else{  // data[mid] == k
        if(mid == 0){
          return 0;
        }else{
          if(data[mid - 1] == k){
            end = mid - 1;
          }else{
            return mid;
          }
        }
      }
    }
    return -1;
  }

  int getLastK(int *data, int num, int start, int end, int k){
    if(data == nullptr || num == 0 || start > end)
      return -1;
    while(start <= end){
      int mid = (start + end) / 2;
      if(data[mid] > k){
        end = mid - 1;
      }else if(data[mid] < k){
        start = mid + 1;
      }else{  // data[mid] == k
        if(mid == end){
          return mid;
        }else{
          if(data[mid + 1] == k){
            start = mid + 1;
          }else{
            return mid;
          }
        }
      }
    }
    return -1;
  }
  int getCountOfK(int *data, int num, int k){
    int first = getFirstK(data, num, 0, num - 1, k);
    int last = getLastK(data, num, 0, num - 1, k);
    if(first == -1 || last == -1)
      return 0;
    return (last - first + 1);
  }
  void main(){
    int data[] = {1, 2, 3, 3, 3, 3, 4, 5};
    int num = sizeof(data) / sizeof(int);
    int k = 3;
    LOG(INFO)<<"count of "<<k<<" is:"<<getCountOfK(data, num, k);
  }
};

TEST_F(JZOffer, TC53){
  TC53Solution s;
  s.main();
}

// 给定一个二叉搜索树，请找出其中第k大节点
class TC54Solution {
  typedef BinaryTreeNode<int> Node;
public:
  Node* GetKthNodeCore(Node* node, int &k){
    Node* result = nullptr;
    if(node->m_pLeft != nullptr)
      result = GetKthNodeCore(node->m_pLeft, k);

    if(result == nullptr){ // 说明左子树没有命中
      if(k == 1){
        result = node;
      }else{
        k--;
      }
    }

    if(result == nullptr && node->m_pRight != nullptr)
      result = GetKthNodeCore(node->m_pRight, k);
    
    return result;
  }
  Node* GetKthNode(Node *root, int k){
    if(root == nullptr || k < 1)
      return nullptr;
    return GetKthNodeCore(root, k);
  }
  void main(){
    Node *l = new Node(2);
    Node *r = new Node(4);
    Node *root = new Node(3, l, r);
    l = new Node(6);
    r = new Node(8);
    Node *p = new Node(7, l, r);
    l = root;
    r = p;
    root = new Node(5, l, r);
    int k = 3;
    p = GetKthNode(root, k);
    if(p != nullptr){
      LOG(INFO)<<"The "<<k<<"th Node is:"<<p->m_Value;
    }else{
      LOG(INFO)<<"The "<<k<<"th Node NOT exists";
    }
  }
};

TEST_F(JZOffer, TC54){
  TC54Solution s;
  s.main();
}

// 输入一棵二叉树的根节点，求该树的深度（从根节点到叶子节点的最长路径）。
class TC55Solution {
  typedef BinaryTreeNode<int> Node;
public:
  int treeDepth(Node* root){
    if(root == nullptr)
      return 0;
    int left = treeDepth(root->m_pLeft);
    int right = treeDepth(root->m_pRight);
    return left>right?(left+1):(right+1);
  }

  void main(){
    Node* l = new Node(7);
    Node* p = new Node(5, l);
    Node* r = p;
    l = new Node(4);
    Node* root = new Node(2, l, r);
    r = new Node(6);
    p = new Node(3, nullptr, r);
    l = root;
    r = p;
    root = new Node(1, l, r);
    LOG(INFO)<<"tree depth is:"<<treeDepth(root);
  }
};

TEST_F(JZOffer, TC55){
  TC55Solution s;
  s.main();
}

// 输入一棵二叉树的根节点，判断该二叉树是不是平衡二叉树。
class TC55BSolution {
  typedef BinaryTreeNode<int> Node;
public:
  bool isBalance(Node* root, int& depth){
    if(root == nullptr){
      depth = 0;
      return true;
    }
    int left = 0;
    int right = 0;
    if(isBalance(root->m_pLeft, left) && isBalance(root->m_pRight, right)){
      int diff = left - right;
      if(diff <= 1 && diff >= -1){
        depth = 1 + (left>right?left:right);
        return true;
      }
    }
    LOG(INFO)<<"node "<<root->m_Value<<" is not balance. left="<<left<<" right="<<right;
    return false;
  }
  void main(){
    Node* l = new Node(7);
    Node* p = new Node(5, l);
    Node* r = p;
    l = new Node(4);
    Node* root = new Node(2, l, r);
    r = new Node(6);
    p = new Node(3, nullptr, r);
    l = root;
    r = p;
    root = new Node(1, l, r);
    int depth = 0;
    bool ret = isBalance(root, depth);
    if(ret){
      LOG(INFO)<<"tree is balance";
    }else{
      LOG(INFO)<<"tree is NOT balance";
    }
  }
};

TEST_F(JZOffer, TC55B){
  TC55BSolution s;
  s.main();
}

// 给定一个正整数s，求所有和为s的连续正整数序列（至少含有两个数）
class TC57Solution {
public:
  void printContinuousSequence(int start, int end){
    printf("continuous sequence: ");
    for(int i=start; i<=end; i++){
      printf(" %d", i);
    }
    printf("\n");
  }
  void findContinuousSequence(int sum){
    if(sum < 3)
      return;
    int start = 1;
    int end = 2;
    int mid = (sum + 1) / 2;
    int currSum = start + end;
    while(start < mid){
      if(currSum == sum)
        printContinuousSequence(start, end);
      
      while(currSum > sum && start < mid){
        currSum -= start;
        start++;
        if(currSum == sum)
          printContinuousSequence(start, end);
      }
      end++;
      currSum += end;
    }
  }
  void main(){
    findContinuousSequence(3);
  }
};

TEST_F(JZOffer, TC57){
  TC57Solution s;
  s.main();
}

// 字符串的左旋操作是把字符串前面若干个字符转移到字符串的尾部。比如：
// 输入字串abcdefg和数字2，该函数左旋结果为cdefgab。
class TC58Solution {
public:
  void reverseString(char* str, int begin, int end){
    if(str == nullptr)
      return;
    while(begin < end){
      char tmp = str[begin];
      str[begin] = str[end];
      str[end] = tmp;
      begin++;
      end--;
    }
  }
  void leftRotateString(char* str, int n){
    int len = strlen(str);
    if(n>=len)
      return;
    reverseString(str, 0, len-1);
    reverseString(str, 0, len - n - 1);
    reverseString(str, len - n, len - 1);
  }
  void main(){
    char str[] = "abcdefg";
    leftRotateString(str, 2);
    LOG(INFO)<<"rotated string is: "<<str;
  }
};

TEST_F(JZOffer, TC58){
  TC58Solution s;
  s.main();
}

// 给定一个数组和滑动窗口的大小，请找出所有滑动窗口里的最大值。例如：
// 数组{2, 3, 4, 2, 6, 2, 5, 1}，滑动窗口为3，则共存在6个滑动窗口
// 他们的最大值分别为{4, 4, 6, 6, 6, 5}
class TC59Solution {
public:
  std::vector<int> maxInWindow(const std::vector<int>& num, unsigned int size){
    std::vector<int> maxWindow;
    if(size>num.size() || size <= 0){
      return maxWindow;
    }
    std::deque<int> index;
    for(int i=0; i<size; i++){
      while(!index.empty() && num[i] >= num[index.back()]){
        index.pop_back();
      }
      index.push_back(i);
    }
    for(int i=size; i<num.size(); i++){
      maxWindow.push_back(num[index.front()]);
      while(!index.empty() && num[i] >= num[index.back()]){
        index.pop_back();
      }
      if(!index.empty() && index.front() <= i - size){
        index.pop_front();
      }
      index.push_back(i);
    }
    maxWindow.push_back(num[index.front()]);
    return maxWindow;
  }
  void main(){
    std::vector<int> num = {2, 3, 4, 2, 6, 2, 5, 1};
    // std::vector<int> num = {5, 2, 3, 6, 4, 1, 7, 4, 5, 9};

    int size = 3;
    std::vector<int> maxInWin = maxInWindow(num, size);
    for(int i=0; i<maxInWin.size(); i++){
      printf(" %d", maxInWin[i]);
    }
    printf("\n");
  }
};

TEST_F(JZOffer, TC59){
  TC59Solution s;
  s.main();
}

class TCSolution {
public:
  void main(){
  }
};

TEST_F(JZOffer, TC){
  TCSolution s;
  s.main();
}
