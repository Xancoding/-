## 插入排序
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
## 选择排序
```cpp
void select_sort()
{
    for (int i = 0; i < n; i ++ )
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
## 希尔排序
```cpp
void shell_sort()
{
    for (int gap = n >> 1; gap; gap >>= 1)
    {
        for (int i = gap; i < n; i ++ )
        {
            int x = a[i];
            int j;
            for (j = i; j >= gap && a[j - gap] > x; j -= gap)
                a[j] = a[j-gap];
            a[j] = x;
        }
    }
}
```
## 快速排序
```cpp
void quick_sort(int l, int r)
{
    if (l >= r) return ;
    
    int x = a[l + r>> 1], i = l - 1, j = r + 1;
    while (i < j)
    {
        while (a[++ i] < x);
        while (a[-- j] > x);
        if (i < j) swap(a[i], a[j]);
    }
    sort(l, j), sort(j + 1, r);
}
```
