## 存储
- 邻接矩阵
```cpp
#define MAX 20  //最大顶点数
#define NUM 20  //最大字符串长度

typedef struct {
    char vexs[MAX][NUM];;  //顶点信息
    int arcs [MAX][MAX];  //顶点关系(边或弧上的权值)
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
    for (int i = 0; i < G->vex; i++) scanf("%s", G->vexs[i]);  //顶点信息
    for (int i = 0; i < G->vex; i++)
        for (int j = 0; j < G->vex; j++)
            G->arcs[i][j] = 0;  //邻接矩阵初始化
    printf("输入边\n");
    for (int k = 0; k < G->arc; k++) {  //读入边
        int i, j;
        scanf("%d%d", &i, &j);
        G->arcs[i - 1][j - 1] = 1;
        G->arcs[i - 1][j - 1] = 1;
    }
}
```
- 邻接表
```cpp
```
## 显示
- 邻接矩阵
```cpp
void disp_graph(graphlink G) {
    printf("顶点如下\n");
    for (int i = 0; i < G->vex; i++) printf("%s ", G->vexs[i]);
    printf("\n邻接矩阵如下\n");
    for (int i = 0; i < G->vex; i++) {
        for (int j = 0; j < G->vex; j++)
            printf("%4d", G->arcs[i][j]);
        puts("");
    }
}
```
- 邻接表
```cpp
```
