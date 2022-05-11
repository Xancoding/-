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
void all_tree_path(treelink T, stack<char*>st); /* 求所有叶子结点路径 */
void print_stack(stack<char*>st);  /* 遍历输出栈中数据 */
void preorder_traversal(treelink root);  /* 先根遍历 */
void postorder_traversal(treelink root); /* 后根遍历 */
void levelorder_traversal(treelink root);  /*层次遍历 */
void Path(treelink pTree, stack<char*>&st, char  *szName);  /* 路径 */
treelink node_find1(treelink root, char *name);  /* 查找 */
void get_follow(treelink T, char *s);  /* 子结点输出 */

int main() {
    int n;
    int dep = 0;  //树深度
    char str[MAX];
    char str1[MAX];
    char str2[MAX];
    treelink root;
    stack<char*>st;

    while (1) {
        n = menu();
        switch(n) {
            case 1:
                printf("请输入树的节点：");
                tree_create(root);
                printf("按任意键继续!\n");
                getch(); break;
            case 2:
                levelorder_traversal(root);
                puts("");
                printf("按任意键继续!\n");
                getch(); break;
            case 3:
                preorder_traversal(root);
                puts("");
                printf("按任意键继续!\n");
                getch(); break;
            case 4:
                postorder_traversal(root);
                puts("");
                printf("按任意键继续!\n");
                getch(); break;
            case 5:
                disp_tree(root, get_depth(root));
                printf("按任意键继续!\n");
                getch(); break;
            case 6:
                all_tree_path(root, st);
                printf("按任意键继续!\n");
                getch(); break;
            case 7:
                printf("请输入节点名: ");
                scanf("%s", str);
                Path(root, st, str);
                printf("按任意键继续!\n");
                getch(); break;
            case 8:
                printf("请输入节点名: ");
                scanf("%s", str);
                get_follow(root, str);
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

/* 求所有叶子结点路径 */
void all_tree_path(treelink T, stack<char*>st) {
    while (T) {
        st.push(T->data);
        if (!T->child) print_stack(st);  //T是叶子结点
        else all_tree_path(T->child, st);  //找以T为根的子树上的叶子结点路径
        st.pop();  //栈顶结点是叶子结点或以栈顶结点为根的子树上的叶子路径已完成
        T = T->sibling;     //继续找T的其余子树
    }
}

/* 遍历输出栈中数据 */
void print_stack(stack<char*>st) {
    stack<char*>stack;
    while (!st.empty()) {
        stack.push(st.top());
        st.pop();
    }
    while(!stack.empty()) {
        printf("/%s", stack.top());
        stack.pop();
    }
    puts("");

}

/* 先根遍历 */
void preorder_traversal(treelink root) {
    if (root == NULL) return ;
    printf("%s ", root->data);
    preorder_traversal(root->child);
    preorder_traversal(root->sibling);
}

/* 后根遍历 */
void postorder_traversal(treelink root) {
    if (root == NULL) return ;
    preorder_traversal(root->child);
    preorder_traversal(root->sibling);
    printf("%s ", root->data);
}

/*层次遍历 */
void levelorder_traversal(treelink root) {
    queue<treelink> que;
    que.push(root);
    if (root == NULL) return;
    while (!que.empty()) {
        int size = que.size();
        for (int i = 0; i < size; i++) {    //size不能换成que.size(),因为que长度会变
            treelink cur = que.front();
            que.pop();
            printf("%s ", cur->data);
            cur = cur->child;
            while (cur != NULL) {
                que.push(cur);
                cur = cur->sibling;
            }
        }
        puts("");
    }
}

/* 路径 */
void Path(treelink pTree, stack<char*>st, char  *szName) {
    if(pTree){
        st.push(pTree->data);
        if(strcmp(pTree->data,szName) == 0) print_stack(st);
        else Path(pTree->child,st,szName);
        st.pop();
        Path(pTree->sibling,st,szName);
    }
}

/* 查找 */
treelink node_find1(treelink root, char *name) {

    treelink p;
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
