// 448. Find All Numbers Disappeared in an Array
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        // unordered_map<int,int>m;
        // vector<int> ans;
        // for(int i=1;i<=nums.size();i++){
        //     m[i]=0;
        // }
        // for(int i:nums){
        //     m[i]++;
        // }
        // for(auto it=m.begin();it!=m.end();it++){
        //     if(it->second==0){
        //         ans.push_back(it->first);
        //     }
        // }
        // return ans;

        vector<int>k(nums.size()+1);
        for(int i:nums){
            k[i]=1;
        }
        vector<int>ans;
        for(int i =1;i<=nums.size();i++){
            if(k[i]==0){
                ans.push_back(i);
            }
        }
        return ans;
        
    }
};