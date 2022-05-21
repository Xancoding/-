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

int menu();  /* 菜单 */
void tree_create(treelink &T);  /* 创建一棵二叉树  */
int get_depth(treelink T);  /* 求二叉树深度 */
void disp_tree(treelink T, int level, char c);  /* 凹入表显示 */
treelink node_find(treelink T, char *data);  /* 查找 */
void Destroy(treelink &p);   /* 销毁二叉树 */
void node_delete(treelink &T, char *data);  /* 删除数据 */
void node_insert(treelink T, char *pdata, char *cdata);  /* 插入数据 */

int main() {
    int n;
    int dep = 0;  //二叉树深度
    char str[MAX];
    char str1[MAX];
    char str2[MAX];
    treelink T;
    treelink p;

    while (1) {
        n = menu();
        switch(n) {
            case 1:
                printf("请输入二叉树的节点：");
                tree_create(T);
                printf("按任意键继续!\n");
                getch(); break;
            case 2:
                printf("请输入查找结点名：");
                scanf("%s", str);
                p = node_find(T,str);
                if(p != NULL)
                    printf("\nnode addr = %x\nnode val = %s\n",p,p->data);
                else
                    printf("没找到结点\n");

                printf("按任意键继续!\n");
                getch(); break;
            case 3:
                printf("请输入结点名：");
                scanf("%s", str);
                node_delete(T, str);
                printf("按任意键继续!\n");
                getch(); break;
            case 4:
                printf("请输入父结点名、新结点名字(中间用空格隔开)：");
                scanf("%s %s", str1, str2);
                node_insert(T, str1, str2);
                printf("按任意键继续!\n");
                getch(); break;
            case 5:
                Destroy(T);
                printf("按任意键继续!\n");
                getch(); break;
            case 6:
                disp_tree(T, get_depth(T), 'D');
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
        printf("\t1.创建二叉树\n");
        printf("\t2.查找数据\n");
        printf("\t3.删除数据\n");
        printf("\t4.插入数据\n");
        printf("\t5.销毁二叉树\n");
        printf("\t6.凹入表表示\n");
        printf("************************\n");
        printf("请输入数字：");
        scanf("%d", &n);
        if (n > 6 || n < 0) {
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

/* 查找数据 */
treelink node_find(treelink T, char *data)
{
    treelink p;
    if(T == NULL) return NULL;
    else{
        printf("%s ", T->data);
        if(strcmp(T->data, data)==0)
            return T;
        else if(p = node_find(T->left, data))
            return p;
        else
            return node_find(T->right, data);
    }
}

/* 销毁二叉树 */
void Destroy(treelink &p) {
    if(p) {
        Destroy(p->left);
        Destroy(p->right);
        delete p;
        p = NULL;
    }
}

/* 删除数据 */
void node_delete(treelink &T, char *data) {

    if(T){
        if(strcmp(T->data,data)==0){
            Destroy(T);
            T = NULL;
        }
        else{
            node_delete(T->left, data);
            node_delete(T->right, data);
        }
    }
}

/* 插入数据 */
void node_insert(treelink T, char *pdata, char *cdata) {
    treelink parent, pnew;
    parent = node_find(T, pdata);
    if(parent==NULL){
        printf("父结点不存在\n");
        return;
    }else{
        if(parent->left && parent->right){
            printf("子结点已满\n");
            return;
        }

        if(parent->left){
            if(strcmp(parent->left->data,cdata)==0){
                printf("同名子结点已存在\n");
                return;
            }
        }
        if(parent->right){
            if(strcmp(parent->right->data, cdata)==0){
                printf("同名子结点已存在\n");
                return;
            }
        }

        pnew = new treenode;  pnew->left = pnew->right =NULL;
        strcpy(pnew->data, cdata);
        /* 优先插入左结点 */
        if(parent->left == NULL)
            parent->left = pnew;
        else
            parent->right = pnew;

    }
}
