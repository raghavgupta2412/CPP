#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
               int i=0,j = nums.size()-1;
            while(j>i){
                int m = i+(j-i)/2;
                if(nums[m]<nums[m+1]){
                    i=m+1;
                }else{
                    j=m;
                }
            }
        return i;

    }
};