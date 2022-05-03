## 表达式求值（整型数据）
```cpp
#include<stdio.h>
#include<string.h>
#include <ctype.h>
#define N 10000

int num[N];  //存放运算对象
char op[N]; //存放运算符
int h1;
int h2;

int prior(char a);  //判断运算符优先级
void eval();  //取两个栈顶元素进行运算后再将结果入栈
int getVal(char *str);  //求表达式值

int main() {

    char null[] = "#";
    while (1) {
        char str[N];
        char s[N];

        printf("请输入表达式(输入null退出)：");
        scanf("%s", str);
        if (strcmp(str, null) == 0) return 0;

        printf("表达式结果为%d:", getVal(str));
        printf("\n");
    }
}

int prior(char a) {
    if (a == '*' || a == '/') return 2;
    else if (a == '+' || a == '-') return 1;
}

void eval() {
    int b = num[h1--];
    int a = num[h1--];
    char c = op[h2--];
    int x;
    if (c == '+') x = a + b;
    else if (c == '-') x = a - b;
    else if (c == '*') x = a * b;
    else x = a / b;
    num[++h1] = x;
}

int getVal(char *str) {
    h1 = -1;
    h2 = -1;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        char c = str[i];
        if (isdigit(c)) {
            int x = 0, j = i;
            while (j < len && isdigit(str[j]))
                x = x * 10 + str[j ++ ] - '0';
            i = j - 1;
            num[++h1] = x;
        }
        else if (c == '(') op[++h2] = c;
        else if (c == ')') {
            while (op[h2] != '(') eval();
            h2--;
        } else {
            while (h2 != -1 && op[h2] != '(' && prior(op[h2]) >= prior(c)) eval();
            op[++h2] = c;
        }
    }

    while (h2 != -1) eval();
    return num[h1];
}
```
