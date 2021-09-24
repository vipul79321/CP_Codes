## Scheduling jobs on two machines
[Link](https://cp-algorithms.com/schedules/schedule_two_machines.html)

**Problem Description** - 
* Given is an array of jobs and two machines. 
* For each job i, it take a_i time on first and b_i time on second machine.
* A job can only be processed on second after it has been processed on first machine
* Each machine can execute one job at a time.
* We cant execute partial jobs
* Our objective is to **find optimal order of jobs execution such that final processing time is minimized**

**Solution Description** - 
* Sort jobs according to min(a_i,b_i) value.
* Now make two vectors X and Y.
* Iterate through all the jobs and if a_i < b_i then push that job in X otherwise push that job in Y
* Reverse(Y) and X.append(Y)
* Now X will contain order of execution. Also note that, it is always optimal to process a job in second machine right after it comes out of first machine.

See code for more details -
```c++
struct Job {
    int a, b, idx;

    bool operator<(Job o) const {
        return min(a, b) < min(o.a, o.b);
    }
};

vector<Job> johnsons_rule(vector<Job> jobs) {
    sort(jobs.begin(), jobs.end());
    vector<Job> X, Y;
    for (Job j : jobs) {
        if (j.a < j.b)
            X.push_back(j);
        else
            Y.push_back(j);
    }
    reverse(Y.begin(),Y.end());
    X.insert(X.end(), Y.begin(),Y.end());
    return a;
}

pair<int, int> finish_times(vector<Job>& jobs) {
    int t1 = 0, t2 = 0;
    
    jobs = johnsons_rule(jobs);
    
    for (Job j : jobs) {
        t1 += j.a;
        t2 = max(t2, t1) + j.b;
    }
    return make_pair(t1, t2);
}
```
