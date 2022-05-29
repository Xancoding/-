## 数据类型定义
```cpp
typedef struct stack {
    char data[MAX][NUM];  //data是一个指针变量，存放一片连续空间的首地址
    int top;  //指示栈顶的位置 
    int stackSize;  //栈的容量 
}SqStack;
```

## 初始化
```cpp
void InitSqStack(SqStack &S) {
    S.top = -1;  //约定栈空时S.top=-1
    S.stackSize = MAX;
}
```
## 入栈
```cpp
void PushSqStack(SqStack &S,char *data) {
    if(S.stackSize != S.top + 1)
        strcpy(S.data[++S.top], data);
}
```
## 出栈
```cpp
void PopSqStack(SqStack &S) {
    if(S.top != -1)
        S.top--;
}
```
## 遍历栈
```cpp
void TraversSqStack(SqStack S) {
	if(S.top != -1) 
        for(int i = S.top; i >= 0; i--)
	    printf("%s ",S.data[i]);
	printf("\n");
	
}
```
## 取栈顶
```cpp
void GetStackHead(SqStack &S, char* &p){
    if(S.top != -1)
        strcpy(p, S.data[S.top]);
}
```
## 判空
```cpp
int EmSqStack(SqStack S){
    if (S.top != -1) return 0;
    else return 1;
}
```
