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
} treenode, *treelink;

/* 凹入表显示 */
void disp_tree(treelink T, int level, char c) { //level为T结点的高度，c为树根的标志，如"D"
    if (T == NULL) return ;

    for(int i = 1; i < level + 20; i++)
        putchar('-');

    putchar('+');
    printf("%c(%c)\n",T->data,c);
    level = level - 2;
    disp_tree(T->left,level,'L');
    disp_tree(T->right,level,'R');
}

treelink buildTree(int pl, int pr, int ml, int mr) {
    if (pl > pr) return NULL;

    treelink T = (treelink)malloc(sizeof(treenode));
    T->data = pre[pl];

    int pos = 0;
    for (pos = ml; pos <= mr; pos++)
        if (mid[pos] == pre[pl]) break;

    T->left = buildTree(pl + 1, pl + pos - ml, ml, pos - 1);
    T->right = buildTree(pl + pos - ml + 1, pr, pos + 1, mr);

    return T;
}

int get_depth(treelink T) {
    if (T == NULL) return 0;
    else {
        int L = get_depth(T->left);
        int R = get_depth(T->right);
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
    treelink T = buildTree(0, n - 1, 0, m - 1);
    printf("该二叉树的凹入表为：\n");
    disp_tree(T, get_depth(T), 'D');
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
} treenode, *treelink;

/* 凹入表显示 */
void disp_tree(treelink T, int level, char c) { //level为T结点的高度，c为树根的标志，如"D"
    if (T == NULL) return ;

    for(int i = 1; i < level + 20; i++)
        putchar('-');

    putchar('+');
    printf("%c(%c)\n",T->data,c);
    level = level - 2;
    disp_tree(T->left,level,'L');
    disp_tree(T->right,level,'R');
}

treelink buildTree(int pl, int pr, int ml, int mr) {
    if (pl > pr) return NULL;

    treelink T = (treelink)malloc(sizeof (treenode));
    T->data = post[pr];

    int pos = 0;
    for (pos = ml; pos <= mr; pos++)
        if (mid[pos] == post[pr]) break;

    T->left = buildTree(pl, pl + pos - ml - 1, ml, pos - 1);
    T->right = buildTree(pl + pos - ml, pr - 1, pos + 1, mr);

    return T;
}

int get_depth(treelink T) {
    if (T == NULL) return 0;
    else {
        int L = get_depth(T->left);
        int R = get_depth(T->right);
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
    treelink T = buildTree(0, n - 1, 0, m - 1);
    printf("该二叉树的凹入表为：\n");
    disp_tree(T, get_depth(T), 'D');
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
