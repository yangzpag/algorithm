# 二分查找

>Although the basic idea of binary search is comparatively straightforward, 
>the details can be surprisingly tricky... 

## 1 .基本二分

在一个数组中查找某个数基本操作就是以下两种情况：

**在排序数组中查找第一个大于x的数(upper_bound)**

**在排序数组中查找第一个大于等于x的数(lower_bound)**

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

题目：[34. 在排序数组中查找元素的第一个和最后一个位置](https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/)

（2）稍微复杂一点

将升序数组在某个位置旋转，然后搜索，这道题的元素不重复。

两种思路：

* 两次二分，第一次找到分割点，第二次对部分进行二分
* 直接一次二分

题目：[33. 搜索旋转排序数组](https://leetcode-cn.com/problems/search-in-rotated-sorted-array/)

上一题的扩展题，允许重复。思路与上一题类似，需要增加一些判断。这道题目前看到的解法，只能做到平均复杂度为$log n$，最坏情况是O(n)的。

题目：[81. 搜索旋转排序数组 II](https://leetcode-cn.com/problems/search-in-rotated-sorted-array-ii/)



[154. 寻找旋转排序数组中的最小值 II](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array-ii/)



（3）拓展到二维

搜索二维数组，每行中的整数从左到右按升序排列；每行的第一个整数大于前一行的最后一个整数。

解题思路很直接：二分在哪一行，再二分在哪一列。

题目：[74. 搜索二维矩阵](https://leetcode-cn.com/problems/search-a-2d-matrix/)





## 2.与二叉树相关

题目：[222. 完全二叉树的节点个数](https://leetcode-cn.com/problems/count-complete-tree-nodes/)



## 3.二分 + 贪心

第k大元素

[378. 有序矩阵中第K小的元素](https://leetcode-cn.com/problems/kth-smallest-element-in-a-sorted-matrix/)

```c++
int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        if(n == 0) return -1;
        int l = matrix[0][0];
        int r = matrix[n-1][n-1];

        while(l < r){
            int mid = l + (r-l)/2;
            if(getsize(matrix,mid) < k) l = mid + 1;
            else r = mid;
        }
        return l;
    }

    int getsize(vector<vector<int>>& matrix,int num){
        int cnt = 0;
        int n = matrix.size();
        int i = n-1,j = 0;
        while(i >= 0){
            if(j < n && num >= matrix[i][j]) j ++;
            else{
                cnt += j;
                i--;
            }
        }
        return cnt;
    }
```

[668. 乘法表中第k小的数](https://leetcode-cn.com/problems/kth-smallest-number-in-multiplication-table/)

[786. 第 K 个最小的素数分数](https://leetcode-cn.com/problems/k-th-smallest-prime-fraction/)



[719. 找出第 k 小的距离对](https://leetcode-cn.com/problems/find-k-th-smallest-pair-distance/)

在递增数组中，利用双指针可以以$O(n)$时间复杂度求解满足以下条件的元组个数：
$$
a[j] - a[i] <= val,i < j
$$

> 注意是递增数组，类似的问题如果是非递增数组，只能在O(nlogn)的时间复杂度内完成，使用归并排序（归并过程也使用了双指针法进行归并求值）或者线段树，类似问题的见题：[327. 区间和的个数](https://leetcode-cn.com/problems/count-of-range-sum/)

因此我们可以对所有可能的值进行二分，即求得某个值mid，满足$a[j] - a[i] <= mid,i < j$的元组个数为k。

```c++
    int smallestDistancePair(vector<int>& nums, int k) {
        
        sort(nums.begin(),nums.end());
        int n = nums.size();
        if(n*(n-1)/2 < k) return -1;
        int l = 0,r = nums[n-1] - nums[0];
        while(l < r){
            int mid = l + (r - l)/2;
            int right = 0;
            int cnt = 0;
            for(int i = 0;i < n;i++){
                while(right < n && nums[right] - nums[i] <= mid){
                    right++;
                }
                cnt += right - i - 1;
            }
            if(cnt >= k) r = mid;
            else l = mid + 1;
        }
        return l;
    }
```

[644. 最大平均子段和 II](https://leetcode-cn.com/problems/maximum-average-subarray-ii/)

这道题最难的部分是以下子问题：判断数组中是否有长度大于等于k的连续序列的平均值大于等于d，即：
$$
sum(a_i,...,a_j) \geq (j-i+1)*d , j-i+1\geq k
$$
将原数组全部减去d，得到新的数组：
$$
a^{'}_1,a^{'}_2,...,a^{'}_n = a_1 - d,a_2 - d,...,a_n - d
$$
问题转化为：
$$
sum(a^{'}_i,...,a^{'}_j) \geq 0, j - i + 1 \geq k
$$
令：$presum(i) = sum(a^{'}_1,...,a^{'}_i)$

最后转化为：
$$
presum(j) - min\{presum(0),...,presum(j-k)\} \geq 0, j \geq k
$$
所以可以在O(n)的时间复杂度处理该子问题。



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



