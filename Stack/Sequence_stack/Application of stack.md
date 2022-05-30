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
### 表达式求值（实数）（未完成）
```cpp
#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include<math.h>
#define N 10000

double num[N];  //存放运算对象
char op[N]; //存放运算符
int h1;
int h2;

int prior(char a);  //判断运算符优先级
void eval();  //取两个栈顶元素进行运算后再将结果入栈
double getVal(char *str);  //求表达式值
double chToDb(char str[]);  //将数字字符串转换成实数

int main() {

    char null[] = "#";
    while (1) {
        char str[N];
        char s[N];

        printf("请输入表达式(输入null退出)：");
        scanf("%s", str);
        if (strcmp(str, null) == 0) return 0;

        printf("表达式结果为%lf:", getVal(str));
        printf("\n");
    }
}

//判断运算符优先级
int prior(char a) {
    if (a == '*' || a == '/') return 2;
    else if (a == '+' || a == '-') return 1;
}

//取两个栈顶元素进行运算后再将结果入栈
void eval() {
    double b = num[h1--];
    double a = num[h1--];
    char c = op[h2--];
    double x;
    if (c == '+') x = a + b;
    else if (c == '-') x = a - b;
    else if (c == '*') x = a * b;
    else x = a / b;
    num[++h1] = x;
}

//求表达式值
double getVal(char *str) {
    h1 = -1;
    h2 = -1;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        char c = str[i];
        if (isdigit(c)) {   //处理实数
            int j = i;
            while (isdigit(str[j]) || str[j] == '.')
                j++;
            char val[N];
            strncpy(val, str + i, j - i + 1);  //截取字符串
            num[++h1] = chToDb(val);
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

//将数字字符串转换成实数
double chToDb(char str[]) {
    int n = -1;
    double x = 0, y= 0;

    //确定小数点下标
    for (int i = 0; i < strlen(str); i++)
        if (str[i]  == '.') {
            n = i;
            break;
        }

    //整数部分
    for (int i = n - 1; i >= 0; i--)
        x += (str[i] - 48) * pow(10, n - 1 - i);

    //小数部分
    for (int i = n + 1; i < strlen(str); i++)
        y += (str[i] - 48) * pow(10, n - i);

    return x + y;
}
```
### 将字符串转换为实数
```cpp
#include<stdio.h>
#include "string.h"
#include "math.h"
//将数字字符串转换成实数
double chToDb(char str[]) {
    int n = -1;
    double x = 0, y= 0;

    //确定小数点下标
    for (int i = 0; i < strlen(str); i++)
        if (str[i]  == '.') {
            n = i;
            break;
        }

    //整数部分
    for (int i = n - 1; i >= 0; i--)
        x += (str[i] - 48) * pow(10, n - 1 - i);

    //小数部分
    for (int i = n + 1; i < strlen(str); i++)
        y += (str[i] - 48) * pow(10, n - i);

    return x + y;
}

int main() {
    char str[10];
    scanf("%s", str);

    double a = chToDb(str);

    printf("%lf", a);
}
```
## 括号匹配
```cpp
#include<stdio.h>
#include<string.h>

 const int N = 10;

 int main() {
     char str[N];
     char st[N];
     char null[] = "null";
     while (1) {
         int top = -1;
         printf("请输入括号(输入null退出)：");
         scanf("%s", str);
        if (strcmp(str, null) == 0) return 0;
         for (int i = 0; str[i]; i++) {
             if (str[i] == '(' || str[i] == '[' || str[i] == '{') {
                 st[++top] = str[i];
             }else if (str[i] == ')' && st[top] == '(' || str[i] == ']' && st[top] == '[' || str[i] == '}' && st[top] == '{') {
                 top--;
             } else {  //匹配失败
                 top = 0;
                 break;
             }
         }
         if (top == -1)printf("匹配成功！\n");
         else printf("匹配失败！\n");
     }
 }
```
