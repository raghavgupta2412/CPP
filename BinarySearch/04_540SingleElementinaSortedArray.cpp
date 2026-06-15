#include<bits/stdc++.h>
using namespace std;

class Solution1 {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int i =0,j = nums.size()-1;
        while(j>=i){
            if( (i+1<=j) && nums[i]==nums[i+1]){
                if( (j-1>=0) && nums[j]==nums[j-1]){
                    j-=2;
                    i+=2;
                }else{
                    return nums[j];
                }
            }else{
                return nums[i];
            }
        }
        return nums[i];   
    }
};


class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        if(nums.size()==1){
            return nums[0];
        }
        int i =0,j = nums.size()-1;
        while(j>i){
           int m = i+(j-i)/2;
           if(m%2==1){
                m--;
           }
           if(nums[m]==nums[m+1]){
                i = m+2;
           }else{
             j=m;
           }
        }
        return nums[i];
}
};