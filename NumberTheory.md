#  数论（Number Theory）

## 1. 素数

### 1.1 朴素方法

时间复杂度：$O(n \sqrt{n})$

```c++
int cnt = 0;
int prime[N];
void getPrime(int n){
    for(int i=1;i <= n;i++){
        if(isPrime(i)){
            prime[cnt++] = i;
        }
    }
}
bool isPrime(int n){
    if(n == 1) return false;
    for(int i = 2;i*i <= n;i++){
        if(n % i == 0) return false;
    }
    return true;
}
```

### 1.2 埃氏筛法

时间复杂度：$O(nloglogn)$

```c++
vector<int> getPrime(int n){  //不包含n
	vector<bool> not_prime(n);
	vector<int> prime;
	not_prime[0] = not_prime[1] = true;
    for(int i=2;i< n;i++){
        if(!not_prime[i]){
            prime.push_back(i);
            for(int j = i + i;j < n;j += i){
                not_prime[j] = true;
            }
        }
    }
    return prime;
}
```



### 1.3 欧几里得筛（线性筛）

```c++
int cnt = 0;
void get_prime(int n)
{
    for(int i=2;i<=n;i++)
    {
        if(!vis[i]){prim[++cnt]=i;}
        for(int j=1;j<=cnt&&prim[j]*i<=n;j++)
        {
            vis[prim[j]*i]=1;
            if(i%prim[j]==0)break; 
        }
    }
 }
```


## 快速幂
```cpp
int quickpow(int a, int b, int c) //a^b mod c
{
     int res = 1;
     a %= c;
     while (b)
     {
         if (b % 2 ==  1)
             res = (res * a) % c;
         a = (a * a) % c;
         b /= 2;
     }
     return res;
}
```
## 费马小定理

$$
a^{p-1} = 1 \pmod{p},p\not|  a
$$

考虑 p - 1 个整数 a ,2a , 3a ,...,(p-1)a，这些整数都不可能被p整除。并且这些数不会模p同余，可以得到：
$$
a \cdot 2a \cdot 3a ... (p-1)a = 1 \cdot 2 \cdot \cdot \cdot (p-1) \pmod{p}
$$

## 欧拉$\phi$函数

$$
\phi\left( p \right) = p - 1
$$
$$
\phi\left( p^k \right) = p^k - p^{k-1}
$$
$$
\phi(m_1\cdot m_2) = \phi(m_1)\phi(m_2),gcd(m_1,m_2)=1
$$
$$
a^{\phi(m)} = 1 (mod  m),gcd(a,m) = 1
$$
```cpp
void getphi(int N){
    phi[1]=1;//φ(1)=1
    for(int i=2;i<=N;i++){//从2枚举到N
        if(!mark[i]){//如果是素数
            prime[++tot]=i;//那么进素数数组，指针加1
            phi[i]=i-1;//根据性质1所得
        }
        for(int j=1;j<=tot;j++){//从现求出素数枚举
            if(i*prime[j]>N) break;//如果超出了所求范围就没有意义了
            mark[i*prime[j]]=1;//标记i*prime[j]不是素数
            if(i%prime[j]==0){//应用性质2
                phi[i*prime[j]]=phi[i]*prime[j];break;
            }
            else phi[i*prime[j]]=phi[i]*phi[prime[j]];//应用性质3
        }
    }
}
```


## $\mu$函数
```cpp
void get_mu(int n)
{
    mu[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!vis[i]){prim[++cnt]=i;mu[i]=-1;}
        for(int j=1;j<=cnt&&prim[j]*i<=n;j++)
        {
            vis[prim[j]*i]=1;
            if(i%prim[j]==0)break;
            else mu[i*prim[j]]=-mu[i];
        }
    }
 }
```
## 拓展欧几里得算法
《算法导论》定理31.2：如果a和b是不都为0的任意整数，则gcd(a,b)是a与b的线性组合集合$\{ax+by|x,y \in \mathbb{Z}\}$中的最小正元素。
$$
a\cdot x + b \cdot y = gcd(a,b)
$$
拓展欧几里得算法正确性证明：
$$
d' = \gcd(b,a\bmod b)
$$

$$
d' = bx' + (a\bmod b)y' =  bx' + (a - \lfloor \frac{a}{b} \rfloor b)y' = ay' + b(x'- \lfloor \frac{a}{b} \rfloor y')
$$

$$
d = ax + by
$$

$$
x = y',y = x'- \lfloor \frac{a}{b} \rfloor y'
$$

```c++
long long exgcd(long long a,long long b,long long &x,long long &y)
{
    if (b==0) { x=1,y=0; return a; }
    long long d=exgcd(b,a%b,x,y);
    long long tmp=x;
    x=y;
    y=tmp-a/b*y;
    return d;
}
```

## 中国剩余定理

求解$x \equiv a_i \pmod{m_i}$,i = 1,2,....n

```math

M = m_1 \cdot m_2 \cdot m_3 .... m_n

M_i = \frac{M}{m_i}

M_i^{-1} M_i \equiv 1 \pmod{m_i}

x \equiv (a_1M_1M_1^{-1}+....+a_nM_nM_n^{-1}) \pmod{M}


```

## 小步大步算法(bsgs算法)

求解 $a^x = y \left( mod p\right)$,p表示素数。
朴素算法让y从0取到p-1，可以使用meet-in-the-middle思想将算法复杂度降到($O(\sqrt{p})$)

$$ s = \lceil \sqrt{p-1} \rceil $$

$$ x = t \cdot s - r (t,r < s) $$

$$ a^{t \cdot s - r} \equiv y\pmod{s}$$

$$ a^{t \cdot s} \equiv y\cdot a^{r}\pmod{s}$$





```cpp
#include <iostream>
#include <cstdio>
#include <map>
 
using namespace std;
typedef long long LL;
 
 
LL quick_mod(LL a, LL b, LL c)//费马小定理+快速幂求逆元  
{
	LL ans = 1;
	while (b)
	{
		if (b % 2 == 1)
			ans = (ans*a) % c;
		b /= 2;
		a = (a*a) % c;
	}
	return ans;
}
 
int bsgs(int a, int b, int n) 
{
	int m, v, e = 1, i;
	m = (int)sqrt(n + 0.5);
	v = quick_mod(quick_mod(a, m, n),n-2, n);  //(a^(-m))
	map<int, int> x;
	x[1] = 0;
	for (int i = 1; i < m; i++) {
		e = e*a%n;
		if (!x.count(e)) x[e] = i;
	}
	for (i = 0; i < m; i++) {
		if (x.count(b)) return i*m + x[b];
		b = b*v%n;
	}
	return -1;
}
```