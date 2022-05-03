#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<malloc.h>

typedef int elemtype;

typedef struct node{
	elemtype data;
	struct node *next;
}node, *nodelink;

int menu();  //菜单
void init(nodelink &h); //初始化
void insert(nodelink h, int k, elemtype e); //插入数据
void traversal(nodelink h);  //遍历数据
void remove(nodelink h, int k);  //删除数据
void search(nodelink h, elemtype e);  //查找数据

int main(){
    int n;
    int k;
    elemtype e;
    nodelink h = (nodelink)malloc(sizeof (node));
    while (1) {
        n = menu();
        switch(n) {
            case 1:
                init(h);
                printf("按任意键继续！\n");
                getch();  break;
            case 2:
                printf("请输入要插入的数据：");
                scanf("%d", &e);
                printf("请输入要插入的位置");
                scanf("%d", &k);
                insert(h, k, e);
                printf("按任意键继续！\n");
                getch();  break;
            case 3:
                traversal(h);
                printf("按任意键继续！\n");
                getch();  break;
            case 4:
                printf("请输入要删除的数据位置：");
                scanf("%d", &k);
                remove(h, k);
                printf("按任意键继续！\n");
                getch();  break;
            case 5:
                printf("请输入要查找的数据的值：");
                scanf("%d", &e);
                search(h, e);
                printf("按任意键继续！\n");
                getch();  break;
        }
    }
}

int menu() {
    int n;
    while (1) {
        printf("*****欢迎使用本系统*****\n");
        printf("\t1.初始化\n");
        printf("\t2.插入数据\n");
        printf("\t3.遍历输出数据\n");
        printf("\t4.删除数据\n");
        printf("\t5.查找数据\n");
        printf("************************\n");
        printf("请输入数字：");
        scanf("%d", &n);
        if (n > 6 || n < 0) {
            printf("输入错误，请重新输入!\n");
        } else return n;
    }
}

void init(nodelink &h){
	h->next = NULL;
}

void insert(nodelink h, int k, elemtype e) {
	nodelink tmp = (nodelink)malloc(sizeof(node));
	tmp->data = e;
	nodelink cur = h;
	if (k <= 0) {
		printf("输入错误，请重新输入！\n");
		return ;
	}
	while (--k) {
		cur = cur->next;
		if (cur == NULL) break;
	}
	if (cur == NULL) {
		printf("插入失败！\n");
		return ;
	}
	tmp->next = cur->next;
	cur->next = tmp;
	printf("插入成功！\n");
}

void traversal(nodelink h) {
	nodelink cur = h->next;
	while (cur != NULL) {
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");
}

void remove(nodelink h, int k) {
	nodelink cur = h;
	while (--k) {
		cur = cur->next;
		if (cur == NULL) break;
	}
	if (cur == NULL) {
		printf("删除失败！\n");
		return ;
	}
	printf("删除的数据为：%d\n", cur->next->data);
	cur->next = cur->next->next;
	printf("删除成功！\n");
}

void search(nodelink h, elemtype e) {
	int k = 0;
	nodelink cur = h;
	while (cur != NULL) {
		if (cur->data == e) break;
		k++;
		cur = cur->next;
	}
	if (cur == NULL){
		printf("找不到该数据！\n");
		return ;
	} else {
		printf("查找成功！\n");
		printf("该数据的位置为：%d\n", k);
		return ;
	}
}
