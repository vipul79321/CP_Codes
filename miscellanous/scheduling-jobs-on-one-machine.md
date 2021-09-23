## Scheduling Jobs on one machine with given penalty function for each job
[Link](https://cp-algorithms.com/schedules/schedule_one_machine.html)

**Permutation Method** - In this method, we take one permutation say p, and assume its cost(penalty in our case) and then we swap two consecutive elements say i and i+1 and compute difference between current cost and previous cost and obtain a condition on sorting.

**Problem Description** - Given n job with their penalty function f_i(wait_time_i), find optimal permutation of jobs such that total penalty is minimized.

**Solution Approach** - 
* It can be solved using **permutation method** if and only if penalty function is one of following type - 
  * f_i(t_i) = c_i * wait_time_i; there is no constant as we can simply add up constant part in our final penalty
  * f_i(t_i) = c_i * exp(x * t_i);
  * f_i(t_i) = F(t_i), i.e. penalty function is same for all jobs and that function is **Monotone increasing function** 

**Solution When penalty function is linear**
* Consider a permutation p and let it cost be C
* Now consider two index i and i + 1, swap jobs at them
* new_cost will be `C + summation(t_j for all j from 0 to i-1) * c_i+1  + summation(t_j for all j from 0 to i) * c_i - summation(t_j for all j from 0 to i-1) * c_i  - summation(t_j for all j from 0 to i) * c_i+1`
* On simplifying `new_cost = C  + c_i * t_i+1 - c_i+1 * t_i`; 
* So, difference between previous cost and new_cost is `c_i * t_i+1 - c_i+1 * t_i`
* In an optimal solution this difference should be positive, ie. `c_i * t_i+1 - c_i+1 * t_i >= 0`
* On further simplifying `c_i/t_i >= c_i+1/t_i+1`
* So our solution will be sort all job in non-ascending order on the basis of `c_i/t_i`



