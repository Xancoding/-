### 由先序序列和中序序列确定二叉树
```cpp
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#define MAX 100

char pre[MAX];
char mid[MAX];

typedef struct Node {
    char data;
    struct Node *left;
    struct Node *right;
} Node; 

void traversal(Node *root) {
    if (root == NULL) return ;
    
    traversal(root->left);
    traversal(root->right);
    printf("%c", root->data);
}

Node *buildTree(int pl, int pr, int ml, int mr) {
    if (pl > pr) return NULL;
    
    Node *root = (Node*)malloc(sizeof(Node));
    root->data = pre[pl];
    
    int pos = 0;
    for (pos = ml; pos <= mr; pos++)
    	if (mid[pos] == pre[pl]) break;
    
    root->left = buildTree(pl + 1, pl + pos - ml, ml, pos - 1);
    root->right = buildTree(pl + pos - ml + 1, pr, pos + 1, mr);
    
    return root;
}


int main() { 
    printf("请输入二叉树的前序遍历：");
    scanf("%s", pre);

    printf("请输入二叉树的中序遍历：");
    scanf("%s", mid);
	
    int n = strlen(pre), m = strlen(mid);
    Node *root = buildTree(0, n - 1, 0, m - 1);
    printf("该二叉树的后序遍历为：");
    traversal(root);
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

typedef struct Node {
    char data;
    struct Node *left;
    struct Node *right;
} Node; 

void preorder_traversal(Node *root) {
    if (root == NULL ) return ;
	
    printf("%c", root->data);
    if (root->left != NULL) preorder_traversal(root->left);
    if (root->right!= NULL) preorder_traversal(root->right);	
}


Node *buildTree(int pl, int pr, int ml, int mr) {
    if (pl > pr) return NULL;
    
    Node *root = (Node*)malloc(sizeof (Node));
    root->data = post[pr];
    
    int pos = 0;
    for (pos = ml; pos <= mr; pos++)
    	if (mid[pos] == post[pr]) break;
    
    root->left = buildTree(pl, pl + pos - ml - 1, ml, pos - 1);
    root->right = buildTree(pl + pos - ml, pr - 1, pos + 1, mr);
    
    return root;
}


int main() { 
    printf("请输入二叉树的后序遍历：");
    scanf("%s", post);

    printf("请输入二叉树的中序遍历：");
	scanf("%s", mid);
	
    int n = strlen(post), m = strlen(mid);
    Node *root = buildTree(0, n - 1, 0, m - 1);
    printf("该二叉树前序遍历为：");
    preorder_traversal(root);
    puts("");
}
```
### 测试数据
```cpp
构造二叉树 A B D # # E  # # C # F # # 

前序遍历   A B D E C F

中序遍历   D B E A C F

后序遍历   D E B F C A
```
