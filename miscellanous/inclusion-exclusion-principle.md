## Inclusion - Exclusion Principle
[Link](https://cp-algorithms.com/combinatorics/inclusion-exclusion.html)

**Definition** - To compute the size of a union of multiple sets, it is necessary to **sum** the sizes of these sets **separately**, and then **subtract** the sizes of all **pairwise** intersections of the sets, then **add** back the size of the intersections of **triples** of the sets, **subtract** the size of **quadruples** of the sets, and so on, up to the intersection of all sets.

### Count number of solutions of following equations 
[Link]([Link](https://cp-algorithms.com/combinatorics/inclusion-exclusion.html#toc-tgt-10))
**Equation** - x_1 + x_2 + x_3 + x_4 + x_5 + x_6 = 20 , where each x_i is in range [0,8]

**Solution Using Inclusion Exclusion Principle** - 
* Initialize ans = 0;
* Forget all the upper bound restriction. Obtain number of ways to obtain sum = 20, using 6 variables it will be Binomial(20+6-1, 6) using [stars and bars principle](https://cp-algorithms.com/combinatorics/stars_and_bars.html) and **add** it to ans.
* Now obtain number of ways when atleast one element takes value greater than equal to 9, it will be Binomial(20-9+6-1,6) * Binomial(6,1). And **subtract** this value from ans.
* Now obtain number of ways when atleast two elements take value greater than equal to 9, it will be Binomial(20-18 + 6-1,6) * Binomial(6,2). And **add** this value from ans.
* Its not possible for four numbers to take value greater than or equal to 9.
* Return ans.


### Number of Relative Primes with n in range [1..r]
[Link](https://cp-algorithms.com/combinatorics/inclusion-exclusion.html#toc-tgt-11) | See better solution below

**Solution using inclusion-exclusion principle** - 
* Intiailize ans = r;
* Obtain all primes dividing n.
* Generate all possible masks of primes, obtain product of primes present in that mask, if number of primes in mask is even then **add** it in the ans, otherwise **subtract** it from the ans


### The number of coprime quadruples in the given array
[Link](https://cp-algorithms.com/combinatorics/inclusion-exclusion.html#toc-tgt-15)

**Solution using Inclusion - exclusion principle** - 
* Intialize ans = Binomial(n,4)
* Now loop through all numbers d from 2 to MAX_VAL:
  * if d is not a square free number continue
  * else 
    * deg(d) be numbers of different primes present in factors of d and cnt(d) be count of numbers in array divisible by d
    * if deg(d) is odd, subtract Binomial(cnt,4) from the ans
    * else add Binomial(cnt,4) in the ans


### The number of harmonic triplets in range [2,n] where n <= 1e6
[Link](https://cp-algorithms.com/combinatorics/inclusion-exclusion.html#toc-tgt-16)

**Problem Description** - 
* We need to find all triplets `(a,b,c)` where `a<b<c` and one of the following conditions holds
  * gcd(a,b) == 1 && gcd(b,c) == 1 && gcd(a,c) == 1
  * gcd(a,b) > 1 && gcd(b,c) > 1 && gcd(a,c) > 1

**Solution using Inclusion-Exclusion Principle** - 
* We will start by counting all bad triplets.
* Note that, Any non-harmonic triplet is made of a pair of coprimes and a third number that is not coprime with at least one from the pair.
* Thus, the number of bad triples that contain i is equal the number of integers from 2 to n that are coprimes with i multiplied by the number of integers that are not coprime with i. This product will produce one triplet only. But this product may be counted twice. See next point for repetitions.
* Without considering order all the bad triplets will be one of the following form - 
  1. gcd(a,b) == 1 && gcd(a,c) > 1 && gcd(b,c) > 1
  2. gcd(a,b) == 1 && gcd(a,c) == 1 && gcd(b,c) > 1 
* Coming to repetition in above types - 
  * (i) will be repeated when we take i = a and i = b
  * (ii) will be repeated when we take i = b and i = c
* So to overcome repetition we need to divide final count of bad triplets by 2.
* And in final step, we need to subtract this count from Binomial(n,3);

See code below for more details
```c++
int n;
bool good[MAXN];
int deg[MAXN], cnt[MAXN];

long long solve() {
    memset (good, 1, sizeof good);
    memset (deg, 0, sizeof deg);
    memset (cnt, 0, sizeof cnt);

    long long ans_bad = 0;
    for (int i=2; i<=n; ++i) {
        if (good[i]) {
            if (deg[i] == 0)  deg[i] = 1;
            for (int j=1; i*j<=n; ++j) {
                if (j > 1 && deg[i] == 1)
                    if (j % i == 0)
                        good[i*j] = false;
                    else
                        ++deg[i*j];
                cnt[i*j] += (n / i) * (deg[i]%2==1 ? +1 : -1);
            }
        }
        ans_bad += (cnt[i] - 1) * 1ll * (n-1 - cnt[i]);
    }

    return (n-1) * 1ll * (n-2) * (n-3) / 6 - ans_bad / 2;
}
```
