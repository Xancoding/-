- 有向网
# dijkstra
- 贪心
- 某个源点到其余各点的最短路
## 时间复杂度
```cpp
O(n^2), n 表示点数
```
## 代码实现
```cpp
```
## 测试数据
```cpp
输入顶点数和边数 
输入顶点信息  
输入边  
```
## 输出
```cpp
```
# floyd
- DP(动态规划)
- 每一对顶点之间的最短路
## 时间复杂度
```cpp
O(n^3), n 表示点数
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
#include<iostream>
using namespace std;

typedef struct {  //图的邻接矩阵
    char vexs[MAX][NUM];;  //顶点信息
    int arcs[MAX][MAX];  //顶点关系(边或弧上的权值)
    int vex;  //顶点数
    int arc;  //弧数
}graph, *graphlink;


int menu();  //菜单
void crt_graph(graphlink G);  //创建
void disp_graph(graphlink G);  //显示
void floyd(graphlink G, int dist[][MAX], int path[][MAX]);  //求每一对顶点之间的最短路
void print_path(graphlink G, int dist[][MAX], int path[][MAX]);  //打印最短路

int main() {
    int n;
    graphlink G = new graph;
    int dist[MAX][MAX];  //dist[i][j]表示当前求出的i到j的路径长度
    int path[MAX][MAX];  //path[i][j]存放当前i到j的路径中最后一条弧的弧尾编号，最后一条弧的弧头编号为j

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
                floyd(G, dist, path);
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
        for (int j = 1; j <= G->vex; j++) {
            G->arcs[i][j] = INF;  //邻接矩阵初始化
            if (i == j) G->arcs[i][j] = 0;
        }
    printf("输入边和权值（空格隔开）\n");
    for (int k = 1; k <= G->arc; k++) {  //读入边
        int i, j, w;
        scanf("%d%d%d", &i, &j, &w);
        G->arcs[i][j] = w;
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

void floyd(graphlink G, int dist[][MAX], int path[][MAX]) {
    for (int i = 1; i <= G->vex; i++)  //初始化
        for (int j = 1; j <= G->vex; j++) {
            dist[i][j] = G->arcs[i][j];
            path[i][j] = i;
            if (dist[i][j] == 0 || dist[i][j] == INF) path[i][j] = -1;
        }

    for (int k = 1; k <= G->vex; k++)  //对每一个顶点做一次迭代
        for (int i = 1; i <= G->vex; i++)
            for (int j = 1; j <= G->vex; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = k;
                }
    
    print_path(G, dist, path);
}

void print_path(graphlink G, int dist[][MAX], int path[][MAX]) {
    for (int i = 1; i <= G->vex; i++)
        for (int j = 1; j <= G->vex; j++) {
            if (path[i][j] == -1) printf("不存在！\n");
            else {
                printf("最短距离为：%d\t路径为：", dist[i][j]);
                int k = j;
                while (k != i) {
                    printf("%s<-", G->vexs[k]);
                    k = path[i][k];
                }
                printf("%s", G->vexs[i]);
                puts("");
            }
        }
}
```
## 测试数据
```cpp
输入顶点数和边数 4 8
输入顶点信息  1 2 3 4
输入边  1 2 1 2 4 2 4 3 6 3 4 8 3 1 3 1 4 4 2 3 9 3 2 5
```
## 输出
```cpp
不存在！
最短距离为：1   路径为：2<-1
最短距离为：9   路径为：3<-4<-2<-1
最短距离为：3   路径为：4<-2<-1
最短距离为：11  路径为：1<-4<-2
不存在！
最短距离为：8   路径为：3<-4<-2
最短距离为：2   路径为：4<-2
最短距离为：3   路径为：1<-3
最短距离为：4   路径为：2<-1<-3
不存在！
最短距离为：6   路径为：4<-2<-1<-3
最短距离为：9   路径为：1<-3<-4
最短距离为：10  路径为：2<-3<-4（这条数据的路径和真实情况不符，只有path[4][2]这条数据与实际不符）
最短距离为：6   路径为：3<-4
不存在！
```
