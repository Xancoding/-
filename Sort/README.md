- **非线性时间比较类排序**：通过比较来决定元素间的相对次序，其时间复杂度不能突破O(nlogn)

- **线性时间非比较类排序**：不通过比较来决定元素间的相对次序，它可以突破基于比较排序的时间下界，以线性时间运行 
![](https://git.acwing.com/ZagY/learn-data-structures/-/raw/main/Sort/images/2.png " ")
![](https://git.acwing.com/ZagY/learn-data-structures/-/raw/main/Sort/images/1.png " ")
# 插入类排序
## 直接插入排序  
- 适用：基本有序
```cpp
void insert_sort() 
{
    for (int i = 1; i < n; i ++ )
    {
        int x = a[i];
        int j = i - 1;
        
        while (j >= 0 && x < a[j])
        {
            a[j + 1] = a[j];
            j -- ;
        }
        a[j + 1] = x;
    }
}
```
## 希尔排序
- 适用：数据量大
- **直接插入排序算法**的改进
### 算法思想
![希尔排序](https://www.bilibili.com/video/BV1BK4y1478X/?spm_id_from=333.788"希尔排序")
- 将整个待排序记录序列按给定增量分成若干子序列
- 分别对各个子序列进行直接插入排序
- 当整个序列**基本有序**时，再对全体记录进行一次直接插入排序
- 选择排序
```cpp
void shell_sort()
{
    //初始增量；n / 2，每一趟之后除以二
    int gap = n / 2;
    while (gap > 0)
    {
        //每一趟采用插入排序
        for (int i = gap; i < n; i++)
        {
            int j;
            int x = a[i];
            for (j = i; j >= gap && x < a[j - gap]; j -= gap)
                a[j] = a[j - gap];
            a[j] = x;
        }
        gap /= 2;
    }
}
```
# 交换类排序
## 冒泡排序
```cpp
void bubble_sort()
{
    for (int i = n - 1; i >= 1; i -- )
    {
        bool flag = true;
        for (int j = 1; j <= i; j ++ )
            if (a[j - 1] > a[j])
            {
                swap(a[j - 1], a[j]);
                flag = false;
            }
        if (flag) return;
    }
}
```
## 快速排序
- 适用：广泛（最快）
- **分治策略**
```cpp
void quick_sort(int l, int r)
{
    if (l >= r) return ;
    
    int x = a[l + r >> 1], i = l - 1, j = r + 1;
    while (i < j)
    {
        do i++; while (a[i] < x);
        do j--; while (a[j] > x);
        if (i < j) swap(a[i], a[j]);
    }
    quick_sort(l, j), quick_sort(j + 1, r);
}
```
# 选择类排序
## 选择排序
-  适用：数据量少
```cpp
void select_sort()
{
    for (int i = 0; i < n - 1; i ++ )  //进行n - 1趟扫描
    {
        int k = i;
        for (int j = i + 1; j < n; j ++ )
        {
            if (a[j] < a[k])
                k = j;
        }
        swap(a[i], a[k]);
    }
        
}
```
## 堆排序
- [堆排序](https://www.cnblogs.com/wanglei5205/p/8733524.html "堆排序")
- 此排序使用了模拟堆，为了使最后一个非叶子节点的编号为n / 2，数组编号从1开始
```cpp
#include<iostream>

using namespace std;

const int N = 100010;

int h[N], cnt;

void down(int u) {
    int t = u;
    if (2 * u <= cnt && h[2 * u] < h[t]) t = 2 * u;
    if (2 * u + 1 <= cnt && h[2 * u + 1] < h[t]) t = 2 * u + 1;
    
    if (t != u) {
        swap(h[u], h[t]);
        down(t);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    for (int i = 1; i <= n; i++) scanf("%d", &h[i]);
    cnt = n;
    
    for (int i = n / 2; i >= 1; i--) down(i);
    
    while (m--) {
        printf("%d ", h[1]);
        
        h[1] = h[cnt--];
        down(1);
    }
    puts("");

    
    return 0;
}
```
# 归并类排序
## 二路归并排序
- 适用：不受数据影响，所需空间与n成正比
- **分治策略**
### 算法思想
- 将一个具有`n`个待排序记录的序列看成是`n`个**长度为1**的有序序列
- 进行两两归并，得到`n / 2`个**长度为2**的有序序列
- 重复上述步骤，直至得到一个**长度为n**的有序序列为止
```cpp
void merge_sort(int l, int r)
{
    if (l >= r) return;
    int temp[N];
    int mid = l + r >> 1;
    merge_sort(l, mid), merge_sort(mid + 1, r);
    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)
    {
        if (a[i] < a[j]) temp[k ++ ] = a[i ++ ];
        else temp[k ++ ] = a[j ++ ];
        
    }
    while (i <= mid) temp[k ++ ] = a[i ++ ];
    while (j <= r) temp[k ++ ] = a[j ++ ];
    for (int i = l, j = 0; i <= r; i ++ , j ++ ) a[i] = temp[j];
}
```
# 桶排序
- 适用：均匀分布的数据
## 算法思路
![桶排序(数组实现)](https://www.geeksforgeeks.org/bucket-sort-2/?ref=lbp "桶排序")
![桶排序(链表实现)](https://blog.csdn.net/liaoshengshi/article/details/47320023 "桶排序")
- 将待排序的序列分到若干个桶中，每个桶内的元素再进行个别排序
- 设置固定数量的空桶
- 把数据放到对应的桶中
- 对每个不为空的桶中数据进行排序
- 拼接不为空的桶中数据，得到结果
```cpp
void bucket_sort(vector<float>& nums)
{
    int n = nums.size();
    int max = *max_element(nums.begin(), nums.end());
    int min = *min_element(nums.begin(), nums.end());
    int bs = 100;  //桶的个数
    float range = (max - min) / bs + 1;  //每个桶所包含数的范围
    vector<vector<float>> bucket(bs);  //生成bs个桶

    //将数组元素分散到这些桶中
    for (int i = 0; i < n; ++i)
    {
        bucket[(nums[i] - min) / range].push_back(nums[i]);
    }

    //将桶中数据复制回原数组
    int idx = 0;
    for (int i = 0; i < bs; ++i)
    {
        //桶内排序
        sort(bucket[i].begin(), bucket[i].end());

        //将桶中数据复制回原数组
        int sz = bucket[i].size();
        for (int j = 0; j < sz; ++j)
        {
            nums[idx++] = bucket[i][j];
        }
    }

}
```
## 基数排序
- 适用：max和min的差值不大
- 基数排序是桶排序的特例，优势是可以处理浮点数和负数，劣势是还要配合别的排序函数
### 算法思路
![基数排序](https://www.runoob.com/w3cnote/radix-sort.html "基数排序")
- 通过**分配**和**收集**过程来实现排序
```cpp
//最大位数
int getMaxDigit()
{
    int max = a[0];
    for (int i = 1; i < n; i ++ )
        if (max < a[i]) max = a[i];

    int cnt = 0;
    while (max > 0)
    {
        cnt++;
        max /= 10;
    }

    return cnt;
}

//基数排序
void radix_sort()
{
    int d = getMaxDigit();  //最大位数
    int tmp[n];  //临时数组
    int count[10]; //计数器
    int radix = 1;  //位数

    //进行d次排序
    for(int i = 1; i <= d; i++)
    {
        //每次分配前清空计数器
        for(int j = 0; j < 10; j++)
            count[j] = 0;

        //统计每个桶中的记录数
        for(int j = 0; j < n; j++)
        {
            int  k = (a[j] / radix) % 10;
            count[k]++;
        }

        //将tmp中的位置依次分配给每个桶
        for(int j = 1; j < 10; j++)
            count[j] += count[j - 1];

        //将所有桶中记录依次收集到tmp中
        for(int j = n - 1; j >= 0; j--)
        {
            int k = (a[j] / radix) % 10;
            tmp[count[k] - 1] = a[j];
            count[k]--;
        }

        //将临时数组的内容复制到a中
        for(int j = 0; j < n; j++)
            a[j] = tmp[j];

        radix = radix * 10;
    }

}
```
# 计数排序
- 适用：max和min的差值不大
### 算法思路
![计数排序](https://www.bilibili.com/video/BV1KU4y1M7VY?spm_id_from=333.337.search-card.all.click "计数排序")
- 借助足够大的辅助数组，把数字排在一个相对位置不会错的地方，最后并拢
```cpp
void counting_sort()
{
    //寻找最大元素
    int max = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > max) max = a[i];

    //分配一个长度为max+1的数组存储计数，并初始化为0
    int count[max + 1];
    memset(count, 0, sizeof(int) * (max + 1));

    //计数
    for (int i = 0; i < n; i++)
        count[a[i]]++;

    //统计计数的累计值
    for (int i = 1; i < max + 1; i++)
        count[i] += count[i - 1];

    //创建一个临时数组保存结果
    int output[n];

    //将元素放到正确的位置上
    for (int i = 0; i < n; i++)
    {
        output[count[a[i]]  - 1] = a[i];
        count[a[i]]--;
    }

    //将结果复制回原数组
    for (int i = 0; i < n; i++)
        a[i] = output[i];
}
```
