# Prim
- 适用于稠密图
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
void MST(graphlink G, int v, lowcost lc[]);  //最小生成树
void print_MST(graphlink G, lowcost lc[]);  //打印最小生成树

int main() {
    int n;
    int v;  //出发点编号
    lowcost lc[MAX]; //最小代价数组
    int path[MAX];
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
                MST(G, 1, lc);  //从编号为1的点出发
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

void MST(graphlink G, int v, lowcost lc[]) {
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
        st[pos] = 1;  //已在最小生成树中的点
        //更新其他点到当前最小生成树的距离
        for (int k = 1; k <= G->vex; k++)
            if (st[k] == 0 && G->arcs[pos][k] < lc[k].weight) {
                lc[k].weight = G->arcs[pos][k];
                lc[k].adjnode = pos;
            }
    }

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
## 时间复杂度
```cpp
O(n^2 + e), n 表示点数，e 表示边数
```
## 测试数据
```cpp
输入顶点数和边数 5 7
输入顶点信息  a b c d e
输入边  1 2 100 1 3 30 1 5 10 5 4 50 3 4 20 2 4 10 2 3 25
```
## 输出
```cpp
最小生成树
a(ROOT)
d->b
a->c
c->d
a->e
```
# Kruskal
- 适用于稀疏图
## 代码实现
```cpp
```
## 时间复杂度
```cpp
O(eloge),e 表示边数
```
## 测试数据
```cpp
输入顶点数和边数 
输入顶点信息  
输入边  
```
## 输出
```cpp
最小生成树

```
