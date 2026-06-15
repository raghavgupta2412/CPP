#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int ans =INT_MAX;
        int i = 0;
        int j = nums.size() - 1;
        while (i < j) {
            int m = i + (j - i) / 2;
            if(nums[m]>nums[j]){
                i=m+1;
            }else{
                j=m;
            }
        }
        return nums[i];        
    }

};