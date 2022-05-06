## 求一条包含无向图中所有顶点的简单路径问题（Hamilton）
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
