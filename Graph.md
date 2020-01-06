# 图论（Graph）

## 1. 并查集

### 1.1 几种并查集的写法

对于节点编号为有限整数的情况，使用一维数组就可以实现并查集

```c
vector<int> f(n);

void init(int n){
    for(int i=0;i<n;i++){
        f[i] = i;
    }
}
void find(int x){
    return f[x] == x?x:f[x] = find(x);
}
void merge(int x,int y){
    int px = find(x);
    int py = finx(y);
    if(px != py){
        f[py] = px;
    }
}
```

对于编号不是有限整数的情况，可以使用哈希映射实现并查集，其他部分基本一致

```c++
unordered_map<string,string> f;
```



[685. 冗余连接 II](https://leetcode-cn.com/problems/redundant-connection-ii/)





## 二分图



匈牙利算法

