# 二分查找

>Although the basic idea of binary search is comparatively straightforward, 
>the details can be surprisingly tricky... 

## 1 .基本二分

在一个数组中查找某个数基本操作就是以下两种情况：

**在排序数组中查找第一个大于x的数(upper_bound)**

**在排序数组中查找第一个大于等于x的数(lower_cound)**

```c
int upper_bound(int A[],int l,int r,int x){   //[l,r)
    while(l < r){
        int mid = l + (r - l)/2;
        if(x >= A[mid]) l = mid + 1;
        else r = mid;
    }
    return l;
}
int lower_bound(int A[],int l,int r,int x){     //[l,r)
    while(l < r){
        int mid = l + (r - l)/2;
        if(x > A[mid]) l = mid + 1;
        else r = mid;
    }
    return l;
}
```

其他情况都是以上两个形式的简单变形:

（1）查找x第一次出现和最后一次出现的位置，x可能不出现

第一次出现就是lower_bound的位置，并且判断这个位置的值是否等于x；

最后一次出现就是upper_bound - 1的位置，并判断这个位置的值是否等于x。

[34. 在排序数组中查找元素的第一个和最后一个位置](https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/)

（2）稍微复杂一点

[33. 搜索旋转排序数组](https://leetcode-cn.com/problems/search-in-rotated-sorted-array/)

[81. 搜索旋转排序数组 II](https://leetcode-cn.com/problems/search-in-rotated-sorted-array-ii/)

[658. 找到 K 个最接近的元素](https://leetcode-cn.com/problems/find-k-closest-elements/)

$i$从0开始遍历，以$i$为起始的k个值是最优解的充要条件：
$$
|a_i - x| \leq |a_{i+k} - x|
$$


进一步，上述充要条件简化为：
$$
x - a_i \leq a_k - x
$$


（1）如果$a_i < a_k < x$，$a_i$不应该为答案，对应的 $x - a_i > a_k -x$；

（2）如果$x < a_i < a_k$，$a_i$应该为答案，对应的 $x - a_i < a_k -x$；

所以我们的目标就是从头开始找到第一个满足$x - a_i \leq a_k - x$的$i$，数组有序，所以可以使用二分查找。



