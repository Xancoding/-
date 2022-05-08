# Prim
- 适用于稠密图
## 时间复杂度
```cpp
O(n^2 + e), n 表示点数，e 表示边数
```
## 代码实现
```cpp
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<conio.h>
#include<stack>
#include<queue>
#define MAX 20  //最大顶点数
#define NUM 20  //最大字符串长度
#define INF 0x3f3f3f3f //无穷大
using namespace std;

typedef struct {  //图的邻接矩阵
    char vexs[MAX][NUM];;  //顶点信息
    int arcs[MAX][MAX];  //顶点关系(边或弧上的权值)
    int vex;  //顶点数
    int arc;  //弧数
}graph, *graphlink;

typedef struct {  //最小代价数组
    int weight;  //边的权值
    int adjnode;  //邻接点编号
}lowcost;

int menu();  //菜单
void crt_graph(graphlink G);  //创建
void disp_graph(graphlink G);  //显示
void prim(graphlink G, int v, lowcost lc[]);  //最小生成树
void print_MST(graphlink G, lowcost lc[]);  //打印最小生成树

int main() {
    int n;
    lowcost lc[MAX]; //最小代价数组
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
                prim(G, 1, lc);  //从编号为1的点出发
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
        printf("\t3.最小生成树\n");
        printf("************************\n");
        printf("请输入数字：");
        scanf("%d", &n);
        if (n > 3 || n < 0) {
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
            G->arcs[i][j] = INF;  //邻接矩阵初始化
    printf("输入边和权值（空格隔开）\n");
    for (int k = 1; k <= G->arc; k++) {  //读入边
        int i, j, w;
        scanf("%d%d%d", &i, &j, &w);
        G->arcs[i][j] = w;
        G->arcs[j][i] = w;
    }
}

void disp_graph(graphlink G) {
    printf("顶点如下\n");
    for (int i = 1; i <= G->vex; i++) printf("%s ", G->vexs[i]);
    printf("\n邻接矩阵如下\n");
    for (int i = 1; i <= G->vex; i++) {
        for (int j = 1; j <= G->vex; j++)
            printf("%-16d", G->arcs[i][j]);
        puts("");
    }
}

void prim(graphlink G, int v, lowcost lc[]) {
    int total = 0;  //边权总和
    int st[MAX] = {0};  //存储每个点是否已经在生成树中
    st[v] = 1;
    for (int i = 1; i <= G->vex; i++) {  //初始化
        lc[i].weight = G->arcs[v][i];
        if (lc[i].weight == INF) lc[i].adjnode = -1;
        else lc[i].adjnode = v;
    }
    for (int i = 1; i <= G->vex - 1; i++) {  //循环 G->vex - 1 次
        int min = INF;  //其他点到当前最小生成树的最短距离
        int pos = -1;  //到当前最小生成树的最短距离的点
        for (int k = 1; k <= G->vex; k++)  //选出权值最小的边
            if (st[k] == 0 && lc[k].weight < min) {
                min = lc[k].weight;
                pos = k;
            }
        total += min;
        st[pos] = 1;  //已在最小生成树中的点
        //更新其他点到当前最小生成树的距离
        for (int k = 1; k <= G->vex; k++)
            if (st[k] == 0 && G->arcs[pos][k] < lc[k].weight) {
                lc[k].weight = G->arcs[pos][k];
                lc[k].adjnode = pos;
            }
    }
    printf("边权总和为：%d\n", total);
    print_MST(G, lc);
}

void print_MST(graphlink G, lowcost lc[]) {
    int n = G->vex;
    for (int i = 1;  i <= n; i++) {
        if (lc[i].adjnode == -1) printf("%s(ROOT)\n", G->vexs[i]);  //若adjnode为-1，该点为根结点
        else printf("%s->%s\n", G->vexs[lc[i].adjnode], G->vexs[i]);  //邻接点编号adjnode为其父结点
    }
}
```
## 测试数据
```cpp
输入顶点数和边数 5 7
输入顶点信息  a b c d e
输入边  1 2 100 1 3 30 1 5 10 5 4 50 3 4 20 2 4 10 2 3 25
```
## 输出
```cpp
边权总和为：70

最小生成树
a(ROOT)
d->b
a->c
c->d
a->e
```
# Kruskal
- 适用于稀疏图
## 时间复杂度
```cpp
O(eloge),e 表示边数
```
## 代码实现
```cpp
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<conio.h>
#include<stack>
#include<queue>
#define MAX 20  //最大顶点数
#define NUM 20  //最大字符串长度
#define INF 0x3f3f3f3f //无穷大
using namespace std;

typedef struct {  //图的邻接矩阵
    char vexs[MAX][NUM];;  //顶点信息
    int arcs[MAX][MAX];  //顶点关系(边或弧上的权值)
    int vex;  //顶点数
    int arc;  //弧数
}graph, *graphlink;

typedef struct {
    int a, b, w;
    int flag;  //构成最小生成树边的标志
}edge;

int menu();  //菜单
void crt_graph(graphlink G);  //创建
void disp_graph(graphlink G);  //显示
void init(graphlink G, edge edges[], int fa[]);  //初始化
int get_father(int x, int fa[]);  //求编号为x的顶点所在的最大子树的编号
void Kruskal(graphlink G, edge edges[], int fa[]);  //最小生成树
void print_MST(graphlink G, edge edges[], int n);  //打印最小生成树

int main() {
    int n;
    int fa[MAX];
    edge edges[MAX];
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
                Kruskal(G, edges, fa);
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
        printf("\t3.最小生成树\n");
        printf("************************\n");
        printf("请输入数字：");
        scanf("%d", &n);
        if (n > 3 || n < 0) {
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
            G->arcs[i][j] = INF;  //邻接矩阵初始化
    printf("输入边和权值（空格隔开）\n");
    for (int k = 1; k <= G->arc; k++) {  //读入边
        int i, j, w;
        scanf("%d%d%d", &i, &j, &w);
        G->arcs[i][j] = w;
        G->arcs[j][i] = w;
    }
}

void disp_graph(graphlink G) {
    printf("顶点如下\n");
    for (int i = 1; i <= G->vex; i++) printf("%s ", G->vexs[i]);
    printf("\n邻接矩阵如下\n");
    for (int i = 1; i <= G->vex; i++) {
        for (int j = 1; j <= G->vex; j++)
            printf("%-16d", G->arcs[i][j]);
        puts("");
    }
}

void init(graphlink G, edge edges[], int fa[]) {  //fa[i]存储i的父结点
    int k = 0;
    for (int i = 1; i <= G->vex; i++)
        for (int j = 1; j < i; j++)
            if (G->arcs[i][j] != INF) {  //初始化edges数组
                edges[k].a = i;  edges[k].b = j; edges[k].w = G->arcs[i][j];
                edges[k].flag = 0;  k++;
            }

    for (int i = 1; i <= G->vex; i++) fa[i] = i;  //初始化fa数组

    for (int i = 0; i < k - 1; i++)  //对边排序(冒泡排序)
        for (int j = 0; j < k - i - 1; j++)
            if (edges[j].w > edges[j + 1].w)
                swap(edges[j], edges[j + 1]);
}

int get_father(int x, int fa[]) { //求编号为x的顶点所在的最大子树的编号
    if (x != fa[x]) fa[x] = get_father(fa[x], fa);
    return fa[x];
}

void Kruskal(graphlink G, edge edges[], int fa[]) {
    init(G, edges, fa);  //初始化
    int cnt = 0;  //合并次数
    int k = 0;  //边的下标
    int total = 0;  //边权总和
    while (cnt < G->vex - 1) {
        int x = get_father(edges[k].a, fa);
        int y = get_father(edges[k].b, fa);
        if (x != y) {
            fa[x] = y;  //合并到一棵生成树
            total += edges[k].w;  edges[k].flag = 1;  cnt++;
        }
        k++;
    }
    printf("边权总和为：%d\n", total);
    print_MST(G, edges, k);
}

void print_MST(graphlink G, edge edges[], int n) {
    for (int i = 0; i < n; i++)
        if (edges[i].flag == 1)
            printf("%s->%s\n", G->vexs[edges[i].a], G->vexs[edges[i].b]);
}
```
## 测试数据
```cpp
输入顶点数和边数 6 10
输入顶点信息  a b c d e f 
输入边  1 2 6 1 3 1 1 4 4 2 3 5 3 4 5 2 5 3 4 6 2 5 6 6 5 3 6 3 6 4
```
## 输出
```cpp
边权总和为：15

最小生成树
c->a
f->d
e->b
d->a
c->b
```
