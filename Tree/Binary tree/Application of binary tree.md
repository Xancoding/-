### 由先序序列和中序序列确定二叉树
```cpp
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#define MAX 100

char pre[MAX];
char mid[MAX];

typedef struct treenode {
    char data;
    struct treenode *left;
    struct treenode *right;
} treenode;

/* 凹入表显示 */
void disp_tree(treenode *root, int level, char c) { //level为root结点的高度，c为树根的标志，如"D"
    if (root == NULL) return ;

    for(int i = 1; i < level + 20; i++)
        putchar('-');

    putchar('+');
    printf("%c(%c)\n",root->data,c);
    level = level - 2;
    disp_tree(root->left,level,'L');
    disp_tree(root->right,level,'R');
}

treenode *buildTree(int pl, int pr, int ml, int mr) {
    if (pl > pr) return NULL;

    treenode *root = (treenode*)malloc(sizeof(treenode));
    root->data = pre[pl];

    int pos = 0;
    for (pos = ml; pos <= mr; pos++)
        if (mid[pos] == pre[pl]) break;

    root->left = buildTree(pl + 1, pl + pos - ml, ml, pos - 1);
    root->right = buildTree(pl + pos - ml + 1, pr, pos + 1, mr);

    return root;
}

int get_depth(treenode *root) {
    if (root == NULL) return 0;
    else {
        int L = get_depth(root->left);
        int R = get_depth(root->right);
        if (L > R) return (L + 1);
        else return (R + 1);
    }
}

int main() {
    printf("请输入二叉树的前序遍历：");
    scanf("%s", pre);

    printf("请输入二叉树的中序遍历：");
    scanf("%s", mid);

    int n = strlen(pre), m = strlen(mid);
    treenode *root = buildTree(0, n - 1, 0, m - 1);
    printf("该二叉树的凹入表为：");
    disp_tree(root, get_depth(root), 'D');
    puts("");
}
```
### 由后序序列和中序序列确定二叉树
```cpp
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#define MAX 100

char post[MAX];
char mid[MAX];

typedef struct treenode {
    char data;
    struct treenode *left;
    struct treenode *right;
} treenode;

/* 凹入表显示 */
void disp_tree(treenode *root, int level, char c) { //level为root结点的高度，c为树根的标志，如"D"
    if (root == NULL) return ;

    for(int i = 1; i < level + 20; i++)
        putchar('-');

    putchar('+');
    printf("%c(%c)\n",root->data,c);
    level = level - 2;
    disp_tree(root->left,level,'L');
    disp_tree(root->right,level,'R');
}

treenode *buildTree(int pl, int pr, int ml, int mr) {
    if (pl > pr) return NULL;

    treenode *root = (treenode*)malloc(sizeof (treenode));
    root->data = post[pr];

    int pos = 0;
    for (pos = ml; pos <= mr; pos++)
        if (mid[pos] == post[pr]) break;

    root->left = buildTree(pl, pl + pos - ml - 1, ml, pos - 1);
    root->right = buildTree(pl + pos - ml, pr - 1, pos + 1, mr);

    return root;
}

int get_depth(treenode *root) {
    if (root == NULL) return 0;
    else {
        int L = get_depth(root->left);
        int R = get_depth(root->right);
        if (L > R) return (L + 1);
        else return (R + 1);
    }
}

int main() {
    printf("请输入二叉树的后序遍历：");
    scanf("%s", post);

    printf("请输入二叉树的中序遍历：");
    scanf("%s", mid);

    int n = strlen(post), m = strlen(mid);
    treenode *root = buildTree(0, n - 1, 0, m - 1);
    printf("该二叉树的凹入表为：");
    disp_tree(root, get_depth(root), 'D');
    puts("");
}
```
### 测试数据
```cpp
构造二叉树 A B D # # E  # # C # F # # 

前序遍历   ABDECF

中序遍历   DBEACF

后序遍历   DEBFCA

凹入表显示
----------------------+A(D)
--------------------+B(L)
------------------+D(L)
------------------+E(R)
--------------------+C(R)
------------------+F(R)
```
