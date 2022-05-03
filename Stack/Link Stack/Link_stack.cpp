#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<conio.h>

typedef int elemtype;

typedef struct stack{
    elemtype data;
    struct stack *next;
} snode, *slink;

int menu();  //菜单
void init(slink &h); //初始化
int empty(slink h); //判断栈是否为空
void push(slink &h, elemtype e);  //入栈
void pop(slink &h);  //出栈
void traversal(slink h);  //遍历栈
void top(slink h);  //取栈顶元素

int main() {
    int n;
    elemtype e;
    slink h;

    while (1) {
        n = menu();
        switch(n) {
            case 1:
                init(h);
                printf("按任意键继续！\n");
                getch(); break;
            case 2:
                printf("请输入入栈的数据：");
                scanf("%d", &e);
                push(h, e);
                printf("按任意键继续！\n");
                getch(); break;
            case 3:
                traversal(h);
                printf("按任意键继续！\n");
                getch(); break;
            case 4:
                pop(h);
                printf("按任意键继续！\n");
                getch(); break;
            case 5:
                empty(h);
                printf("按任意键继续！\n");
                getch(); break;
            case 6:
                top(h);
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
        printf("\t2.入栈\n");
        printf("\t3.遍历栈\n");
        printf("\t4.出栈\n");
        printf("\t5.栈是否为空?\n");
        printf("\t6.输出栈顶元素\n");
        printf("************************\n");
        printf("请输入数字：");
        scanf("%d", &n);
        if (n > 6 || n < 0) {
            printf("输入错误，请重新输入！\n");
        } else return n;
    }

}

void init(slink &h) {
    h = NULL;
}

int empty(slink h) {
    if (h == NULL) {
        printf("栈为空！\n");
        return 1;
    } else {
        printf("栈不为空！\n");
        return 0;
    }
}

void push(slink &h, elemtype e) {
    slink tmp = (slink)malloc(sizeof(snode));
    tmp->data = e;
    tmp->next= h;
    h = tmp;
}

void pop(slink &h) {
    if (h == NULL) {
        printf("栈为空！\n");
        return ;
    }
    slink tmp = h;
    h = h->next;
    printf("出栈的元素为：%d\n", tmp->data);


}

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

void top(slink h) {
    if (h == NULL) {
        printf("栈为空！\n");
        return ;
    }

    printf("栈顶元素为：%d\n", h->data);

}
