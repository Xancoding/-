## 初始化
```cpp
void init(slink &h) {
    h = NULL;
}
```
## 判断栈是否为空
```cpp
int empty(slink h) {
    if (h == NULL) {
        printf("栈为空！\n");
        return 1;
    } else {
        printf("栈不为空！\n");
        return 0;
    }
}
```
## 入栈
```cpp
void push(slink &h, elemtype e) {
    slink tmp = (slink)malloc(sizeof(snode));
    tmp->data = e;
    tmp->next= h;
    h = tmp;
}
```
## 出栈
```cpp
void pop(slink &h) {
    if (h == NULL) {
        printf("栈为空！\n");
        return ;
    }
    slink tmp = h;
    h = h->next;
    printf("出栈的元素为：%d\n", tmp->data);
}
```
## 遍历栈
```cpp
void traversal(slink h) {
    if (h == NULL) {
        printf("栈为空！\n");
        return ;
    }

    slink cur = h;
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    puts("");
}
```
## 取栈顶元素
```cpp
void top(slink h) {
    if (h == NULL) {
        printf("栈为空！\n");
        return ;
    }
    printf("栈顶元素为：%d\n", h->data);
}
```



