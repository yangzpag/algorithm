# 树形动态规划

## 1. 树的重心

对于点权值以及边权值都为1的树而言，定义如下公式：
$$
\min_{i}\{\max_{j \in children(i)}\{size(j)\}\}
$$
$size(j)$表示以$j$为根的树的节点个数，树的重心为上式的解。含义为：找到点$i$，使得$i$的子树节点个数的最大值是最小的，$i$即为树的重心。


$$
\min_{i}\{\sum_{j}distance(i,j)\}
$$
含义:找到点$i$，使得所有点到$i$的距离之和最小。



## 2. 树的直径

[1245. 树的直径](https://leetcode-cn.com/problems/tree-diameter/)

## 3. 树的最小点覆盖

二叉树的最小点覆盖（贪心）

[968. 监控二叉树](https://leetcode-cn.com/problems/binary-tree-cameras/)



## 其他

[834. 树中距离之和](https://leetcode-cn.com/problems/sum-of-distances-in-tree/)

