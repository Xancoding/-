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
   string data;
   struct treenode *left;
   struct treenode *right;
 }treenode;
``` 
## 二叉树的创建
```cpp
/* 创建一棵二叉树 */
treenode *tree_create()
{  
  string data;
  scanf("%s", data);
  if (data == "#") root = NULL;
  else {
    root = new treenode;
    root->data = data;
    tree_create(root->left);
    tree_create(root->right);
  }
  return root;
}
```
按先序遍历的顺序读入每个结点值，递归创建生成二叉树

