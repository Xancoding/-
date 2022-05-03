#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<conio.h>

typedef int elemtype;

typedef struct queue{
    elemtype data;
    struct queue *next;
}qnode, *qlink;

typedef struct {
    qlink front;
    qlink back;
}queuenode, *queuelink;

int menu();  //菜单
void init(queuelink q);  //初始化
void push(queuelink q, elemtype e);  //入队
void pop(queuelink q);  //出队
void traversal(queuelink q);  //遍历队列
int empty(queuelink q);  //判空
void top(queuelink q);  //取队头

int main() {
    int n;
    elemtype e;
    queuenode q;

    while (1) {
        n = menu();
        switch(n) {
            case 1:
                init(&q);
                printf("按任意键继续！\n");
                getch(); break;
            case 2:
                printf("请输入入队的数据：");
                scanf("%d", &e);
                push(&q, e);
                printf("按任意键继续！\n");
                getch(); break;
            case 3:
                traversal(&q);
                printf("按任意键继续！\n");
                getch(); break;
            case 4:
                pop(&q);
                printf("按任意键继续！\n");
                getch(); break;
            case 5:
                empty(&q);
                printf("按任意键继续！\n");
                getch(); break;
            case 6:
                top(&q);
                printf("按任意键继续！\n");
                getch(); break;
        }
    }
}

int menu() {
    int n;
    while (1) {
        printf("*****欢迎使用本系统*****\n");
        printf("\t1.初始化\n");
        printf("\t2.入队\n");
        printf("\t3.遍历队列\n");
        printf("\t4.出队\n");
        printf("\t5.队列是否为空?\n");
        printf("\t6.输出栈顶元素\n");
        printf("************************\n");
        printf("请输入数字：");
        scanf("%d", &n);
        if (n > 6 || n < 0) {
            printf("输入错误，请重新输入！\n");
        } else return n;
    }
}

void init(queuelink q) {
    q->front = q->back = (qlink)malloc(sizeof(qnode));
    q->front->next = NULL;
}

void push(queuelink q, elemtype e) {
    qlink tmp = (qlink)malloc(sizeof(qnode));
    tmp->data = e;
    tmp->next = NULL;
    q->back->next = tmp;
    q->back = tmp;
}

void pop(queuelink q) {
    if (q->front == q->back) {
        printf("队列为空！\n");
        return ;
    }

    qlink tmp = q->front->next;
    q->front->next = tmp->next;
    printf("出队元素为：%d\n", tmp->data);
    if (q->back == tmp) q->back = q->front;
    free(tmp);
}

void traversal(queuelink q) {
    if (q->front == q->back) {
        printf("队列为空！\n");
        return ;
    }

    qlink cur = q->front->next;
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    puts("");
}

int empty(queuelink q) {
    if (q->front == q->back) {
        printf("队列为空！\n");
        return 1;
    } else {
        printf("队列不为空！\n");
        return 0;
    }
}

void top(queuelink q) {
    if (q->front == q->back) {
        printf("队列为空！\n");
        return ;
    }
    printf("队头元素为：%d", q->front->next->data);
    puts("");
}
