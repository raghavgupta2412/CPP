#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int i = 1;
        int j = *max_element(nums.begin(),nums.end());
        int jj = INT_MAX;
        while(j>=i){
            int mid =i+(j-i)/2;
            int ans=solve(mid,nums);
            if(ans<=threshold){
                jj=min(jj,mid);
                j=mid-1;
            }else{
                i=mid+1;
            }
        }
        return jj;
    }
    int solve(int mid,vector<int>& a){
        int ans=0;
        for(auto x:a){
            ans+=(x+mid-1)/mid;
        }
        return ans;
    }
};