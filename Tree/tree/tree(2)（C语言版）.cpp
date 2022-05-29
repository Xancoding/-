#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<conio.h>
#define MAX 10  //结点个数
#define NUM 10  //字符串长度

using namespace std;

typedef struct treenode {
    char data[NUM];
    struct treenode *child;  //第一个孩子
    struct treenode *sibling;  //下一个兄弟
}treenode, *treelink;

typedef struct {
    treelink *elem;
    int front,rear;
    int queuesize;
}XhQueue;

typedef struct stack {
    char data[MAX][NUM];  //data是一个指针变量，存放一片连续空间的首地址
    int top;  //指示栈顶的位置 
    int stackSize;  //栈的容量 
}SqStack;

int menu();  /* 菜单 */
void tree_create(treelink &T);  /* 创建一棵树  */
int get_depth(treelink T);  /* 求树深度 */
void disp_tree(treelink T, int level);  /* 凹入表显示 */
void all_tree_path(treelink T, SqStack S); /* 求所有叶子结点路径 */
void preorder_traversal(treelink T);  /* 先根遍历 */
void postorder_traversal(treelink T); /* 后根遍历 */
void levelorder_traversal(treelink T);  /*层次遍历 */
void Path(treelink pTree, SqStack S, char data[]);  /* 路径 */
treelink node_find1(treelink T, char *data);  /* 查找 */
void get_follow(treelink T, char *s);  /* 子结点输出 */
void InitQueue(XhQueue &Q);
void EnQueue(XhQueue &Q, treelink p);
void DeQueue(XhQueue &Q,treelink &p);
void GetQueueHead(XhQueue &Q,treelink &p);
int EmQueue(XhQueue Q);
int LengthQueue(XhQueue Q);
void InitSqStack(SqStack &S);
void PushSqStack(SqStack &S,char *data);
void PopSqStack(SqStack &S);
void TraversSqStack(SqStack S);
void GetStackHead(SqStack &S, char* &p);
int EmSqStack(SqStack S);

int main() {
    int n;
    char str[MAX];
    treelink T;
    SqStack S;

    while (1) {
        n = menu();
        switch(n) {
            case 1:
                printf("请输入树的节点：");
                tree_create(T);
                printf("按任意键继续!\n");
                getch(); break;
            case 2:
                levelorder_traversal(T);
                puts("");
                printf("按任意键继续!\n");
                getch(); break;
            case 3:
                preorder_traversal(T);
                puts("");
                printf("按任意键继续!\n");
                getch(); break;
            case 4:
                postorder_traversal(T);
                puts("");
                printf("按任意键继续!\n");
                getch(); break;
            case 5:
                disp_tree(T, get_depth(T));
                printf("按任意键继续!\n");
                getch(); break;
            case 6:
                InitSqStack(S);
                all_tree_path(T, S);
                printf("按任意键继续!\n");
                getch(); break;
            case 7:
                InitSqStack(S);
                printf("请输入节点名: ");
                scanf("%s", str);
                Path(T, S, str);
                printf("按任意键继续!\n");
                getch(); break;
            case 8:
                printf("请输入节点名: ");
                scanf("%s", str);
                get_follow(T, str);
                puts("");
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
        printf("\t1.创建树\n");
        printf("\t2.层序遍历\n");
        printf("\t3.先根遍历\n");
        printf("\t4.后根遍历\n");
        printf("\t5.凹入表表示\n");
        printf("\t6.求所有叶子结点路径\n");
        printf("\t7.路径\n");
        printf("\t8.子结点\n");
        printf("************************\n");
        printf("请输入数字：");
        scanf("%d", &n);
        if (n > 8 || n < 0) {
            printf("输入错误，请重新输入！\n");
        } else return n;
    }
}

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

/* 求树深度 */
int get_depth(treelink T) {
    if (T == NULL) return 0;
    else {
        int d1 = get_depth(T->child);
        int d2 = get_depth(T->sibling);
        return d1 + 1 > d2 ? d1 + 1 : d2;
    }
}

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

/* 先根遍历 */
void preorder_traversal(treelink T) {
    if (T == NULL) return ;
    printf("%s ", T->data);
    preorder_traversal(T->child);
    preorder_traversal(T->sibling);
}

/* 后根遍历 */
void postorder_traversal(treelink T) {
    if (T == NULL) return ;
    preorder_traversal(T->child);
    preorder_traversal(T->sibling);
    printf("%s ", T->data);
}

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

/* 路径 */
void Path(treelink pTree, SqStack S, char data[]) {
    if (pTree) {
        PushSqStack(S, pTree->data);
        if (strcmp(pTree->data, data) == 0) TraversSqStack(S);
        else Path(pTree->child, S, data);
        PopSqStack(S);
        Path(pTree->sibling, S, data);
    }
}

/* 求所有叶子结点路径 */
void all_tree_path(treelink T, SqStack S) {
    while (T) {
        PushSqStack(S, T->data);
        if (!T->child) TraversSqStack(S);  //T是叶子结点
        else all_tree_path(T->child, S);  //找以T为根的子树上的叶子结点路径
        PopSqStack(S);  //栈顶结点是叶子结点或以栈顶结点为根的子树上的叶子路径已完成
        T = T->sibling;     //继续找T的其余子树
    }
}

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

/* 子结点输出 */
void get_follow(treelink T, char *s) {
    T = node_find1(T, s);

    if (T == NULL) return ;
    T = T->child;
    while (T != NULL) {
        printf("%s ", T->data);
        T = T->sibling;
    }
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

void GetQueueHead(XhQueue &Q,treelink &p){
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

void InitSqStack(SqStack &S) {
    S.top = -1;  //约定栈空时S.top=-1
    S.stackSize = MAX;
}

void PushSqStack(SqStack &S,char *data) {
    if(S.stackSize != S.top + 1)
       strcpy(S.data[++S.top], data);
}

void PopSqStack(SqStack &S) {
    if(S.top != -1)
        S.top--;
}

void TraversSqStack(SqStack S) {
    if(S.top != -1)
        for(int i = 0; i <= S.top; i++)
            printf("/%s",S.data[i]);
    printf("\n");

}

void GetStackHead(SqStack &S, char* &p){
    if(S.top != -1)
        strcpy(p, S.data[S.top]);
}

int EmSqStack(SqStack S){
    if (S.top != -1) return 0;
    else return 1;
}
