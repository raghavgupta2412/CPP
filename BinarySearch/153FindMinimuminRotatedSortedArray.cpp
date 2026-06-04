#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int m= INT_MIN;
        return search(nums,m);

    }
    int search(vector<int>& nums, int target) {
        int ans =INT_MAX;
        int i = 0;
        int j = nums.size() - 1;
        while (i <= j) {
            int m = i + (j - i) / 2;
            if (nums[m] == target) {
                return m;                       // m is the index we return
            }
            ans = min(ans,nums[m]);
            if (nums[i] <= nums[m]) {           // left half [i..m] is sorted
                if (target >= nums[i] && target < nums[m]) {
                    j = m - 1;                  // target lies in the sorted left
                } else {
                    i = m + 1;                  // otherwise look right
                }
            } else {                            // right half [m..j] is sorted
                if (target > nums[m] && target <= nums[j]) {
                    i = m + 1;                  // target lies in the sorted right
                } else {
                    j = m - 1;                  // otherwise look left
                }
            }
        }
        return ans;
    }
};