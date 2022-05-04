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

# 树的基本操作
- 采用孩子兄弟链表存储
## 树的结点
```cpp
typedef struct treenode {
    char data[MAX];
    struct treenode *child;  //第一个孩子 
    struct treenode *sibling;  //下一个兄弟 
}treenode, *treelink;
```
## 创建树
- 与父结点建立链接关系时，首次出现的孩子结点作为第一个孩子，其他孩子结点依次链接为前一个孩子的右孩子
### 递归创建（先序）
```cpp
/* 创建一棵树  */
void tree_create(treelink &root){
    char data[MAX];
    scanf("%s", data);
    if (strcmp(data, "#") == 0) root = NULL;
    else {
        root = new treenode;
        strcpy(root->data, data);
        tree_create(root->child);
        tree_create(root->sibling);
    }
}
```
### 输入边创建
```cpp
/* 创建一棵二叉树  */
void tree_create(treelink &root){
    char fa[30], ch[30];  //fa为父结点 ch为子结点
    treelink p, s, r;  //p为父结点 s为子结点
    queue<treelink>que;
    root = NULL;
    printf("请输入父结点、子结点（用空格隔开，根结点的双亲为#）\n");
    scanf("%s%s",fa, ch);
    while (strcmp(ch,"end")) {
        s = new treenode;    // 创建结点
        strcpy(s->data,ch);
        s->child = s->sibling = NULL;

        que.push(s);// 指针入队列
        if (strcmp(fa,"#") == 0)  root = s;  // 所建为根结点
        else {// 非根结点的情况
            p = que.front();// 取队列头元素(指针值)
            while (strcmp(p->data,fa)) { // 查询双亲结点
                que.pop();
                p = que.front();
            }//while

            if (!(p->child)){
                p->child = s;
                r = s;
            }// 链接第一个孩子结点
            else {
                r->sibling = s;  r = s;
            }// 链接其它孩子结点
        }// 非根结点的情况
        printf("请输入父结点、子结点（用空格隔开，结束时输入end end 0）\n");
        scanf("%s%s",fa,ch);
    } // for
}
```
## 销毁树
```cpp
/* 销毁二叉树 */
void Destroy(treelink p) {
    if(p) {
        Destroy(p->child);
        Destroy(p->sibling);
        delete p;
        p = NULL;
    }
}
```
## 求树深度
```cpp
/* 求树深度 */
int get_depth(treelink root) {
    if (root == NULL) return 0;
    else {
        int d1 = get_depth(root->child);
        int d2 = get_depth(root->sibling);
        return d1 + 1 > d2 ? d1 + 1 : d2;
    }
}
```
## 凹入表显示
```cpp
/* 凹入表显示 */
void disp_tree(treelink root, int level) { //level为root结点的高度
    if (root == NULL) return ;

    for(int i = 1; i < level + 20; i++)
        putchar('-');

    putchar('+');
    printf("%s\n",root->data);
    disp_tree(root->child,level - 2);
    disp_tree(root->sibling, level);
}
```
## 查找
```cpp
treelink node_find1(treelink root, char *name) {

    treenode *p;
    if(root == NULL) return NULL;
    else{
        if(strcmp(root->data, name)==0)
            return root;
        else if(p = node_find1(root->child, name))
            return p;
        else
            return node_find1(root->sibling, name);
    }
}
```
```cpp
void node_find2(treelink pTree, char  *szName, treelink &pLast, treelink &p1, treelink &p2) {
    if(pTree == NULL) return;
    if(strcmp(pTree->data, szName) == 0){  //找到则返回父节点指针和当前节点指针
        p2 = pTree;  //当前节点
        p1 = pLast;  //父节点
    }
    else{
        //pLast = pTree;//暂存上一级节点指针
        node_find2(pTree->child, szName, pTree, p1, p2);
        //pLast = pTree;
        node_find2(pTree->sibling, szName, pTree, p1, p2);
    }
}
```
## 插入
- 如果找到的双亲结点的第一个孩子结点地址为空，则双亲结点没有孩子，新插入的孩子结点作为第一个孩子结点
- 反之，在第一个孩子结点的兄弟链上找到最后一个孩子结点，将新结点插入为最后一个孩子
```cpp
/* 插入 */
void node_insert(treelink pTree, char  *szParent, char  *szNew)
{
    treelink pFind = NULL;
    treelink pChild = NULL;
    pFind = node_find(pTree, szParent);

    if(pFind){
        pChild = pFind->child;
        while(pChild!=NULL){
            if(strcmp(pChild->data,szNew)==0){
                printf("子节点已存在！\n");
                return;
            }else
                pChild = pChild->sibling;
        }

        treelink pNew = new treenode;
        strcpy(pNew->data, szNew);
        if(pFind->child){
            pNew->sibling = pFind->child;
            pNew->child = NULL;
        }else{
            pNew->child = NULL;
            pNew->sibling = NULL;
        }
        pFind->child = pNew;
    }else
        printf("父节点不存在!\n");

}
```
## 删除
- 删除树中的一个结点，约定将删除以该结点为根的子树
- 如果该结点是双亲的第一个孩子，需将它的右兄弟链接为双亲的第一个孩子
- 如果该结点不是第一个孩子，需将它的右孩子链接成它前一个兄弟的右兄弟
```cpp
/* 删除 */
void node_delete(treelink &pTree, char *szName){
    treelink pFind = NULL, pParent = NULL, p = NULL;

    node_find2(pTree, szName, p, pParent, pFind);

    if(pFind){
        if(pParent == NULL){//删除根节点
            Destroy(pTree);
            pTree = NULL;
        }else{
            if(pParent->child == pFind)//删除孩子节点
                pParent->child = pFind->sibling;
            else//删除兄弟节点
                pParent->sibling = pFind->sibling;

            pFind->sibling = NULL;//摘除当前节点
            Destroy(pFind);//删除当前节点
        }
    }else
        printf("指定删除节点不存在!\n");
}
```


# 测试数据
```cpp
ncepu 学院 控计 软件 # 计算 # 信安 # 物联 # # 电气 # 能源 # # 管理部门 # # #
```
# 输出
```cpp
凹入表显示
-----------------------+ncepu
---------------------+学院
-------------------+控计
-----------------+软件
-----------------+计算
-----------------+信安
-----------------+物联
-------------------+电气
-------------------+能源
---------------------+管理部门
```
