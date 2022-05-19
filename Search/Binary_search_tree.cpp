#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<conio.h>
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
bool node_find(treelink T, char  *name,treelink &p, treelink &s);  /* 查找 */
void Destroy(treelink &p);   /* 销毁二叉树 */
bool node_delete(treelink &T, char *name);  /* 删除数据 */
void Delete(treelink &p);   /* 删除结点p */
void node_insert(treelink &T, char *name);  /* 插入数据 */

int main() {
    int n;
    char str[MAX];
    treelink root = NULL;
	treelink p = NULL;  //父结点
 	treelink s = NULL;  //子结点

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
                p = NULL;
				s = NULL; 
                if(node_find(root, str, p,s))
                    printf("\nnode addr = %x\nnode val = %s\n",s,s->data);
                else
                    printf("没找到结点\n");
				
				printf("按任意键继续!\n");
                getch(); break;
			case 3:
                printf("请输入结点名：");
                scanf("%s", str);
                if (!node_delete(root, str))
                    printf("没找到结点\n");
                printf("按任意键继续!\n");
                getch(); break;
            case 4:
                printf("请输入新结点名字：");
                scanf("%s", str);
                node_insert(root, str);
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
        printf("\t1.创建\n");
        printf("\t2.查找\n");
        printf("\t3.删除\n");
        printf("\t4.插入\n");
        printf("\t5.销毁\n");
        printf("\t6.显示\n");
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
   while(1) {
       char data[MAX];
       scanf("%s", data);
       if (strcmp(data, "#") == 0)
           break;
       else
           node_insert(T, data);
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
bool node_delete(treelink &T, char *name) {
    if (T == NULL) return false;
    else {
        if (strcmp(T->data, name) == 0) {
            Delete(T);
            return true;
        }
        else if (strcmp(T->data, name) > 0)
            return node_delete(T->left, name);
        else
            return node_delete(T->right, name);
    }
}

void Delete(treelink &p) {
    if (!p->right) {  //没有右子树
        treelink tmp = p;
        p = p->left;
        delete tmp;
    } else if (!p->left) {  //没有左子树
        treelink tmp = p;
        p = p->right;
        delete tmp;
    } else {  //左右子树都存在
        treelink q = p, s = q->left;  //s指向被删结点的中序前驱，q指向s的双亲
        while(s->right) {
            q = s;
            s = s->right;
        }
        strcpy(p->data, s->data);
        if (q != p)
            q->right = s->left;
        else
            q->left = s->left;
        delete s;
    }
}

/* 查找数据 */
bool node_find(treelink T, char  *name,treelink &p, treelink &s) {  //p为父结点 s为子结点
    if(T == NULL) {
        s = p;
        return false;
    } else if (strcmp(T->data, name) == 0) {
        s = T;
        return true;
    } else if (strcmp(T->data, name) > 0) {
        p = T;
        return node_find(T->left, name, p, s);
    } else {
        p = T;
        return node_find(T->right, name, p, s);
    }
}

/* 插入数据 */
void node_insert(treelink &T, char *name) {
   if (T == NULL) {
       T = new treenode;
       strcpy(T->data, name);
       T->left = T->right = NULL;
   } else if (strcmp(T->data, name) > 0) {
       node_insert(T->left, name);
   } else {
       node_insert(T->right, name);
   }
}
