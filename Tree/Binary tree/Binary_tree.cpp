#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<conio.h>
#include<stack>
#include<queue>
#define MAX 10

using namespace std;

typedef struct treenode {
    char data[MAX];
    struct treenode *left;
    struct treenode *right;
}treenode;

int menu();  /* 菜单 */
void tree_create(treenode* &root);  /* 创建一棵二叉树  */
void preorder_traversal(treenode *root);  /* 前序遍历 */
void inorder_traversal(treenode *root);  /* 中序遍历 */
void postorder_traversal(treenode *root);  /* 后序遍历 */
void levelorder_traversal(treenode* root);  /* 层序遍历 */
int get_depth(treenode *root);  /* 求二叉树深度 */
void leaf_count(treenode *root, int &count);  /* 求叶节点个数 */
void node_count(treenode *root, int &num);  /*求结点个数 */
void disp_tree(treenode *root, int level, char c);  /* 凹入表显示 */

int main() {
    int n;
    int dep = 0;  //二叉树深度
    int leafcnt = 0;  //叶节点个数
    int nodecnt = 0;  //结点个数
    treenode *root;

    while (1) {
        n = menu();
        switch(n) {
            case 1:
                printf("请输入二叉树的节点：");
                tree_create(root);
                printf("按任意键继续!\n");
                getch(); break;
            case 2:
                preorder_traversal(root);
                printf("\n按任意键继续!\n");
                getch(); break;
            case 3:
                inorder_traversal(root);
                printf("\n按任意键继续!\n");
                getch(); break;
            case 4:
                postorder_traversal(root);
                printf("\n按任意键继续!\n");
                getch(); break;
            case 5:
                levelorder_traversal(root);
                printf("\n按任意键继续!\n");
                getch(); break;
            case 6:
                disp_tree(root, get_depth(root), 'D');
                printf("按任意键继续!\n");
                getch(); break;
            case 8:
                dep = get_depth(root);
                printf("深度为：%d\n", dep);
                printf("\n按任意键继续!\n");
                getch(); break;

            case 9:
                leaf_count(root, leafcnt);
                printf("叶子结点个数为：%d\n", leafcnt);
                printf("按任意键继续!\n");
                getch(); break;
            case 10:
                node_count(root, nodecnt);
                printf("结点个数为：%d\n", nodecnt);
                printf("按任意键继续!\n");
                getch(); break;
        }
    }
}

/* 菜单 */
int menu() {
    int n;
    while (1) {
        system("cls");
        printf("*****欢迎使用本系统*****\n");
        printf("\t1.构建二叉树（先序遍历）\n");
        printf("\t2.先序遍历\n");
        printf("\t3.中序遍历\n");
        printf("\t4.后序遍历\n");
        printf("\t5.层序遍历\n");
        printf("\t6.凹入表表示\n");
        printf("\t7.广义表表示\n");
        printf("\t8.求二叉树的深度\n");
        printf("\t9.求二叉树的叶子结点数\n");
        printf("\t10.求二叉树的结点数\n");
        printf("************************\n");
        printf("请输入数字：");
        scanf("%d", &n);
        if (n > 10 || n < 0) {
            printf("输入错误，请重新输入！\n");
        } else return n;
    }
}

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

/* 层序遍历 */
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
}

/* 求二叉树深度 */
int get_depth(treenode *root) {
    if (root == NULL) return 0;
    else {
        int L = get_depth(root->left);
        int R = get_depth(root->right);
        if (L > R) return (L + 1);
        else return (R + 1);
    }
}

/* 求叶节点个数 */
void leaf_count(treenode *root, int &count) {
    if (root == NULL) return ;
    else {
        leaf_count(root->left, count);
        if (root->left == NULL && root->right == NULL) count++;
        leaf_count(root->right, count);
    }
}

/*求结点个数 */
void node_count(treenode *root, int &num) {
    if (root == NULL) return ;

    node_count(root->left, num);
    num++;
    node_count(root->right, num);
}

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
