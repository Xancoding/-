# 树的存储结构
- 不仅要存储各节点的数据信息，还要存储结点之间的关系（父子关系）
- 树的存储结构一般采用**链式存储**,又可分为**数组表示法**和**链表表示法**

## 双亲表示法
- 树的双亲表示法就是用指针表示出每个结点的双亲在存储空间的位置信息
- 方便访问结点的双亲,但查找结点的孩子则需要遍历整个表
### 双亲数组法
- **双亲数组法**就是用一维**结构体数组**依次存储树中的各结点，数组中的一个元素表示树中的一个结点，数组元素中包括**结点本身的信息**和**结点的双亲结点在数组中的下标**
![](https://git.acwing.com/ZagY/learn-data-structures/-/raw/main/Tree/tree/picture/1.png "")
```cpp
树结点的定义
#define MAXSIZE 100
typedef struct tnode
{   ElemType  data;
    int parent; 
}PNode;
 树类型定义
typedef struct 
{   PNode node[MAXSIZE];
    int n; //结点数
    int r; //根结点位置
}PTree;
```
### 双亲链表法
- **双亲链表法**就是用一组任意的存储单元存储树中各结点，结点中包括结点本身的信息和指向该结点的双亲的指针
