## Optimal schedule of jobs given their deadlines and durations
[Link](https://cp-algorithms.com/schedules/schedule-with-completion-duration.html)

**Problem Descriptions** - Given a list of jobs with their deadline and duration. Find maximum number of jobs that can be executed. We can only execute one job at a time. Also, we execute partial job that is job can be started and then taken out in middle and once again restarted. But it will only be counted in ans if we can complete it.

**Solution Description** - 
* Sort jobs according to their deadline in ascending order, that is deadline[i-1] < deadline[i]
* Maintain a set s of pair<remaining_duration, job>, and an completed vector
* Loop from i = n-1 to i=0 - 
  * Take time interval t = deadline[i] - deadline[i-1];
  * while(t && !s.empty())
    * if t >= s.begin()->first : then t -= s.begin()->first; completed.push_back(s.begin()->second); (s.erase(s.begin());
    * else p = *s.begin(); p.first -= t; s.erase(s.begin()); s.insert(p); t = 0; 
* Return completed vector.

```c++
struct Job {
    int deadline, duration, idx;

    bool operator<(Job o) const {
        return deadline < o.deadline;
    }
};

vector<int> compute_schedule(vector<Job> jobs) {
    sort(jobs.begin(), jobs.end());

    set<pair<int,int>> s;
    vector<int> completed;
    for (int i = jobs.size()-1; i >= 0; i--) {
        int t = jobs[i].deadline - (i ? jobs[i-1].deadline : 0);
        s.insert(make_pair(jobs[i].duration, jobs[i].idx));
        while (t && !s.empty()) {
            auto it = s.begin();
            if (it->first <= t) {
                t -= it->first;
                completed.push_back(it->second);
            } else {
                s.insert(make_pair(it->first - t, it->second));
                t = 0;
            }
            s.erase(it);
        }
    }
    return completed;
}
```
