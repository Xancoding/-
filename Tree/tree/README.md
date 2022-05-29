# 顺序栈的基本操作
```cpp
typedef struct stack {
    char **data;  //data是一个指针变量，存放一片连续空间的首地址 
    int top;  //指示栈顶的位置 
    int stackSize;  //栈的容量 
}SqStack;

void InitSqStack(SqStack &S) {
    S.data = new char*[MAX];
    S.top = -1;  //约定栈空时S.top=-1
    S.stackSize = MAX;
}

void PushSqStack(SqStack &S,char *data) {
    if(S.stackSize != S.top + 1)
        S.data[++S.top] = data;
}

void PopSqStack(SqStack &S) {
    if(S.top != -1)
        S.top--;
}

void TraversSqStack(SqStack S) {
    if(S.top != -1)
        for(int i = S.top; i >= 0; i--)
            printf("%s ",S.data[i]);
    printf("\n");

}

void GetHead(SqStack &S, char* &p){
    if(S.top != -1)
        p = S.data[S.top];
}

int EmSqStack(SqStack S){
    if (S.top != -1) return 0;
    else return 1;
}
```
# 循环队列的基本操作
```cpp
typedef struct {
    treelink *elem;
    int front,rear;
    int queuesize;
}XhQueue;

void InitQueue(XhQueue &Q){
    Q.elem = new treelink[MAX];
    if(Q.elem != NULL) {
        Q.front = Q.rear = 0;
        Q.queuesize = MAX;
    }
}

void EnQueue(XhQueue &Q,treelink p){
    if((Q.rear + 1) % Q.queuesize != Q.front){
        Q.elem[Q.rear] = p;
        Q.rear = (Q.rear + 1) % Q.queuesize;
    }
}

void DeQueue(XhQueue &Q,treelink &p){
    if(Q.front != Q.rear){
        p = Q.elem[Q.front];
        Q.front = (Q.front +1) % Q.queuesize;
    }
}

void GetHead(XhQueue &Q,treelink &p){
    if(Q.front != Q.rear){
        p = Q.elem[Q.front];
    }
}

int EmQueue(XhQueue Q){
    if(Q.front != Q.rear)return 0;
    else return 1;
}

int LengthQueue(XhQueue Q){
    return (Q.rear - Q.front + Q.queuesize) % Q.queuesize;
}
```
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
void tree_create(treelink &T) {
    char data[MAX];
    scanf("%s", data);
    if (strcmp(data, "#") == 0) T = NULL;
    else {
        T = new treenode;
        strcpy(T->data, data);
        tree_create(T->child);
        tree_create(T->sibling);
    }
}
```
### 输入边创建
#### STL版
```cpp
/* 创建一棵树  */
void tree_create(treelink &T){
    char fa[30], ch[30];  //fa为父结点 ch为子结点
    treelink p, s, r;  //p为父结点 s为子结点
    queue<treelink>que;
    T = NULL;
    printf("请输入父结点、子结点（用空格隔开，根结点的双亲为#）\n");
    scanf("%s%s",fa, ch);
    while (strcmp(ch,"end")) {
        s = new treenode;    // 创建结点
        strcpy(s->data,ch);
        s->child = s->sibling = NULL;

        que.push(s);// 指针入队列
        if (strcmp(fa,"#") == 0)  T = s;  // 所建为根结点
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
        printf("请输入父结点、子结点（用空格隔开，结束时输入end end）\n");
        scanf("%s%s",fa,ch);
    } // for
}
```
#### C语言版
```cpp
/* 创建一棵树  */
void tree_create(treelink &T){
    char fa[30], ch[30];  //fa为父结点 ch为子结点
    treelink p, s, r;  //p为父结点 s为子结点
    XhQueue Q;
    InitQueue(Q);
    T = NULL;
    printf("请输入父结点、子结点（用空格隔开，根结点的双亲为#）\n");
    scanf("%s%s",fa, ch);
    while (strcmp(ch,"end")) {
        s = new treenode;    // 创建结点
        strcpy(s->data,ch);
        s->child = s->sibling = NULL;

        EnQueue(Q, s);// 指针入队列
        if (strcmp(fa,"#") == 0)  T = s;  // 所建为根结点
        else {// 非根结点的情况
            GetHead(Q, p);// 取队列头元素(指针值)
            while (strcmp(p->data,fa)) { // 查询双亲结点
                DeQueue(Q, p);
                GetHead(Q, p);
            }//while

            if (!(p->child)){
                p->child = s;
                r = s;
            }// 链接第一个孩子结点
            else {
                r->sibling = s;  r = s;
            }// 链接其它孩子结点
        }// 非根结点的情况
        printf("请输入父结点、子结点（用空格隔开，结束时输入end end）\n");
        scanf("%s%s",fa,ch);
    } // for
}
```
## 销毁树
```cpp
/* 销毁树 */
void Destroy(treelink &p) {
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
int get_depth(treelink T) {
    if (T == NULL) return 0;
    else {
        int d1 = get_depth(T->child);
        int d2 = get_depth(T->sibling);
        return d1 + 1 > d2 ? d1 + 1 : d2;
    }
}
```
## 凹入表显示
```cpp
/* 凹入表显示 */
void disp_tree(treelink T, int level) { //level为T结点的高度
    if (T == NULL) return ;

    for(int i = 1; i < level + 20; i++)
        putchar('-');

    putchar('+');
    printf("%s\n",T->data);
    disp_tree(T->child,level - 2);
    disp_tree(T->sibling, level);
}
```
## 查找
- 仅查找当前结点
```cpp
/* 查找 */
treelink node_find1(treelink T, char *data) {

    treelink p;
    if(T == NULL) return NULL;
    else{
        if(strcmp(T->data, data)==0)
            return T;
        else if(p = node_find1(T->child, data))
            return p;
        else
            return node_find1(T->sibling, data);
    }
}
```
- 查找当前结点及其父结点
```cpp
void node_find2(treelink pTree, char *data, treelink &pLast, treelink &p1, treelink &p2) {
    if(pTree == NULL) return;
    if(strcmp(pTree->data, data) == 0){  //找到则返回父节点指针和当前节点指针
        p2 = pTree;  //当前节点
        p1 = pLast;  //父节点
    }
    else{
        //pLast = pTree;//暂存上一级节点指针
        node_find2(pTree->child, data, pTree, p1, p2);
        //pLast = pTree;
        node_find2(pTree->sibling, data, pTree, p1, p2);
    }
}
```
## 插入
- 如果找到的双亲结点没有孩子，那么将新插入的结点作为第一个孩子结点
- 如果双亲结点已经有孩子，那么将第一个孩子结点作为新结点的兄弟，并将新结点作为第一个孩子结点
```cpp
/* 插入 */
void node_insert(treelink pTree, char  *szParent, char  *szNew)
{
    treelink pFind= NULL;
    treelink pChild = NULL;
    treelink parent;  //待查找结点的父结点
    pFind = node_find1(pTree, szParent);

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
void node_delete(treelink &pTree, char  *data){
    treelink pFind = NULL, pParent = NULL, p = NULL;

    node_find2(pTree, data, p, pParent, pFind);

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
## 树的遍历
### 先根遍历
- 同二叉树的先序遍历 
```cpp
/* 先根遍历 */
void preorder_traversal(treelink T) {
    if (T == NULL) return ;
    printf("%s ", T->data);
    preorder_traversal(T->child);
    preorder_traversal(T->sibling);
}
```
### 后根遍历
- 同二叉树的中序遍历 
```cpp
/* 后根遍历 */
void postorder_traversal(treelink T) {
    if (T == NULL) return ;
    preorder_traversal(T->child);
    preorder_traversal(T->sibling);
    printf("%s ", T->data);
}
```
### 层次遍历
#### STL版
```cpp
/*层次遍历 */
void levelorder_traversal(treelink T) {
    queue<treelink> que;
    que.push(T);
    if (T == NULL) return;
    while (!que.empty()) {
        int size = que.size();
        for (int i = 0; i < size; i++) {    //size不能换成que.size(),因为que长度会变
            treelink cur = que.front();
            que.pop();
            printf("%s ", cur->data);
            cur = cur->child;
            while (cur != NULL) {
                que.push(cur);
                cur = cur->sibling;
            }
        }
        puts("");
    }
}
```
#### C语言版
```cpp
/*层次遍历 */
void levelorder_traversal(treelink T) {
    XhQueue Q;
    InitQueue(Q);
    EnQueue(Q, T);
    if (T == NULL) return;
    while (!EmQueue(Q)) {
        int size = LengthQueue(Q);
        for (int i = 0; i < size; i++) {
            treelink cur;
            DeQueue(Q, cur);
            printf("%s ", cur->data);
            cur = cur->child;
            while (cur != NULL) {
                EnQueue(Q, cur);
                cur = cur->sibling;
            }
        }
        puts("");
    }
}
```

## 子结点
```cpp
/* 子结点输出 */
void get_follow(treelink T, char *s) { //输出指定结点的子结点
    T = node_find1(T, s);
    
    if (T == NULL) return ;
    T = T->child;
    while (T != NULL) {
        printf("%s ", T->data);
        T = T->sibling;
    }
}
```
## 求路径
### 路径
#### STL版
```cpp
/* 路径 */
void Path(treelink pTree, stack<char*>st, char data[]) {
    if (pTree) {
    	st.push(pTree->data);
    	if (strcmp(pTree->data, data) == 0) print_stack(st);
    	else Path(pTree->child, st, data);
    	st.pop();
    	Path(pTree->sibling, st, data);
    }
}
```
#### C语言版
```cpp
```
### 叶子结点路径
- 对只有左子树的二叉树作先序遍历，用栈保存首次遇到的结点
- 如果栈顶是叶子结点，遍历输出栈得到一条叶子路径，栈顶结点出栈。如果出栈结点有右兄弟，继续对以右兄弟为根的子树先序遍历，找其叶子结点路径
- 如果栈顶不是叶子结点，继续进行以栈顶结点为根的子树进行先序遍历。如果以栈顶结点为根的所有子树的先序遍历均已完成，栈顶结点出栈
- 当栈为空时，所有叶子结点路径均已完成，算法结束
#### STL版
```cpp
/* 求所有叶子结点路径 */
void all_tree_path(treelink T, stack<char*>st) {
    while (T) {
        st.push(T->data);
        if (!T->child) print_stack(st);  //T是叶子结点
        else all_tree_path(T->child, st);  //找以T为根的子树上的叶子结点路径
        st.pop();  //栈顶结点是叶子结点或以栈顶结点为根的子树上的叶子路径已完成
        T = T->sibling;     //继续找T的其余子树
    }
}
```
#### C语言版
```cpp
```
# 测试数据
```cpp
ncepu 学院 控计 软件 # 计算 # 信安 # 物联 # # 电气 # 能源 # # 管理部门 # # #
```
# 输出
```cpp
先根遍历  ncepu 学院 控计 软件 计算 信安 物联 电气 能源 管理部门

后根遍历  学院 控计 软件 计算 信安 物联 电气 能源 管理部门 ncepu

层序遍历
ncepu
学院 管理部门
控计 电气 能源
软件 计算 信安 物联

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

控计结点的子结点
软件 计算 信安 物联

到计算结点的路径
/ncepu/学院/控计/计算

叶子结点路径
/ncepu/学院/控计/软件
/ncepu/学院/控计/计算
/ncepu/学院/控计/信安
/ncepu/学院/控计/物联
/ncepu/学院/电气
/ncepu/学院/能源
/ncepu/管理部门
```
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
