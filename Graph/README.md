## 存储
- 邻接矩阵
```cpp
typedef struct {
    char vexs[MAX][NUM];;  //顶点信息
    int arcs[MAX][MAX];  //顶点关系(边或弧上的权值)
    int vex;  //顶点数
    int arc;  //弧数
}graph, *graphlink;
```
- 邻接表
```cpp
#define MAX 20  //最大顶点数
#define NUM 20  //最大字符串长度

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
```
## 创建
- 邻接矩阵
```cpp
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
        
        /* 无向图 */
        //G->arcs[j][i] = 1;  
    }
}
```
- 邻接表
```cpp
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

        /* 无向图 */
        // arcnode *q = new arcnode;
        // q->adjvex = i;
        // q->next = G->adjlist[j].head;  //头插
        // G->adjlist[j].head = q;
    }
}
```
## 显示
- 邻接矩阵
```cpp
void disp_graph(graphlink G) {
    printf("顶点如下\n");
    for (int i = 1; i <= G->vex; i++) printf("%s ", G->vexs[i]);
    printf("\n邻接矩阵如下\n");
    for (int i = 1; i <= G->vex; i++) {
        for (int j = 1; j <= G->vex; j++)
            printf("%4d", G->arcs[i][j]);
        puts("");
    }
}
```
- 邻接表
```cpp
```
## 遍历
### DFS
- 邻接矩阵
```cpp
void dfs(graphlink G, int v, int visited[]) {  //v为出发点编号
    printf("%s ", G->vexs[v]);
    visited[v] = 1;
    for (int w = 1; w <= G->vex; w++)
        if (G->arcs[v][w] != 0 && visited[w] == 0)
            dfs(G, w, visited);
}
```
### BFS
- 邻接矩阵
```cpp
void bfs(graphlink G, int v, int visited[], queue<int>que) {  //que存储已访问过的顶点编号
    printf("%s ", G->vexs[v]);
    visited[v] = 1;
    que.push(v);

    while (!que.empty()) {
        int u = que.front();  que.pop();
        for (int w = 1; w <= G->vex; w++)   //找出u所有邻接点
            if (G->arcs[u][w] != 0 && visited[w] == 0) {
                printf("%s ", G->vexs[w]);
                visited[w] = 1;
                que.push(w);
            }
    }
}
```
## 测试数据
```cpp
![](https://git.acwing.com/ZagY/learn-data-structures/-/raw/main/Graph/picture/1.jpg "")
输入顶点数和边数 9 11
输入顶点信息  1 2 3 4 5 6 7 8 9
输入边  3 2 3 1 2 4 1 4 1 2 4 9 3 6 6 5 5 8 5 7 7 8
```
## 输出
```cpp

```
