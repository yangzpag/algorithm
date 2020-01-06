

## 迭代器(Iterator)

```c++
#include<iterator>
void advance (InputIterator& it, Distance n);

typename iterator_traits<InputIterator>::difference_type
    distance (InputIterator first, InputIterator last);

BidirectionalIterator prev (BidirectionalIterator it,
       typename iterator_traits<BidirectionalIterator>::difference_type n = 1);

ForwardIterator next (ForwardIterator it,
       typename iterator_traits<ForwardIterator>::difference_type n = 1);
```





## multiset



[295. 数据流的中位数](https://leetcode-cn.com/problems/find-median-from-data-stream/)

[480. 滑动窗口中位数](https://leetcode-cn.com/problems/sliding-window-median/)



## deque

hud-3530-Subsequence

[862. 和至少为 K 的最短子数组](https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/)

```c++
    int shortestSubarray(vector<int>& A, int K) {
        int n = A.size();
        int ans = INT_MAX;
        deque<int> dq;
        vector<int> presum(n+1,0);
        for(int i=1;i<=n;i++){
            presum[i] += presum[i-1] + A[i-1];
        }
        for(int i=0;i<=n;i++){
            while(!dq.empty() && presum[dq.back()] >= presum[i]){
                dq.pop_back();
            }
            while(!dq.empty() && presum[i] - presum[dq.front()] >= K){
                ans = min(ans,i - dq.front());
                dq.pop_front();
            }
            dq.push_back(i);
        }
        return ans == INT_MAX? -1 : ans;
    }
```

