#include<bits/stdc++.h>
using namespace std;


class Solution {
public:
    int search(vector<int>& nums, int target) {
        int i =0;
        int j =nums.size()-1;
        int m = i+(j-i)/2;
        while(j>=i){
            bool leftSorted = isSorted(nums,i,m);
            bool rightSorted = isSorted(nums,m,j);
            if(leftSorted){
                if(target>=nums[i] && target<=nums[m]){
                    if(nums[m]==target) return m;
                    int an = binaryS(i,m,nums,target);
                    if(an!=-1){
                        return an;
                    }
                }
            }
            if(rightSorted){
                if(target>=nums[m] && target<=nums[j]){
                    if(nums[m]==target) return m;
                    int an = binaryS(m,j,nums,target);
                    if(an!=-1){
                        return an;
                    }
            }
            }
            leftSorted?i=m+1:j=m-1;
            m = i+(j-i)/2;
        }
        return -1;
    }
    
    bool isSorted(vector<int>& nums,int i,int m){
        if(nums[i]<=nums[m]){
            return true;
        }
        return false;
    }

    int binaryS(int i,int j,vector<int>& nums,int target){
        while(j>=i){
            int m = i+(j-i)/2;
            if(nums[m]==target){
                return m;
            }
            if(nums[m]>target){
                j=m-1;
            }else{
                i=m+1;
            }
        }
        return -1;
    }
};