#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<conio.h>
#include<stack>
#define MAX 10

using namespace std;

typedef struct treenode {
    char data[MAX];
    struct treenode *left;
    struct treenode *right;
}treenode, *treelink;

typedef struct {
    treelink *elem;
    int front,rear;
    int queuesize;
}XhQueue;

int menu();  /* 菜单 */
void tree_create(treelink &T);  /* 创建一棵二叉树  */
void preorder_traversal(treelink T);  /* 前序遍历 */
void inorder_traversal(treelink T);  /* 中序遍历 */
void postorder_traversal(treelink T);  /* 后序遍历 */
void levelorder_traversal(treelink T);  /* 层序遍历 */
int get_depth(treelink T);  /* 求二叉树深度 */
void leaf_count(treelink T, int &count);  /* 求叶节点个数 */
void node_count(treelink T, int &num);  /*求结点个数 */
void disp_tree(treelink T, int level, char c);  /* 凹入表显示 */
void InitQueue(XhQueue &Q);
void EnQueue(XhQueue &Q, treelink p);
void DeQueue(XhQueue &Q,treelink &p);
void GetHead(XhQueue &Q,treelink &p);
int EmQueue(XhQueue Q);
int LengthQueue(XhQueue Q);


int main() {
    int n;
    int dep = 0;  //二叉树深度
    int leafcnt = 0;  //叶节点个数
    int nodecnt = 0;  //结点个数
    treelink T;

    while (1) {
        n = menu();
        switch(n) {
            case 1:
                printf("请输入二叉树的节点：");
                tree_create(T);
                printf("按任意键继续!\n");
                getch(); break;
            case 2:
                preorder_traversal(T);
                printf("\n按任意键继续!\n");
                getch(); break;
            case 3:
                inorder_traversal(T);
                printf("\n按任意键继续!\n");
                getch(); break;
            case 4:
                postorder_traversal(T);
                printf("\n按任意键继续!\n");
                getch(); break;
            case 5:
                levelorder_traversal(T);
                printf("\n按任意键继续!\n");
                getch(); break;
            case 6:
                disp_tree(T, get_depth(T), 'D');
                printf("按任意键继续!\n");
                getch(); break;
            case 8:
                dep = get_depth(T);
                printf("深度为：%d\n", dep);
                printf("\n按任意键继续!\n");
                getch(); break;

            case 9:
                leafcnt = 0;
                leaf_count(T, leafcnt);
                printf("叶子结点个数为：%d\n", leafcnt);
                printf("按任意键继续!\n");
                getch(); break;
            case 10:
                nodecnt = 0;
                node_count(T, nodecnt);
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
        printf("\t7.广义表表示(未完成)\n");  //未完成
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
void tree_create(treelink &T){
    char data[MAX];
    scanf("%s", data);
    if (strcmp(data, "#") == 0) T = NULL;
    else {
        T = new treenode;
        strcpy(T->data, data);
        tree_create(T->left);
        tree_create(T->right);
    }
}

/* 前序遍历 */
void preorder_traversal(treelink T) {
    if (T == NULL) return ;
    printf("%s ", T->data);
    preorder_traversal(T->left);
    preorder_traversal(T->right);
}

/* 中序遍历 */
void inorder_traversal(treelink T) {
    if (T == NULL) return ;
    inorder_traversal(T->left);
    printf("%s ", T->data);
    inorder_traversal(T->right);
}

/* 后序遍历 */
void postorder_traversal(treelink T) {
    if (T == NULL) return ;
    postorder_traversal(T->left);
    postorder_traversal(T->right);
    printf("%s ", T->data);
}

/* 层序遍历 */
void levelorder_traversal(treelink T) {
    XhQueue Q;
    InitQueue(Q);
    EnQueue(Q, T);
    if (T == NULL) return ;
    while (!EmQueue(Q)) {
        int size = LengthQueue(Q);
        for (int i = 0; i < size; i++) {
            treelink cur;
            DeQueue(Q, cur);
            printf("%s ", cur->data);
            if (cur->left != NULL) EnQueue(Q, cur->left);
            if (cur->right != NULL) EnQueue(Q, cur->right);
        }
        puts("");
    }
}

/* 求二叉树深度 */
int get_depth(treelink T) {
    if (T == NULL) return 0;
    else {
        int L = get_depth(T->left);
        int R = get_depth(T->right);
        if (L > R) return (L + 1);
        else return (R + 1);
    }
}

/* 求叶节点个数 */
void leaf_count(treelink T, int &count) {
    if (T == NULL) return ;
    else {
        leaf_count(T->left, count);
        if (T->left == NULL && T->right == NULL) count++;
        leaf_count(T->right, count);
    }
}

/*求结点个数 */
void node_count(treelink T, int &num) {
    if (T == NULL) return ;

    node_count(T->left, num);
    num++;
    node_count(T->right, num);
}

/* 凹入表显示 */
void disp_tree(treelink T, int level, char c) { //level为T结点的高度，c为树根的标志，如"D"
    if (T == NULL) return ;

    for(int i = 1; i < level + 20; i++)
        putchar('-');

    putchar('+');
    printf("%s(%c)\n",T->data,c);
    level = level - 2;
    disp_tree(T->left,level,'L');
    disp_tree(T->right,level,'R');
}

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
