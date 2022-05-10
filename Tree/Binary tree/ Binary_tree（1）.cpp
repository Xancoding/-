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
}treenode, *treelink;

int menu();  /* 菜单 */
void tree_create(treelink &root);  /* 创建一棵二叉树  */
int get_depth(treelink root);  /* 求二叉树深度 */
void disp_tree(treelink root, int level, char c);  /* 凹入表显示 */
treelink node_find(treelink root, char *name);  /* 查找 */
void Destroy(treelink &p);   /* 销毁二叉树 */
void node_delete(treelink &Root, char *name);  /* 删除数据 */
void node_insert(treelink Root, char *pname, char *cname);  /* 插入数据 */


int main() {
    int n;
    int dep = 0;  //二叉树深度
    char str[MAX];
    char str1[MAX];
    char str2[MAX];
    treelink root;

    while (1) {
        n = menu();
        switch(n) {
            case 1:
                printf("请输入二叉树的节点：");
                tree_create(root);
                printf("按任意键继续!\n");
                getch(); break;
            case 2:
                printf("请输入查找结点名：");
                scanf("%s", str);
                treelink p = node_find(root,str);
                if(p != NULL)
                    printf("\nnode addr = %x\nnode val = %s\n",p,p->data);
                else
                    printf("没找到结点\n");

                printf("按任意键继续!\n");
                getch(); break;
            case 3:
                printf("请输入结点名：");
                scanf("%s", str);
                node_delete(root, str);
                printf("按任意键继续!\n");
                getch(); break;
            case 4:
                printf("请输入父结点名、新结点名字(中间用空格隔开)：");
                scanf("%s %s", str1, str2);
                node_insert(root, str1, str2);
                printf("按任意键继续!\n");
                getch(); break;
            case 5:
                Destroy(root);
                printf("按任意键继续!\n");
                getch(); break;
            case 6:
                disp_tree(root, get_depth(root), 'D');
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
void tree_create(treelink &root){
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


/* 求二叉树深度 */
int get_depth(treelink root) {
    if (root == NULL) return 0;
    else {
        int L = get_depth(root->left);
        int R = get_depth(root->right);
        if (L > R) return (L + 1);
        else return (R + 1);
    }
}

/* 凹入表显示 */
void disp_tree(treelink root, int level, char c) { //level为root结点的高度，c为树根的标志，如"D"
    if (root == NULL) return ;

    for(int i = 1; i < level + 20; i++)
        putchar('-');

    putchar('+');
    printf("%s(%c)\n",root->data,c);
    level = level - 2;
    disp_tree(root->left,level,'L');
    disp_tree(root->right,level,'R');
}

/* 查找数据 */
treelink node_find(treelink root, char *name)
{
    treelink p;
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
void node_delete(treelink &Root, char *name) {

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

/* 插入数据 */
void node_insert(treelink Root, char *pname, char *cname) {
    treelink parent, pnew;
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
