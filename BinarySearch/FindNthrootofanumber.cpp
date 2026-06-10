#include<bits/stdc++.h>
using namespace std;

long long power(int x , int n,int m){
    long long ans=1;
    while(n>0){
        if(ans>m){
            return m+1;
        }
        ans=ans*x;
        n--;
    }
    return ans;
}

class Solution {
  public:
    int nthRoot(int n, int m) {
        int i=0,j=m;
        while(i<=j){
            int mid = i+(j-i)/2;
            long long val = power(mid,n,m);
            if(val==m){
                return mid;
            }else if(val>m){
                j=mid-1;
            }else{
                i=mid+1;
            }
        }
        return -1;
        
    }
};