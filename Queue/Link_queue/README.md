## 初始化
```cpp
void init(queuelink q) {
    q->front = q->back = (qlink)malloc(sizeof(qnode));
    q->front->next = NULL;
}
```
## 判断队列是否为空
```cpp
int empty(queuelink q) {
    if (q->front == q->back) {
        printf("队列为空！\n");
        return 1;
    } else {
        printf("队列不为空！\n");
        return 0;
    }
}
```
## 入队
```cpp
void push(queuelink q, elemtype e) {
    qlink tmp = (qlink)malloc(sizeof(qnode));
    tmp->data = e;
    tmp->next = NULL;
    q->back->next = tmp;
    q->back = tmp;
}
```
## 出队
```cpp
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
```
## 遍历队列
```cpp
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
```
## 取队头元素
```cpp
void top(queuelink q) {
    if (q->front == q->back) {
        printf("队列为空！\n");
        return ;
    }
    printf("队头元素为：%d", q->front->next->data);
    puts("");
}
```



