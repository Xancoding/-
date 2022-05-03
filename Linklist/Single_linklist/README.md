## 初始化
```cpp
void init(nodelink &h){
	h->next = NULL;
}
```
## 插入数据
```cpp
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
```
## 删除数据
```cpp
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
```
## 查找数据
```cpp
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
```
## 遍历数据
```cpp
void traversal(nodelink h) {
	nodelink cur = h->next;
	while (cur != NULL) {
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");
}
```



