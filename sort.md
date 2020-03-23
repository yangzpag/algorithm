# 排序（Sort）

## 1.快速排序

```c++
    void quicksort(vector<int>& a,int l,int r){
        if(l < r){
            
            int x = a[l];
            int i = l,j = r;
            while(i <= j){
                while(a[j] > x){
                    j--;
                }
                while(a[i] < x){
                    i++;
                }
                if(i <= j){
                    swap(a[i],a[j]);
                    i++;
                    j--;
                }
            }
            quicksort(a,l,j);
            quicksort(a,i,r);
        }
    }
```

**快速选择**

```c++
void quickselect(vector<int>& arr,int l,int r,int k){
        if(l == r) return;
        int pivot = arr[l];
        int i = l, j = r;
        while(i < j){
            while(i < j && pivot < arr[j]) j--;
            swap(arr[i],arr[j]);
            while(i < j && pivot >= arr[i]) i++;
            swap(arr[i],arr[j]);
        }
        if(i == k) return;
        if(i > k) quickselect(arr,l,i-1,k);
        if(i < k) quickselect(arr,i+1,r,k);
}
```

