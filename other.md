## 众数

绝大多数：超过N/2的数

[1150. 检查一个数是否在数组中占绝大多数](https://leetcode-cn.com/problems/check-if-a-number-is-majority-element-in-a-sorted-array/)

```c++
    bool isMajorityElement(vector<int>& nums, int target) {
        return nums[(nums.size() - 1) /2] == target;
    }
```

