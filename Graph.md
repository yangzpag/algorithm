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
    int find(int x){
        return f[x] == x?x:f[x] = find(f[x]);
    }
    void merge(int x,int y){
        int px = find(x);
        int py = find(y);
        if(px != py){
            f[py] = px;
        }
    }
```

对于编号不是有限整数的情况，可以使用哈希映射实现并查集，其他部分基本一致

```c++
    unordered_map<string,string> f;

    string find(string x){
        if(!f.count(x))f[x] = x;
        return f[x] == x?x:f[x] = find(f[x]);
    }
    void merge(string x,string y){
        string px = find(x);
        string py = find(y);
        if(px != py){
            f[py] = px;
        }
    }
```

同理给出二维的情况

```c++
	vector<vector<Point>> f; 
	void init(int m,int n){
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                f[i][j] = Point(i,j);
            }
        }
    }
    Point find(Point& p){
        return f[p.first][p.second] == p ? p : 
        		f[p.first][p.second] = find(f[p.first][p.second]); 
    }

    void merge(Point& p1,Point& p2){
        Point pp1 = find(p1);
        Point pp2 = find(p2);
        if(pp1 != pp2){
            f[pp1.first][pp1.second] = pp2;
        }
    }
```



### 1.2 模板题

[261. 以图判树](https://leetcode-cn.com/problems/graph-valid-tree/)

[323. 无向图中连通分量的数目](https://leetcode-cn.com/problems/number-of-connected-components-in-an-undirected-graph/)

[737. 句子相似性 II](https://leetcode-cn.com/problems/sentence-similarity-ii/)

### 1.3 比较有技巧性地题目

[952. 按公因数计算最大组件大小](https://leetcode-cn.com/problems/largest-component-size-by-common-factor/)

[399. 除法求值](https://leetcode-cn.com/problems/evaluate-division/)

[685. 冗余连接 II](https://leetcode-cn.com/problems/redundant-connection-ii/)



### 1.4 最小生成树

使用并查集的最小生成树算法称克鲁斯卡尔(Kruskal)算法

```c++
struct Edge{
    int u,v;
    int c;
};
int Kruskal(vector<Edge> edges,int n){ //点的编号从0开始
     sort(edges.begin(),edges.end(),[](Edge a,Edge b){return a.c < b.c;});
     init(n);                         //并查集初始化
     int ans = 0;
     for(Edge e:edges){
         if(!same(e.u,e.v)){          //判断是否在同一个集合
            ans += e.c;
            merge(e.u,e.v);           //并查集合并
         }
     }
     return ans;
}
```

## 二分图



匈牙利算法

