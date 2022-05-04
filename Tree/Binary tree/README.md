## 二叉树的性质

- 二叉树的第 i 层至多有 **2^(i-1)** 个结点

- 深度为k的二叉树最多有 **2^k - 1** 个结点

- 对于一棵非空的二叉树，如果叶子结点数为n0，度为2的结点数为n2，则有：**n0 = n2 + 1**

- 具有n个结点的**完全二叉树**的深度k为 **⌊log2n⌋ + 1**

- 对于一棵有n个结点的**完全二叉树**，其深度为 **⌊log2n⌋ + 1**，对结点按层序编号，则对任一结点i（1 <= i <= n），有：
  - 当 i > 1 时，父亲结点为结点 **⌊i / 2⌋**（i = 1 时，表示的是根结点，无父亲结点）
  - 如果 2 * i > n（总结点的个数） ，则结点 i 肯定没有左孩子（为叶子结点），否则其左孩子是结点 **2 * i** 
  - 如果 2 * i + 1 > n ，则结点 i 肯定没有右孩子，否则右孩子是结点 **2 * i + 1**     
## 二叉树的节点
```cpp
 typedef struct treenode {
   char data[MAX];
   struct treenode *left;
   struct treenode *right;
 }treenode;
``` 
## 二叉树的创建
### 递归创建
```cpp
/* 创建一棵二叉树  */
void tree_create(treenode *&root){
    char data[MAX];
    scanf("%s", data);
    if (strcmp(data, "#") == 0) root = NULL;
    else {
        root = new treenode;
        strcpy(root->data, data);
        tree_create(root->left);
        tree_create(root->right);
    }
}
```
- 用``#``表示空节点，按照先序遍历的次序，生成二叉树
### 用边创建
```cpp
/* 创建一棵二叉树  */
void tree_create(treenode *&root){
    char fa[30], ch[30];  //fa为父结点 ch为子结点 
    treenode *p, *s;  //p为父结点 s为子结点 
    int flag;
    queue<treenode*>que;
    root = NULL;
    printf("请输入父结点、子结点、左(0)右(1)标志（用空格隔开，根结点的双亲为#）\n");
    scanf("%s%s%d",fa, ch,&flag);
    while (strcmp(ch,"end")) {
        s = new treenode;    // 创建结点
        strcpy(s->data,ch);
        s->left = s->right = NULL;

        que.push(s);// 指针入队列
        if (strcmp(fa,"#") == 0)  root = s;  // 所建为根结点
        else {// 非根结点的情况
            p = que.front();// 取队列头元素(指针值)
            while (strcmp(p->data,fa)) { // 查询双亲结点
            	que.pop();
				p = que.front();
            }//while

            if (flag==0){
                p->left = s;
            }// 链接左孩子
            else {
                p->right = s;
            }// 链接右孩子
        }// 非根结点的情况
        printf("请输入父结点、子结点、左右标志（用空格隔开，结束时输入end end 0）\n");
        scanf("%s%s%d",fa,ch,&flag);
    } // for
}
```
## 二叉树的销毁
```cpp
/* 销毁二叉树 */
void Destroy(treenode *p) {
    if(p) {
        Destroy(p->left);
        Destroy(p->right);
        delete p;
    }
}
```
## 结点的查找
```cpp
/* 查找数据 */ 
treenode *node_find(treenode *root, char *name)
{

    treenode *p;
    if(root == NULL) return NULL;
    else{
        printf("%s ", root->data);
        if(strcmp(root->data, name)==0)
            return root;
        else if(p = node_find(root->left, name))
            return p;
        else
            return node_find(root->right, name);
    }
}
```
## 结点的删除
```cpp
/* 删除数据 */
void node_delete(treenode* & Root, char *name) {

    if(Root){
        if(strcmp(Root->data,name)==0){
            Destroy(Root);
            Root = NULL;
        }
        else{
            node_delete(Root->left, name);
            node_delete(Root->right, name);
        }
    }
}
```
## 结点的插入
```cpp
/* 插入数据 */
void node_insert(treenode *Root, char *pname, char *cname) {
    treenode *parent, *pnew;
    parent = node_find(Root, pname);
    if(parent==NULL){
        printf("父结点不存在\n");
        return;
    }else{
        if(parent->left && parent->right){
            printf("子结点已满\n");
            return;
        }

        if(parent->left){
            if(strcmp(parent->left->data,cname)==0){
                printf("同名子结点已存在\n");
                return;
            }
        }
        if(parent->right){
            if(strcmp(parent->right->data, cname)==0){
                printf("同名子结点已存在\n");
                return;
            }
        }

        pnew = new treenode;  pnew->left = pnew->right =NULL;
        strcpy(pnew->data, cname);
        /* 优先插入左结点 */
        if(parent->left == NULL)
            parent->left = pnew;
        else
            parent->right = pnew;

    }
}
```
## 二叉树的遍历
### 深度优先遍历
#### 递归法
```cpp
/* 前序遍历 */
void preorder_traversal(treenode *root) {
  if (root == NULL) return ;
  printf("%s ", root->data);
  preorder_traversal(root->left);
  preorder_traversal(root->right);
}

/* 中序遍历 */
void inorder_traversal(treenode *root) {
  if (root == NULL) return ;
  inorder_traversal(root->left);
  printf("%s ", root->data);
  inorder_traversal(root->right);
}

/* 后序遍历 */
void postorder_traversal(treenode *root) {
  if (root == NULL) return ;
  postorder_traversal(root->left);
  postorder_traversal(root->right);
  printf("%s ", root->data);
}
```
#### 迭代法
```cpp
/* 前序遍历 */
void preorder_traversal(treenode *root) {
  if (root == NULL) return ;
  stack<treenode*>st;
  st.push(root);
  while(!st.empty()) {
  treenode *cur = st.top();
  st.pop();
  printf("%s ", cur->data);
  if (cur->right != NULL) st.push(cur->right);
  if (cur->left != NULL) st.push(cur->left);
  }
}

/* 中序遍历 */
void inorder_traversal(treenode *root) {
  if (root == NULL) return ;
  stack<treenode*>st;
  treenode *cur = root;
  while(cur != NULL || !st.empty()) {
    while (cur != NULL) {   // 指针来访问节点，访问到最底层
      st.push(cur);
      cur = cur->left;
    }
    cur = st.top();
    st.pop();
    printf("%s ", cur->data);
    cur = cur->right;
  } 
}

/* 后序遍历 */
void postorder_traversal(treenode *root) {
  if (root == NULL) return ;
  stack<treenode*>st;
  treenode *prev = NULL;  //记录上一次输出的节点
  treenode *cur = root;
  while (cur != NULL || !st.empty()) {
    while (cur != NULL) {
      st.push(cur);
      cur = cur->left;
    }
    cur = st.top();
    st.pop();
    //该节点没有右子树或者它的右子树已经被访问过
    if (cur->right == NULL || cur->right == prev) {
      printf("%s ", cur->data);
      prev = cur;
      cur = NULL;
    } else {  //若节点的右子树不为空，则该节点再次入栈
      st.push(cur);
      cur = cur->right;
      }
  }
}

```
### 广度优先遍历
```cpp
void levelorder_traversal(treenode* root) {
  queue<treenode*>que;
  que.push(root);
  if (root == NULL) return ;
  while (!que.empty()) {
    int size = que.size();  
    for (int i = 0; i < size; i++) {    //size不能换成que.size(),因为que长度会变
      treenode *cur = que.front();
      que.pop();
      printf("%s ", cur->data);
      if (cur->left != NULL) que.push(cur -> left);
      if (cur->right != NULL) que.push(cur -> right);
    }
    puts("");
  }
```
## 树的表示
### 广义表
```cpp
```
### 凹入表
```cpp
/* 凹入表显示 */
void disp_tree(treenode *root, int level, char c) { //level为root结点的高度，c为树根的标志，如"D"
    if (root == NULL) return ;

    for(int i = 1; i < level + 20; i++)
        putchar('-');

    putchar('+');
    printf("%s(%c)\n",root->data,c);
    level = level - 2;
    disp_tree(root->left,level,'L');
    disp_tree(root->right,level,'R');
}
```
## 遍历算法的应用
### 求二叉树深度
```cpp
int get_depth(treenode *root) {
	if (root == NULL) return 0;
	else {
		int L = get_depth(root->left);
		int R = get_depth(root->right);
		if (L > R) return (L + 1);
		else return (R + 1);
		
	}	
}

```
### 求叶子节点个数
```cpp
void leaf_count(treenode *root, int &count) {
    if (root == NULL) return ;
    else {
        leaf_count(root->left, count);
        if (root->left == NULL && root->right == NULL) count++;
        leaf_count(root->right, count);
    }
}
```
### 求结点个数
```cpp
void node_count(treenode *root, int &num) {
    if (root == NULL) return ;

    node_count(root->left, num);
    num++;
    node_count(root->right, num);
}
```

## 测试数据
```cpp
生成二叉树(先序)  ncepu ee # # cs # #

生成二叉树(用边生成)  
# ncepu 0
ncepu ee 0
ncepu cs 1
end end 0

先序遍历	ncepu ee cs

中序遍历	ee ncepu cs

后序遍历	ee cs ncepu

层序遍历	
ncepu
ee cs
```

## 输出
```cpp
深度为：2
叶子结点个数为：2
结点个数为：3
凹入表显示：
---------------------+ncepu(D)
-------------------+ee(L)
-------------------+cs(R)
```

