

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

