# AOE网络关键路径
- AOE网络：以**顶点**表示事件，**弧**表示活动，**权**表示活动持续的时间的**带权有向无环图**
- 只有在某顶点所代表的事件发生后，从该顶点出发的各有向边所代表的活动才能开始
- 只有在指向某一顶点的各有向边所代表的活动都己经结束后，该顶点所代表的事件才能发生
- 假设AOE网络表示**施工流程图**，弧上权值表示完成该子工程所需**时间**
    - **关键活动**：关键路径上的所有活动
    - **关键路径**：整个工程完成的最短时间（从AOE网络的源点到汇点的最长路径长度）（所有路径中总持续时间最长的路径）
- 求关键活动
    - 假设活动`a(i)`是弧 `<j,k>`上的活动，`j`为弧尾顶点，`k`为弧头
    - 事件（顶点）`最早发生时间ve[j]`：从源点开始到顶点j的最大路径长度
    - 事件（顶点）`最迟发生时间vl[j]`：在不推迟整个工期的前提下，事件j允许发生的最晚时间
    - 活动（弧）`最早开始时间ee[i]`：`ee[i] = ve[j]`
    - 活动（弧）`最晚开始时间el[i]`：`el[i] = w(<j, k>)`
## 代码实现
### STL版
```cpp
#include<stdio.h>
#include<malloc.h>
#include<conio.h>
#include<stack>
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
    int cnt;  //顶点入度
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
void critical_path(graphlink G);  //关键路径


int main() {
    int n;
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
                critical_path(G);
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
        printf("\t3.关键路径\n");
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
    scanf("%d%d", &G->vex, &G->arc);
    printf("输入顶点信息\n");
    for (int i = 1; i <= G->vex; i++) {  //初始化
        scanf("%s", G->adjlist[i].vertex);
        G->adjlist[i].head = NULL;
        G->adjlist[i].cnt = 0;
    }
    printf("输入边的顶点和权值（空格隔开）\n");
    for (int k = 0; k < G->arc; k++) {
        int i, j, w;
        scanf("%d%d%d", &i, &j, &w);
        arcnode *p = new arcnode;
        p->adjvex = j;
        p->weight = w;
        p->next = G->adjlist[i].head;  //头插
        G->adjlist[i].head = p;
        G->adjlist[j].cnt++;  //结点入度
    }
}

void disp_graph(graphlink G) {
    printf("邻接表如下\n");
    for (int i = 1; i <= G->vex; i++) {
        printf("%s ", G->adjlist[i].vertex);  //显示表头结点
        if(G->adjlist[i].head == NULL) printf("^ \n");  //边链表为空
        else {
            arcnode *p = G->adjlist[i].head;  //p指向第一个边结点
            while (p) {printf("(%d)%d-->", p->weight, p->adjvex);  p = p->next;}
            printf("^ \n");
        }
    }
}

void critical_path(graphlink G) {
    stack<int>s1, s2;  //s1存放拓扑排序  s2存放拓扑逆序
    int ve[MAX], vl[MAX];

    for (int i = 1; i <= G->vex; i++)  //入度为0的顶点入栈
        if (G->adjlist[i].cnt == 0) s1.push(i);

    for (int i = 1; i <= G->vex; i++) ve[i] = 0;  //初始化
    while (!s1.empty()) { //按拓扑序列求各顶点的ve值，对每一条弧求弧头的ve值，弧头相同的取最大值
        int u = s1.top();  s1.pop();  s2.push(u);
        arcnode *cur = G->adjlist[u].head;
        while(cur) {  //求弧头k的ve值
            int k = cur->adjvex;
            G->adjlist[k].cnt--;  //更新邻接点入度
            if (G->adjlist[k].cnt == 0) s1.push(k);  //入度为零，入栈
            if (ve[u] + cur->weight > ve[k]) ve[k] = ve[u] + cur->weight;  //更新顶点的最早发生时间
            cur = cur->next;
        }
    }

    for(int i = 1; i <= G->vex; i++) vl[i] = ve[s2.top()];  //用ve（汇点）对v1初始化
    while(!s2.empty()) {  //按拓扑逆序求各顶点的vl值，对每一条弧求弧尾的vl值，弧尾相同的取最小值
        int u = s2.top(); s2.pop();
        arcnode *cur = G->adjlist[u].head;
        while(cur) {  //求弧尾k的vl值
            int k = cur->adjvex;
            G->adjlist[k].cnt--;  //更新邻接点入度
            if (vl[k] - cur->weight < vl[u]) vl[u] = vl[k] - cur->weight;  //更新顶点的最晚发生时间
            cur = cur->next;
        }
    }

    for (int i = 1; i <= G->vex; i++) {  //求ee和el
        arcnode *cur = G->adjlist[i].head;
        while (cur) {
            char tag;
            int k = cur->adjvex;
            int ee = ve[i], el = vl[k] - cur->weight;  //弧的ee和el
            if(ee == el) tag = 'y';  //标记关键活动
            else tag = 'n';
            printf("活动：%s-->%s  ee = %-4d el = %-4d %c\n", G->adjlist[i].vertex, G->adjlist[k].vertex, ee, el, tag);
            cur = cur->next;
        }
    }
}
```
### C语言版
```cpp
#include<stdio.h>
#include<malloc.h>
#include<conio.h>
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
    int cnt;  //顶点入度
    char vertex[NUM];  //存放结点值
    arcnode *head;  //存放边链表头指针
}vexnode;

//邻接表
typedef struct graph{
    vexnode adjlist[MAX];
    int vex;  //顶点数
    int arc;  //边数
}graph, *graphlink;

typedef struct stack {
    int data[MAX];
    int top;
    int stackSize;  //栈的容量
}SqStack;

int menu();  //菜单
void crt_graph(graphlink G);  //创建
void disp_graph(graphlink G);  //显示
void critical_path(graphlink G);  //关键路径
void InitSqStack(SqStack &S);
void PushSqStack(SqStack &S,int data);
void PopSqStack(SqStack &S);
int GetHead(SqStack &S);
int EmSqStack(SqStack S);

int main() {
    int n;
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
                critical_path(G);
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
        printf("\t3.关键路径\n");
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
    scanf("%d%d", &G->vex, &G->arc);
    printf("输入顶点信息\n");
    for (int i = 1; i <= G->vex; i++) {  //初始化结点
        scanf("%s", G->adjlist[i].vertex);
        G->adjlist[i].head = NULL;
        G->adjlist[i].cnt = 0;
    }
    printf("输入边的顶点和权值（空格隔开）\n");
    for (int k = 0; k < G->arc; k++) {
        int i, j, w;
        scanf("%d%d%d", &i, &j, &w);
        arcnode *p = new arcnode;
        p->adjvex = j;
        p->weight = w;
        p->next = G->adjlist[i].head;  //头插
        G->adjlist[i].head = p;
        G->adjlist[j].cnt++;  //结点入度
    }
}

void disp_graph(graphlink G) {
    printf("邻接表如下\n");
    for (int i = 1; i <= G->vex; i++) {
        printf("%s ", G->adjlist[i].vertex);  //显示表头结点
        if(G->adjlist[i].head == NULL) printf("^ \n");  //边链表为空
        else {
            arcnode *p = G->adjlist[i].head;  //p指向第一个边结点
            while (p) {printf("(%d)%d-->", p->weight, p->adjvex);  p = p->next;}
            printf("^ \n");
        }
    }
}

void critical_path(graphlink G) {
    //s1存放拓扑排序  s2存放拓扑逆序
    SqStack S1, S2;
    InitSqStack(S1), InitSqStack(S2);
    int ve[MAX], vl[MAX];

    for (int i = 1; i <= G->vex; i++)  //入度为0的顶点入栈
        if (G->adjlist[i].cnt == 0) PushSqStack(S1, i);

    printf("%d\n", S1.data[S1.top]);

    for (int i = 1; i <= G->vex; i++) ve[i] = 0;  //初始化
    while (!EmSqStack(S1)) { //按拓扑序列求各顶点的ve值，对每一条弧求弧头的ve值，弧头相同的取最大值
        int u = GetHead(S1);
        PopSqStack(S1);
        PushSqStack(S2, u);
        arcnode *cur = G->adjlist[u].head;
        while(cur) {  //求弧头k的ve值
            int k = cur->adjvex;
            G->adjlist[k].cnt--;  //更新邻接点入度
            if (G->adjlist[k].cnt == 0) PushSqStack(S1, k);  //入度为零，入栈
            if (ve[u] + cur->weight > ve[k]) ve[k] = ve[u] + cur->weight;  //更新顶点的最早发生时间
            cur = cur->next;
        }
    }

    for(int i = 1; i <= G->vex; i++) vl[i] = ve[GetHead(S2)];  //用ve（汇点）对v1初始化
    while(!EmSqStack(S2)) {  //按拓扑逆序求各顶点的vl值，对每一条弧求弧尾的vl值，弧尾相同的取最小值
        int u = GetHead(S2);
        PopSqStack(S2);
        arcnode *cur = G->adjlist[u].head;
        while(cur) {  //求弧尾k的vl值
            int k = cur->adjvex;
            G->adjlist[k].cnt--;  //更新邻接点入度
            if (vl[k] - cur->weight < vl[u]) vl[u] = vl[k] - cur->weight;  //更新顶点的最晚发生时间
            cur = cur->next;
        }
    }

    for (int i = 1; i <= G->vex; i++) {  //求ee和el
        arcnode *cur = G->adjlist[i].head;
        while (cur) {
            char tag;
            int k = cur->adjvex;
            int ee = ve[i], el = vl[k] - cur->weight;  //弧的ee和el
            if(ee == el) tag = 'y';  //标记关键活动
            else tag = 'n';
            printf("活动：%s-->%s  ee = %-4d el = %-4d %c\n", G->adjlist[i].vertex, G->adjlist[k].vertex, ee, el, tag);
            cur = cur->next;
        }
    }
}

void InitSqStack(SqStack &S) {
    S.top = -1;  //约定栈空时S.top=-1
    S.stackSize = MAX;
}

void PushSqStack(SqStack &S,int data) {
    if(S.stackSize != S.top + 1)
        S.data[++S.top] = data;
}

void PopSqStack(SqStack &S) {
    if(S.top != -1)
        S.top--;
}

int GetHead(SqStack &S){
    if(S.top != -1)
        return S.data[S.top];
}

int EmSqStack(SqStack S){
    if (S.top != -1) return 0;
    else return 1;
}
```
## 测试数据
```cpp
输入顶点数和边数 6 8
输入顶点信息  1 2 3 4 5 6
输入边  1 2 3 1 3 4 2 4 2 3 4 5 3 6 6 2 5 7 5 6 1 4 6 1
```
## 输出
- `(i)k`表示以`k`为**弧尾**的弧**权值**大小为`i`
```cpp
邻接表如下
1 (4)3-->(3)2-->^
2 (7)5-->(2)4-->^
3 (6)6-->(5)4-->^
4 (1)6-->^
5 (1)6-->^
6 ^

关键路径
活动：1-->3  ee = 0    el = 1    n
活动：1-->2  ee = 0    el = 0    y
活动：2-->5  ee = 3    el = 3    y
活动：2-->4  ee = 3    el = 8    n
活动：3-->6  ee = 4    el = 5    n
活动：3-->4  ee = 4    el = 5    n
活动：4-->6  ee = 9    el = 10   n
活动：5-->6  ee = 10   el = 10   y
```
# AOV网络拓扑序列
- AOV网络：以图中**顶点**表示活动，**弧**表示活动之间的优先关系的**有向图**
- 拓扑序列
    - 拓扑序列一般不唯一
    - **有向无环图**一定存在拓扑序列
## 拓扑排序
### 代码实现
```cpp
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<conio.h>
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
    int cnt;  //顶点入度
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
bool topsort(graphlink G, int q[]);  //拓扑排序


int main() {
    int n;
    int q[MAX];  //队列（存储结点下标）
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
                if (!topsort(G, q)) printf("不存在拓扑序列\n");
                else
                    for (int i = 0; i < G->vex; i++)
                            printf("%s ", G->adjlist[q[i]].vertex);
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
        printf("\t3.拓扑序列\n");
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
        G->adjlist[j].cnt++;  //结点入度
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

bool topsort(graphlink G, int q[]) {
    int tt = -1, hh = 0;  //初始化队列
    for (int i = 1; i <= G->vex; i++)
        if (G->adjlist[i].cnt == 0) q[++tt] = i;

    while(hh <= tt) {
        int u = q[hh++];
        arcnode *cur = G->adjlist[u].head;
        while (cur) {  //遍历顶点u的邻接点
            int k = cur->adjvex;
            G->adjlist[k].cnt--;  //更新邻接点入度
            if (G->adjlist[k].cnt == 0) q[++tt] = k;  //入度为零，入队列
            cur = cur->next;
        }
    }
    
    if (tt == G->vex - 1) return true;
    else return false;
}
```
### 测试数据
```cpp
输入顶点数和边数 7 6
输入顶点信息  1 2 3 4 5 6 7
输入边  1 4 1 3 2 4 2 5 5 7 3 6
```
### 输出
```cpp
邻接表如下
1 3-->4-->^
2 5-->4-->^
3 6-->^
4 ^
5 7-->^
6 ^
7 ^

拓扑序列  1 2 3 5 4 6 7
```

# 最短路
- 有向网
## dijkstra
- 贪心
- 某个源点到其余各点的最短路
### 时间复杂度
```cpp
O(n^2), n 表示点数
```
### 代码实现
```cpp
#include<stdio.h>
#include<malloc.h>
#include<conio.h>
#define MAX 20  //最大顶点数
#define NUM 20  //最大字符串长度
#define INF 0x3f3f3f3f //无穷大

typedef struct {  //图的邻接矩阵
    char vexs[MAX][NUM];;  //顶点信息
    int arcs[MAX][MAX];  //顶点关系(边或弧上的权值)
    int vex;  //顶点数
    int arc;  //弧数
}graph, *graphlink;

typedef struct {  //路径数组
    int distance;  //路径长度
    int path;  //弧尾编号
}shortdist;

int menu();  //菜单
void crt_graph(graphlink G);  //创建
void disp_graph(graphlink G);  //显示
void dijkstra(graphlink G, int v, shortdist dist[]);  //图中某一源点到其余各点的最短路径
void print_path(graphlink G, shortdist dist[], int v);  //打印最短路

int main() {
    int n;
    int v;  //源点下标
    shortdist dist[MAX];  //路径数组
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
                printf("输入源点下标：");
                scanf("%d", &v);
                dijkstra(G, v, dist);
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
        printf("\t3.某个源点到其余各点的最短路\n");
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

void dijkstra(graphlink G, int v, shortdist dist[]) {
    int flag[MAX] = {0};
    flag[v] = 1;

    for (int i = 1; i <= G->vex; i++) {  //dist数组初始化
        dist[i].distance = G->arcs[v][i];
        if (G->arcs[v][i] != INF) dist[i].path = v;
        else dist[i].path = -1;
    }

    while (1) {  //按距离递增顺序找出从v出发到其余各顶点的最短路径
        int pos = v;
        int min = INF;  //距离最小值
        for (int i = 1; i <= G->vex; i++)
            if(flag[i] == 0 && dist[i].distance < min) {
                min = dist[i].distance;
                pos = i;
            }

        if (min == INF) break;  //算法结束
        flag[pos] = 1;  //对已完成的顶点做标记
        for (int i = 1; i <= G->vex; i++)   //更新dist
            if (flag[i] == 0 && dist[pos].distance + G->arcs[pos][i] < dist[i].distance) {
                dist[i].distance = dist[pos].distance + G->arcs[pos][i];
                dist[i].path = pos;
            }
    }

    print_path(G ,dist, v);
}

void print_path(graphlink G, shortdist dist[], int v) {

    for (int i = 1; i <= G->vex; i++) {
        if (dist[i].path == -1) printf("不存在！\n");
        else {
            printf("最短距离为：%d\t路径为：", dist[i].distance);
            int k = i;
            while (k != v) {
                printf("%s<-", G->vexs[k]);
                k = dist[k].path;
            }
            printf("%s", G->vexs[v]);
            puts("");
        }
    }

}
```
### 测试数据
```cpp
输入顶点数和边数 6 8
输入顶点信息  a b c d e f
输入边  2 3 5 3 4 50 5 4 20 5 6 60 1 6 100 1 5 30 4 6 10 1 3 10
```
### 输出
```cpp
输入源点下标：1

最短距离为：0   路径为：a
不存在！
最短距离为：10  路径为：c<-a
最短距离为：50  路径为：d<-e<-a
最短距离为：30  路径为：e<-a
最短距离为：60  路径为：f<-d<-e<-a
```
## floyd
- DP(动态规划)
- 每一对顶点之间的最短路
### 时间复杂度
```cpp
O(n^3), n 表示点数
```
## 代码实现
```cpp
#include<stdio.h>
#include<malloc.h>
#include<conio.h>
#define MAX 20  //最大顶点数
#define NUM 20  //最大字符串长度
#define INF 0x3f3f3f3f //无穷大

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
        printf("\t3.每一对顶点之间的最短路\n");
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
### 测试数据
```cpp
输入顶点数和边数 4 8
输入顶点信息  1 2 3 4
输入边  1 2 1 2 4 2 4 3 6 3 4 8 3 1 3 1 4 4 2 3 9 3 2 5
```
### 输出
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
# 最小生成树
- 无向网
## Prim
- 适用于稠密图
### 时间复杂度
```cpp
O(n^2 + m), n 表示点数，e 表示边数
```
### 代码实现
```cpp
#include<stdio.h>
#include<malloc.h>
#include<conio.h>
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
### 测试数据
```cpp
输入顶点数和边数 5 7
输入顶点信息  a b c d e
输入边  1 2 100 1 3 30 1 5 10 5 4 50 3 4 20 2 4 10 2 3 25
```
### 输出
```cpp
边权总和为：70

最小生成树
a(ROOT)
d->b
a->c
c->d
a->e
```
## Kruskal
- 适用于稀疏图
### 时间复杂度
```cpp
O(mlogm),m 表示边数
```
### 代码实现
```cpp
#include<stdio.h>
#include<malloc.h>
#include<conio.h>
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
### 测试数据
```cpp
输入顶点数和边数 6 10
输入顶点信息  a b c d e f 
输入边  1 2 6 1 3 1 1 4 4 2 3 5 3 4 5 2 5 3 4 6 2 5 6 6 5 3 6 3 6 4
```
### 输出
```cpp
边权总和为：15

最小生成树
c->a
f->d
e->b
d->a
c->b
```
