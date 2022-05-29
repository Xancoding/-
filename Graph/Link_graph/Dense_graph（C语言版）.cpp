//稠密图（e > nlog2n）
//邻接矩阵
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<conio.h>
#define MAX 20  //最大顶点数
#define NUM 20  //最大字符串长度

using namespace std;

typedef struct {
    char vexs[MAX][NUM];;  //顶点信息
    int arcs[MAX][MAX];  //顶点关系(边或弧上的权值)
    int vex;  //顶点数
    int arc;  //弧数
}graph, *graphlink;

typedef struct {
    int elem[MAX];
    int front,rear;
    int queuesize;
}XhQueue;

int menu();  //菜单
void crt_graph(graphlink G);  //创建
void disp_graph(graphlink G);  //显示
void dfs(graphlink G, int v, int visited[]);  //DFS
void bfs(graphlink G, int v, int visited[], XhQueue Q);  //BFS
void InitQueue(XhQueue &Q);
void EnQueue(XhQueue &Q, int p);
void DeQueue(XhQueue &Q,int &p);
void GetHead(XhQueue &Q,int &p);
int EmQueue(XhQueue Q);
int LengthQueue(XhQueue Q);

int main() {
    int n;
    int v;  //出发点编号
    int visited[MAX];
    XhQueue Q;
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
                InitQueue(Q);
                for (int i = 0; i < MAX; i++) visited[i] = 0;
                printf("出发点编号：");
                scanf("%d", &v);
                bfs(G, v, visited, Q);
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
    scanf("%d %d", &G->vex, &G->arc);  //顶点数和边数
    printf("输入顶点信息\n");
    for (int i = 1; i <= G->vex; i++) scanf("%s", G->vexs[i]);  //顶点信息
    for (int i = 1; i <= G->vex; i++)
        for (int j = 1; j <= G->vex; j++)
            G->arcs[i][j] = 0;  //邻接矩阵初始化
    printf("输入边\n");
    for (int k = 1; k <= G->arc; k++) {  //读入边
        int i, j;
        scanf("%d%d", &i, &j);
        G->arcs[i][j] = 1;
        G->arcs[j][i] = 1;
    }
}

void disp_graph(graphlink G) {
    printf("顶点如下\n");
    for (int i = 1; i <= G->vex; i++) printf("%s ", G->vexs[i]);
    printf("\n邻接矩阵如下\n");
    for (int i = 1; i <= G->vex; i++) {
        for (int j = 1; j <= G->vex; j++)
            printf("%-4d", G->arcs[i][j]);
        puts("");
    }
}

void dfs(graphlink G, int v, int visited[]) {  //v为出发点编号
    printf("%s ", G->vexs[v]);
    visited[v] = 1;
    for (int w = 1; w <= G->vex; w++)
        if (G->arcs[v][w] != 0 && visited[w] == 0)
            dfs(G, w, visited);
}

void bfs(graphlink G, int v, int visited[], XhQueue Q) {  //que存储已访问过的顶点编号
    printf("%s ", G->vexs[v]);
    visited[v] = 1;
    EnQueue(Q, v);

    while (!EmQueue(Q)) {
        int u;
        DeQueue(Q, u);
        for (int w = 1; w <= G->vex; w++)   //找出u所有邻接点
            if (G->arcs[u][w] != 0 && visited[w] == 0) {
                printf("%s ", G->vexs[w]);
                visited[w] = 1;
                EnQueue(Q, w);
            }
    }
}

void InitQueue(XhQueue &Q){
    if(Q.elem != NULL) {
        Q.front = Q.rear = 0;
        Q.queuesize = MAX;
    }
}

void EnQueue(XhQueue &Q,int p){
    if((Q.rear + 1) % Q.queuesize != Q.front){
        Q.elem[Q.rear] = p;
        Q.rear = (Q.rear + 1) % Q.queuesize;
    }
}

void DeQueue(XhQueue &Q,int &p){
    if(Q.front != Q.rear){
        p = Q.elem[Q.front];
        Q.front = (Q.front +1) % Q.queuesize;
    }
}

void GetQueueHead(XhQueue &Q,int &p){
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


