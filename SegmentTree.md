# 区间查询问题

**回顾**

首先我们知道传统查询问题可以分为：点查询，范围查询。点查询是范围查询子集，也就是支持范围查询的数据结构一定支持点查询。

对于查询的数据是否可以改变，又可以分为静态查询和动态查询。所谓静态查询，就是说数据给定后不再更改，也就是只支持查，动态查询也就是支持增删改查四个功能。

对于静态或者动态的点查询：可以采用哈希表存储，并以O(1)时间复杂度完成增删改查；

对于静态的范围查询：可以将数据排序，对于之后的查询，使用二分查找可以在O(logn)的时间复杂度找到范围的上边界和下边界的位置；

对于动态的点查询和范围查询：使用平衡的二叉排序树。

**问题**

区间查询是特殊的范围查询，给定一个整数数组A[1...n]，现在需要查询这个数组中某个区间的属性，比如某个区间的最大最小值，区间和等。对于这类问题，依旧要分为静态查询和动态查询。

对于区间和的静态查询：我们使用**前缀和**技术，实现O(1)的查询；

对于区间最大最小值的静态查询：我们使用**Sparse Table**，实现O(1)的查询；

那么这篇文章主要针对**动态区间查询**问题，以下描述全部基于区间和问题，会附带区间最值问题的程序。

## 1.树状数组

树状数组采用了二进制编码的思想，

**求数字$i$末尾连续个0的个数k**

**例如:** 9(1001B)末尾连续个0的个数为0；10(1010B)末尾连续个0的个数为1。

**方法:**  $i \& (-i)$可以求出$2^k$，$k$为末尾连续个0的个数，例如：

$00001 \& 01111 = 00000 = 2^0$

$01000 \& 11000 = 01000 = 2^3$ 

$01010 \& 10110 = 00010= 2^1$ 

```c++
int C[N];
int n;
int lowbit(int i){
    return i & (-i);
}
void update(int i,int v){
    while(i <= n){
        C[i] += v;
        i += lowbit(i);
    }
}
int query(int i){
    int ans = 0;
    while(i > 0){
        ans += C[i];
        i -= lowbit(i);
    }
    return ans;
}
```

## 2.线段树（Segment Tree）

```c++
    vector<int> A;
    int n;
    void update(int o,int L,int R,int p,int v){
        if(L > R) return;
        if(L == R){
            A[o] = v;
            return;
        } 
        int M = L + (R - L) / 2;
        if(p <= M){
            update(2*o,L,M,p,v);
        }else{
            update(2*o+1,M+1,R,p,v);
        }
        A[o] = A[2*o] + A[2*o + 1];
    }
    void init(int o,int L,int R,vector<int>&nums){
        if(L > R) return;
        if(L == R){
            A[o] = nums[L-1];
            return;
        } 
        int M = L + (R - L) / 2;
        init(2*o,L,M,nums);
        init(2*o+1,M+1,R,nums);
        A[o] = A[2*o] + A[2*o + 1];
    }
    int query(int o,int L,int R,int ql,int qr){
        int M = L + (R-L)/2,ans = 0;
        if(ql <= L && R <= qr) return A[o];
        if(ql <= M){
            ans += query(2*o,L,M,ql,qr);
        }
        if(M < qr){
            ans += query(2*o+1,M+1,R,ql,qr);
        }
        return ans;
    }
```



## 3.离散化



[327. 区间和的个数](https://leetcode-cn.com/problems/count-of-range-sum/)

[493. 翻转对](https://leetcode-cn.com/problems/reverse-pairs/)