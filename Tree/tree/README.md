# 树的存储结构
- 不仅要存储各节点的数据信息，还要存储结点之间的关系（父子关系）
- 树的存储结构一般采用**链式存储**,又可分为**数组表示法**和**链表表示法**

## 双亲表示法
- 树的**双亲表示法**就是用指针表示出每个结点的双亲在存储空间的位置信息
- 方便查找双亲，不便查找孩子
### 双亲数组法
- **双亲数组法**就是用一维**结构体数组**依次存储树中的各结点，数组中的一个元素表示树中的一个结点，数组元素中包括**结点本身的信息**和**结点的双亲结点在数组中的下标**
```cpp
#define MAX_TREE_SIZE 100 
typedef struct { 
    TElemType data; 
    int parent; 
}PTreeNode; 
PTreeNode PTree[MAX_TREE_SIZE];
```
![](https://git.acwing.com/ZagY/learn-data-structures/-/raw/main/Tree/tree/picture/1.png "")
### 双亲链表法
- **双亲链表法**就是用一组任意的存储单元存储树中各结点，结点中包括**结点本身的信息**和**指向该结点的双亲的指针**
## 孩子表示法
- 树的**孩子表示法**就是用指针表示出每个结点的孩子在存储空间的位置信息
- 方便查找孩子，不便查找双亲
### 孩子数组法
- **孩子数组法**用一维**结构体数组**依次存储树中的各结点，数组中的一个元素表示树中的一个结点，数组元素中包括**结点本身的信息**和**结点的孩子结点在数组中的下标**
- 每个结点中孩子结点的个数等于该结点的度，若某结点无孩子，其相应的指针域为空（用-1表示）
```cpp
typedef struct {
  TElemType data;                      
  int child[MAX_SON_SIZE];             
}CTreeNode;                           
CTreeNode CTree[MAX_TREE_SIZE];
```
![](https://git.acwing.com/ZagY/learn-data-structures/-/raw/main/Tree/tree/picture/2.png "")
### 孩子链表法
- **孩子链表法**就是用一组任意的存储单元存储树中各结点，结点中包括**结点本身的信息**和**指向该结点的所有孩子的指针**
- 结点中指针域的个数等于树的度数
```cpp
typedef struct CTNode {
  TElemType data;                     
  struct CTNode *child[MAX_SON_SIZE]; 
}CTNode,*CTree;                       
```
![](https://git.acwing.com/ZagY/learn-data-structures/-/raw/main/Tree/tree/picture/3.png "")
## 双亲孩子表示法
- 既存储双亲在存储空间中的位置，又存储孩子在存储空间中的位置
- 方便查找孩子，方便查找双亲
### 双亲孩子数组法
- **双亲孩子数组法**就是用一维数组存储树中各结点，数组元素中包括结点本身的信息以及双亲结点和所有孩子结点在数组中的下标
```cpp
typedef struct {
  TElemType data;                         
  int parent;                             
  int child[MAX_SON_SIZE];                
}PCTreeNode;                             
PCTreeNode PCTree[MAX_TREE_SIZE];
```
### 双亲孩子链表法
- **双亲孩子链表法**就是把某个结点的所有孩子排列起来，并用单链表作为它的存储表示
![](https://git.acwing.com/ZagY/learn-data-structures/-/raw/main/Tree/tree/picture/5.png "")
### 双亲数组孩子链表法
- n个结点的树，用n个这样的单链表组成，每个单链表设立一个表头结点
- 它有3个域：**数据域data**表示树的一个结点的数据信息，**指针域（下标）parent**为该结点的双亲在数组中的下标，**指针域link**指向该结点的孩子单链表的第一个结点
- n个这样的表头结点用一维数组表示

![](https://git.acwing.com/ZagY/learn-data-structures/-/raw/main/Tree/tree/picture/6.png "")
