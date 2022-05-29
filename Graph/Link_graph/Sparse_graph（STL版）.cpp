//稀疏图（e <= nlog2n）
//邻接表
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<conio.h>
#include<stack>
#include<queue>
#define MAX 20  //最大顶点数
#define NUM 20  //最大字符串长度

using namespace std;

//边结点
typedef struct arcnode {
    int adjvex;  //弧所指向顶点下标
    struct arcnode *next;  //指向下一条弧
    int weight;  //边结点类型（权重）
}arcnode;

//表头结点
typedef struct vexnode {
    char vertex[NUM];  //存放结点值
    arcnode *head;  //存放边链表头指针
}vexnode;

//邻接表
typedef struct graph{
    vexnode adjlist[MAX];
    int vex;  //顶点数
    int arc;  //边数
}graph, *graphlink;

int menu();  //菜单
void crt_graph(graphlink G);  //创建
void disp_graph(graphlink G);  //显示
void dfs(graphlink G, int v, int visited[]);  //DFS
void bfs(graphlink G, int v, int visited[], queue<int>que);  //BFS




int main() {
    int n;
    int v;  //出发点编号
    int visited[MAX];
    queue<int>que;
    graphlink G = new graph;

    while (1) {
        n = menu();
        switch(n) {
            case 1:
                crt_graph(G);
                printf("按任意键继续!\n");
                getch(); break;
            case 2:
                disp_graph(G);
                printf("按任意键继续!\n");
                getch(); break;
            case 3:
                for (int i = 0; i < MAX; i++) visited[i] = 0;
                printf("出发点编号：");
                scanf("%d", &v);
                dfs(G, v, visited);
                puts("");
                printf("按任意键继续!\n");
                getch(); break;
            case 4:
                for (int i = 0; i < MAX; i++) visited[i] = 0;
                printf("出发点编号：");
                scanf("%d", &v);
                bfs(G, v, visited, que);
                puts("");
                printf("按任意键继续!\n");
                getch(); break;
        }
    }
}

int menu() {
    int n;
    while (1) {
        system("cls");
        printf("*****欢迎使用本系统*****\n");
        printf("\t1.创建图\n");
        printf("\t2.显示图\n");
        printf("\t3.DFS\n");
        printf("\t4.BFS\n");
        printf("************************\n");
        printf("请输入数字：");
        scanf("%d", &n);
        if (n > 4 || n < 0) {
            printf("输入错误，请重新输入！\n");
        } else return n;
    }
}

void crt_graph(graphlink G) {
    printf("输入顶点数和边数（空格隔开）\n");
    scanf("%d%d", &G->vex, &G->arc);
    printf("输入顶点信息\n");
    for (int i = 1; i <= G->vex; i++) {
        scanf("%s", G->adjlist[i].vertex);
        G->adjlist[i].head = NULL;
    }
    printf("输入边\n");
    for (int k = 0; k < G->arc; k++) {
        int i, j;
        scanf("%d%d", &i, &j);
        arcnode *p = new arcnode;
        p->adjvex = j;
        p->next = G->adjlist[i].head;  //头插
        G->adjlist[i].head = p;

        arcnode *q = new arcnode;
        q->adjvex = i;
        q->next = G->adjlist[j].head;  //头插
        G->adjlist[j].head = q;
    }
}

void disp_graph(graphlink G) {
    printf("邻接表如下\n");
    for (int i = 1; i <= G->vex; i++) {
        printf("%s ", G->adjlist[i].vertex);  //显示表头结点
        if(G->adjlist[i].head == NULL) printf("^ \n");  //边链表为空
        else {
            arcnode *p = G->adjlist[i].head;  //p指向第一个边结点
            while (p) {printf("%d-->", p->adjvex);  p = p->next;}
            printf("^ \n");
        }
    }
}

void dfs(graphlink G, int v, int visited[]) {
    printf("%s ", G->adjlist[v].vertex);
    visited[v] = 1;
    arcnode *p = G->adjlist[v].head;
    while(p) {
        int w = p->adjvex;
        if (visited[w] == 0) dfs(G, w, visited);
        p = p->next;
    }
}

void bfs(graphlink G, int v, int visited[], queue<int>que) {
    printf("%s ", G->adjlist[v].vertex);
    visited[v] = 1;
    que.push(v);

    while (!que.empty()) {
        int u = que.front();  que.pop();
        arcnode *p = G->adjlist[u].head;
        while (p) {
            int w = p->adjvex;
            if (visited[w] == 0) {printf("%s ", G->adjlist[w].vertex);  visited[w] = 1;  que.push(w);}
            p = p->next;
        }
    }
}
