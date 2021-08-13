/*
* Problem used in - https://www.interviewbit.com/problems/n3-repeat-number/
* Article Link - https://www.geeksforgeeks.org/majority-element/
* By Majority we mean count should be **greater than** n/2
*/
int getMajorityElementCandidate(vector<int>&v)
{
    int n = v.size();
    int count = 1,index = 0;
    for(int i=1;i<n;i++)
    {
        if(v[i] == v[index])count++;
        else 
        count--;
        if(count == 0){index = i,count=1;}
    }
    
    return v[index];
}
