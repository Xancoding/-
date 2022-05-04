# 树的存储结构
- 不仅要存储各节点的数据信息，还要存储结点之间的关系（父子关系）
- 树的存储结构一般采用**链式存储**,又可分为**数组表示法**和**链表表示法**

## 双亲表示法
- 树的**双亲表示法**就是用指针表示出每个结点的双亲在存储空间的位置信息
- 方便访问结点的双亲,但查找结点的孩子则需要遍历整个表
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
- **双亲链表法**就是用一组任意的存储单元存储树中各结点，结点中包括结点本身的信息和指向该结点的双亲的指针
## 孩子表示法
- 树的**孩子表示法**就是用指针表示出每个结点的孩子在存储空间的位置信息
- 方便查找孩子，不便查找双亲
### 孩子数组法
- **孩子数组法**用一维**结构体数组**依次存储树中的各结点，数组中的一个元素表示树中的一个结点，数组元素中包括**结点本身的信息**和**结点的孩子结点在数组中的下标**
- 结点中指针（相对指针，下标）的个数等于树的度，若某结点无孩子，其相应的指针域为空（用-1表示）
```cpp
typedef struct {
  TElemType data;                      
  int child[MAX_SON_SIZE];             
}CTreeNode;                           
CTreeNode CTree[MAX_TREE_SIZE];
```
![](https://git.acwing.com/ZagY/learn-data-structures/-/raw/main/Tree/tree/picture/2.png "")
