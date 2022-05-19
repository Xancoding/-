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
    struct treenode *child;  //第一个孩子 
    struct treenode *sibling;  //下一个兄弟 
}treenode, *treelink;

int menu();  /* 菜单 */
void tree_create(treelink &root);  /* 创建一棵二叉树  */
int get_depth(treelink root);  /* 求树深度 */
void disp_tree(treelink root, int level);  /* 凹入表显示 */
treelink node_find1(treelink root, char *name);  /* 查找 */
void node_find2(treelink pTree, char  *szName, treelink &pLast, treelink &p1, treelink &p2);  /* 查找 */
void Destroy(treelink &p);   /* 销毁树 */
void node_delete(treelink &Root, char *name);  /* 删除数据 */
void node_insert(treelink Root, char *pname, char *cname);  /* 插入数据 */



int main() {
    int n;
    int dep = 0;  //树深度
    char str[MAX];
    char str1[MAX];
    char str2[MAX];
    treelink root;
    treelink p;
    
    while (1) {
        n = menu();
        switch(n) {
            case 1:
                printf("请输入树的节点：");
                tree_create(root);
                printf("按任意键继续!\n");
                getch(); break;
            case 2:
                printf("请输入查找结点名：");
                scanf("%s", str);
                p = node_find1(root,str);
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
                disp_tree(root, get_depth(root));
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
        printf("\t2.查找数据\n");
        printf("\t3.删除数据\n");
        printf("\t4.插入数据\n");
        printf("\t5.销毁树\n");
        printf("\t6.凹入表表示\n");
        printf("************************\n");
        printf("请输入数字：");
        scanf("%d", &n);
        if (n > 6 || n < 0) {
            printf("输入错误，请重新输入！\n");
        } else return n;
    }
}

/* 创建一棵树  */
void tree_create(treelink &root) {
    char data[MAX];
    scanf("%s", data);
    if (strcmp(data, "#") == 0) root = NULL;
    else {
        root = new treenode;
        strcpy(root->data, data);
        tree_create(root->child);
        tree_create(root->sibling);
    }
}

/* 销毁二叉树 */
void Destroy(treelink &p) {
    if(p) {
        Destroy(p->child);
        Destroy(p->sibling);
        delete p;
        p = NULL;
    }
}

/* 求二叉树深度 */
int get_depth(treelink root) {
    if (root == NULL) return 0;
    else {
        int d1 = get_depth(root->child);
        int d2 = get_depth(root->sibling);
        return d1 + 1 > d2 ? d1 + 1 : d2;
    }
}

/* 凹入表显示 */
void disp_tree(treelink root, int level) { //level为root结点的高度
    if (root == NULL) return ;

    for(int i = 1; i < level + 20; i++)
        putchar('-');

    putchar('+');
    printf("%s\n",root->data);
    disp_tree(root->child,level - 2);
    disp_tree(root->sibling, level);
}

/* 查找 */
treelink node_find1(treelink root, char *name) {

    treenode *p;
    if(root == NULL) return NULL;
    else{
        if(strcmp(root->data, name)==0)
            return root;
        else if(p = node_find1(root->child, name))
            return p;
        else
            return node_find1(root->sibling, name);
    }
}
void node_find2(treelink pTree, char  *szName, treelink &pLast, treelink &p1, treelink &p2) {
    if(pTree == NULL) return;
    if(strcmp(pTree->data, szName) == 0){  //找到则返回父节点指针和当前节点指针
        p2 = pTree;  //当前节点
        p1 = pLast;  //父节点
    }
    else{
        //pLast = pTree;//暂存上一级节点指针
        node_find2(pTree->child, szName, pTree, p1, p2);
        //pLast = pTree;
        node_find2(pTree->sibling, szName, pTree, p1, p2);
    }
}

/* 插入 */
void node_insert(treelink pTree, char  *szParent, char  *szNew)
{
    treelink pFind= NULL;
    treelink pChild = NULL;
    treelink parent;  //待查找结点的父结点
    pFind = node_find1(pTree, szParent);

    if(pFind){
        pChild = pFind->child;
        while(pChild!=NULL){
            if(strcmp(pChild->data,szNew)==0){
                printf("子节点已存在！\n");
                return;
            }else
                pChild = pChild->sibling;
        }

        treelink pNew = new treenode;
        strcpy(pNew->data, szNew);
        if(pFind->child){
            pNew->sibling = pFind->child;
            pNew->child = NULL;
        }else{
            pNew->child = NULL;
            pNew->sibling = NULL;
        }
        pFind->child = pNew;
    }else
        printf("父节点不存在!\n");

}

/* 删除 */
void node_delete(treelink &pTree, char  *szName){
    treelink pFind = NULL, pParent = NULL, p = NULL;

    node_find2(pTree, szName, p, pParent, pFind);

    if(pFind){
        if(pParent == NULL){//删除根节点
            Destroy(pTree);
            pTree = NULL;
        }else{
            if(pParent->child == pFind)//删除孩子节点
                pParent->child = pFind->sibling;
            else//删除兄弟节点
                pParent->sibling = pFind->sibling;

            pFind->sibling = NULL;//摘除当前节点
            Destroy(pFind);//删除当前节点
        }
    }else
        printf("指定删除节点不存在!\n");
}
