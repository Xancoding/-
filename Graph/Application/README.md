# 基于DFS
## 求所有包含无向图中所有顶点的简单路径问题（Hamilton）
### 代码实现
```cpp
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<conio.h>
#include<stack>
#include<queue>
#define MAX 20  //最大顶点数
#define NUM 20  //最大字符串长度

using namespace std;

typedef struct {
    char vexs[MAX][NUM];;  //顶点信息
    int arcs[MAX][MAX];  //顶点关系(边或弧上的权值)
    int vex;  //顶点数
    int arc;  //弧数
}graph, *graphlink;

int menu();  //菜单
void crt_graph(graphlink G);  //创建
void disp_graph(graphlink G);  //显示
void dfs(graphlink G, int v,int path[], int visited[], int &n);  //DFS
void Hamilton(graphlink G, int path[], int visited[]);  //Hamilton
void print_path(graphlink G, int path[], int n);  //简单路径

int main() {
    int n;
    int v;  //出发点编号
    int visited[MAX];
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
                Hamilton(G, path, visited);
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
        printf("\t3.Hamilton\n");
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

void dfs(graphlink G, int v,int path[], int visited[], int &n) {  //v为出发点编号
    visited[v] = 1;
    path[n++] = v;

    if (n == G->vex) {print_path(G, path, n);  puts("");}  /* 符合条件，输出该简单路径  */
    for (int w = 1; w <= G->vex; w++)
        if (G->arcs[v][w] != 0 && visited[w] == 0)
            dfs(G, w, path, visited, n);

    visited[v] = 0;
    n--;
}

void Hamilton(graphlink G, int path[], int visited[]) {
    for (int i = 1; i <= G->vex; i++)  visited[i] = 0;
    for (int i = 1, n = 0; i <= G->vex; i++)
        if (!visited[i]) dfs(G, i, path, visited, n);
}

void print_path(graphlink G, int path[], int n) {
    for (int i = 0; i < n; i++)  printf("%s ", G->vexs[path[i]]);
}
```
### 测试数据
```cpp
输入顶点数和边数 7 7
输入顶点信息  1 2 3 4 5 6 7
输入边  1 2 2 5 5 7 7 6 6 4 4 1 1 3 3 7
```
### 输出
```cpp
邻接矩阵如下
0   1   1   1   0   0   0
1   0   0   0   1   0   0
1   0   0   0   0   0   0
1   0   0   0   0   1   0
0   1   0   0   0   0   1
0   0   0   1   0   0   1
0   0   0   0   1   1   0
简单路径（4条）
2 5 7 6 4 1 3
3 1 2 5 7 6 4
3 1 4 6 7 5 2
4 6 7 5 2 1 3
```

## 判断有向图中是否有环
### 代码实现
```cpp
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<conio.h>
#include<stack>
#include<queue>
#define MAX 20  //最大顶点数
#define NUM 20  //最大字符串长度

using namespace std;

typedef struct {
    char vexs[MAX][NUM];;  //顶点信息
    int arcs[MAX][MAX];  //顶点关系(边或弧上的权值)
    int vex;  //顶点数
    int arc;  //弧数
}graph, *graphlink;

int menu();  //菜单
void crt_graph(graphlink G);  //创建
void disp_graph(graphlink G);  //显示
void dfs(graphlink G, int v,int stated[], int &hascycle);  //DFS
void cycle(graphlink G);  //判断有无回路

int main() {
    int n;
    int v;  //出发点编号
    int visited[MAX];
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
                cycle(G);
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
        printf("\t3.判断是否有环\n");
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
            G->arcs[i][j] = 0;  //邻接矩阵初始化
    printf("输入边\n");
    for (int k = 1; k <= G->arc; k++) {  //读入边
        int i, j;
        scanf("%d%d", &i, &j);
        G->arcs[i][j] = 1;
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

void dfs(graphlink G, int v,int stated[], int &hascycle) {  //v为出发点编号
    if (hascycle == 1) return ;  //出现环
    if (stated[v] == -1) {  //-1表示从v开始的深搜还没开始
        stated[v] = 0;  //0表示从v开始的深搜已经开始
        for (int w = 0; w  < G->vex; w++) {
            if (G->arcs[v][w] == 1) {  //检查从v出发的每一条弧
                if (stated[w] == -1) dfs(G, w, stated, hascycle);
                else if (stated[w] == 0) hascycle = 1;
            }
        }
        stated[v] = 1;  //1表示从v开始的深搜已经结束
    }
}

void cycle(graphlink G) {
    int hascycle = 0;
    int stated[MAX];
    for (int i = 0; i < G->vex; i++) stated[i] = -1;
    for (int v = 1; v <= G->vex; v++) {
        dfs(G, v, stated, hascycle);
        if (hascycle == 1) {printf("有回路\n"); break;}
        else printf("无回路\n");
    }
}
```
### 测试数据
```cpp
输入顶点数和边数 4 4
输入顶点信息  a b c d
输入边  1 2 2 3 3 1 1 4
```
### 输出
```cpp
邻接矩阵如下
0   1   0   1
0   0   1   0
1   0   0   0
0   0   0   0

有回路
```
## 求一条无向图的顶点v到顶点w的简单路径
- 在遍历中，如果该顶点的所有邻接点都被访问过，但是还没到达目的地w，则必须删除该顶点
### 代码实现
```cpp
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<conio.h>
#include<stack>
#include<queue>
#define MAX 20  //最大顶点数
#define NUM 20  //最大字符串长度

using namespace std;

typedef struct {
    char vexs[MAX][NUM];;  //顶点信息
    int arcs[MAX][MAX];  //顶点关系(边或弧上的权值)
    int vex;  //顶点数
    int arc;  //弧数
}graph, *graphlink;

int menu();  //菜单
void crt_graph(graphlink G);  //创建
void disp_graph(graphlink G);  //显示
void dfs(graphlink G, int v,int w, int path[], int visited[], int &found, int &n);  //DFS
void print_path(graphlink G, int path[], int n);  //简单路径

int main() {
    int n;
    int v;  //出发点编号
    int w;  //结束点编号
    int visited[MAX];
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
                for (int i = 0; i < MAX; i++) {visited[i] = 0;  path[i] = 0;}
                int found = 0;
                int num = 0;
                printf("输入出发点 结束点（空格隔开）:");
                scanf("%d %d", &v, &w);
                dfs(G, v, w, path, visited, found, num);
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
        printf("\t3.求任意两顶点间的简单路径\n");
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

void dfs(graphlink G, int v,int w, int path[], int visited[], int &found, int &n) {  //n表示当前path中包含顶点数
    visited[v] = 1;  //访问顶点v
    path[n++] = v;  //将顶点v放入路径
    for (int j = 1; j <= G->vex && !found; j++) {
        if (G->arcs[v][j] == 1) {
            if (j == w) {
                found = 1;
                path[n++] = j;
                print_path(G ,path, n);
            } else if (visited[j] == 0) dfs(G, j, w, path, visited, found, n);
        }
    }
    if (!found) n--;  //从路径上删除顶点v
}

void print_path(graphlink G, int path[], int n) {
    for (int i = 0; i < n; i++)  printf("%s ", G->vexs[path[i]]);
}
```
### 测试数据
```cpp
输入顶点数和边数 9 13
输入顶点信息  a b c d e f g h i
输入边  1 4 4 8 8 5 5 3 3 4 1 3 1 2 2 3 2 7 3 7 3 6 6 9 9 7
出发点 结束点 1 9  （a->i）
```
### 输出
```cpp
邻接矩阵如下
0   1   1   1   0   0   0   0   0
1   0   1   0   0   0   1   0   0
1   1   0   1   1   1   1   0   0
1   0   1   0   0   0   0   1   0
0   0   1   0   0   0   0   1   0
0   0   1   0   0   0   0   0   1
0   1   1   0   0   0   0   0   1
0   0   0   1   1   0   0   0   0
0   0   0   0   0   1   1   0   0

a b c f i
```
# 基于BFS
## 求无向图的顶点v到顶点w的最短路径
- 边权为1
### 代码实现
```cpp
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<conio.h>
#include<stack>
#include<queue>
#define MAX 20  //最大顶点数
#define NUM 20  //最大字符串长度
#define INF 0x3f3f3f3f  //无穷大

using namespace std;

typedef struct {
    char vexs[MAX][NUM];;  //顶点信息
    int arcs[MAX][MAX];  //顶点关系(边或弧上的权值)
    int vex;  //顶点数
    int arc;  //弧数
}graph, *graphlink;

int menu();  //菜单
void crt_graph(graphlink G);  //创建
void disp_graph(graphlink G);  //显示
void bfs(graphlink G, int v,int w, int path[]);  //BFS
void print_path(graphlink G, int path[], int v, int w);  //最短路径

int main() {
    int n;
    int v;  //出发点编号
    int w;  //结束点编号
    int path[MAX];  //path[i]的值表示路径中下标为i的顶点的上一个顶点的下标
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
                printf("输入出发点 结束点（空格隔开）:");
                scanf("%d %d", &v, &w);
                bfs(G, v, w, path);
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
        printf("\t3.求任意两顶点间的最短路径\n");
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

void bfs(graphlink G, int v,int w, int path[]) {
    bool st[MAX];
    int dist[MAX];  //距离顶点v的距离
    for (int i = 1; i <= G->vex; i++) {
        st[i] = false;  //初始化，设置为未访问
        dist[i] = INF;  //初始化，设置为无穷大
    }

    queue<int>que;
    que.push(v);  st[v] = true; dist[v] = 0;
    while (!que.empty()) {
        int u = que.front(); que.pop();
        for (int i = 1; i <= G->vex; i++)
            if (!st[i] && G->arcs[u][i] != 0) {  //遍历邻接点
                path[i] = u;
                dist[i] = dist[u] + 1;
                if (i == w) {
                    printf("最短距离为：%d\n", dist[w]);
                    print_path(G, path, v, w);
                    return ;
                }
                st[i] = true;
                que.push(i);
            }
    }
}

void print_path(graphlink G, int path[], int v, int w) {
    printf("最短路径为：");
    for (int i = w; i != v; i = path[i])
        printf("%s<--", G->vexs[i]);
    
    printf("%s\n", G->vexs[v]);
}
```
### 测试数据
```cpp
输入顶点数和边数 9 11
输入顶点信息  1 2 3 4 5 6 7 8 9
输入边  1 3 1 2 1 4 1 7 2 3 4 5 4 6 5 6 7 8 7 9 8 9
出发点 结束点 3 5
```
### 输出
```cpp
邻接矩阵如下
0   1   1   1   0   0   1   0   0
1   0   1   0   0   0   0   0   0
1   1   0   0   0   0   0   0   0
1   0   0   0   1   1   0   0   0
0   0   0   1   0   1   0   0   0
0   0   0   1   1   0   0   0   0
1   0   0   0   0   0   0   1   1
0   0   0   0   0   0   1   0   1
0   0   0   0   0   0   1   1   0

最短距离为：3
最短路径为：5<--4<--1<--3
```
