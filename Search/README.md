# 基本概念
- 静态查找表：只需进行数据元素的查询操作
    - 顺序查找 `无序`
    - 二分查找 `有序`
    - 分块查找 `块间有序 块内无序`
- 动态查找表：在查找过程中需要对查找表进行修改
    - 二叉搜索树
        - 左子树所有结点的值均小于根结点的值
        - 右子树所有结点的值均大于根结点的值
        - 对其中序遍历，可得一个按关键字值有序的序列
    - 二叉平衡树(**AVL树**)
        - 左子树和右子树高度之差的绝对值不超过1
    - B-树和B+树
- 关键字(Key)：数据元素中某个数据项，用以标识特定的数据元素
    - 主关键字(Primary Key)：唯一标识某个数据元素的关键字
    - 次关键字(Secondary Key)：能标识多个数据元素的关键字
- ASL：平均查找长度

## 二叉搜索树
### 初始化
```cpp
/* 创建一棵二叉树  */
void tree_create(treelink &T){
   while(1) {
       char data[MAX];
       scanf("%s", data);
       if (strcmp(data, "#") == 0)
           break;
       else
           node_insert(T, data);
   }
}
```
### 查找
- `指针p`指向当前访问结点的双亲，初始值为NULL
- 若**查找成功**，则`指针s`指向该数据元素的结点，函数值返回`true`
- 若**查找失败**，则`指针s`指向查找路径上访问的最后一个结点，函数值返回`false`
```cpp
/* 查找数据 */
bool node_find(treelink T, char  *name,treelink &p, treelink &s) {  //p为父结点 s为子结点
    if(T == NULL) {
        s = p;
        return false;
    } else if (strcmp(T->data, name) == 0) {
        s = T;
        return true;
    } else if (strcmp(T->data, name) > 0) {
        p = T;
        return node_find(T->left, name, p, s);
    } else {
        p = T;
        return node_find(T->right, name, p, s);
    }
}
```
### 插入
```cpp
/* 插入数据 */
void node_insert(treelink &T, char *name) {
   if (T == NULL) {
       T = new treenode;
       strcpy(T->data, name);
       T->left = T->right = NULL;
   } else if (strcmp(T->data, name) > 0) {
       node_insert(T->left, name);
   } else {
       node_insert(T->right, name);
   }
}
```
### 删除
- 若`p结点`既有**左子树**又有**右子树**
    1. 将`待删除结点p`的**右子树**链接到它的`中序前趋结点s`(即左子树下最右下结点)的右孩子指针域上
    2. 将`结点s`的**左子树**链接到其`双亲结点`的左(或右)孩子域上
```cpp
/* 删除数据 */
bool node_delete(treelink &T, char *name) {
    if (T == NULL) return false;
    else {
        if (strcmp(T->data, name) == 0) {
            Delete(T);
            return true;
        }
        else if (strcmp(T->data, name) > 0)
            return node_delete(T->left, name);
        else
            return node_delete(T->right, name);
    }
}

void Delete(treelink &p) {
    if (!p->right) {  //没有右子树
        treelink tmp = p;
        p = p->left;
        delete tmp;
    } else if (!p->left) {  //没有左子树
        treelink tmp = p;
        p = p->right;
        delete tmp;
    } else {  //左右子树都存在
        treelink q = p, s = q->left;  //s指向被删结点p的中序前驱，q指向s的双亲
        while(s->right) {
            q = s;
            s = s->right;
        }
        strcpy(p->data, s->data);  //用待删结点p的中序前趋结点s的值覆盖待删结点的值
        if (q != p)
            q->right = s->left;
        else  //以结点s为根的子树为结点p的左子树
            q->left = s->left;
        delete s;
    }
}
```
### 测试数据
```cpp
45 24 53 12 14 90 #
```
### 输出
```cpp
-----------------------+45(D)
---------------------+24(L)
-------------------+12(L)
-----------------+14(R)
---------------------+53(R)
-------------------+90(R)
```
## 二叉平衡树
### 构造
- 在构造二叉排序树的过程中，每当插入一个结点时，首先检查是否因插入而破坏了树的平衡性，如果是因插入结点而破坏了树的平衡性，则找出其中**最小不平衡子树**，在保持排序树特性的前提下，调整**最小不平衡子树**中各结点之间的连接关系，以达到新的平衡 
- 具体步骤：

        1. 每当插入一个新结点，从该结点开始向上计算各结点的平衡因子，即计算该结点的祖先结点的平衡因子，若该结点的祖先结点的平衡因子的绝对值均不超过1，则平衡二叉树没有失去平衡，继续插入结点

        2. 若插入结点的某祖先结点的平衡因子的绝对值大于1，则找出其中最小不平衡子树的根结点

        3. 判断新插入的结点与最小不平衡子树的根结点的关系，确定是哪种类型的调整

        4. 如果是LL型或RR型，只需应用扁担原理旋转一次，在旋转过程中，如果出现冲突，应用旋转优先原则调整冲突；如果是LR型或LR型，则需应用扁担原理旋转两次，第一次最小不平衡子树的根结点先不动，调整插入结点所在子树，第二次再调整最小不平衡子树，在旋转过程中，如果出现冲突，应用旋转优先原则调整冲突

        5. 计算调整后的平衡二叉树中各结点的平衡因子，检验是否因为旋转而破坏其他结点的平衡因子，以及调整后的平衡二叉树中是否存在平衡因子大于1的结点

#### 例
- 设有关键码序列{20, 35, 40, 15, 30, 25, 38}，图7-3给出了平衡二叉树的构造过程，结点旁边标出的是该结点的平衡因子
<div align="center"> <img src="https://git.acwing.com/ZagY/learn-data-structures/-/raw/main/Search/images/3.bmp" /> </div>
<div align="center"> <img src="https://git.acwing.com/ZagY/learn-data-structures/-/raw/main/Search/images/4.jpg" /> </div>
<div align="center"> <img src="https://git.acwing.com/ZagY/learn-data-structures/-/raw/main/Search/images/5.bmp" /> </div>
<div align="center"> <img src="https://git.acwing.com/ZagY/learn-data-structures/-/raw/main/Search/images/6.bmp" /> </div>

### 插入
- 不妨假设二叉排序树的最小不平衡子树的根结点为 A ，则调整该子树的规律可归纳为下列四种情况：

        1. LL 型：新结点 X 插在 A 的左孩子的左子树里。调整方法见图 (a) 。图中以 B 为轴心，将 A 结点从 B 的右上方转到 B 的右下侧，使 A 成为 B 的右孩子

        2. RR 型：新结点 X 插在 A 的右孩子的右子树里。调整方法见图 (b) 。图中以 B 为轴心，将 A 结点从 B 的左上方转到 B 的左下侧，使 A 成为 B 的左孩子

        3. LR 型：新结点 X 插在 A 的左孩子的右子树里。调整方法见图 (c) 。分为两步进行：第一步以 X 为轴心，将 B 从 X 的左上方转到 X 的左下侧，使 B 成为 X 的左孩子， X 成为 A 的左孩子。第二步跟 LL 型一样处理 ( 应以 X 为轴心 )
        
        4. RL 型：新结点 X 插在 A 的右孩子的左子树里。调整方法见图 (d) 。分为两步进行：第一步以 X 为轴心，将 B 从 X 的右上方转到 X 的右下侧，使 B 成为 X 的右孩子， X 成为 A 的右孩子。第二步跟 RR 型一样处理 ( 应以 X 为轴心 )

<div align="center"> <img src="https://git.acwing.com/ZagY/learn-data-structures/-/raw/main/Search/images/1.png" /> </div>

#### 例
- 设一组记录的关键字按以下次序进行插入： 4 、 5 、 7 ， 2 、 1 、 3 、 6 ，其生成及调整成二叉平衡树的过程👇
<div align="center"> <img src="https://git.acwing.com/ZagY/learn-data-structures/-/raw/main/Search/images/2.png" /> </div>

