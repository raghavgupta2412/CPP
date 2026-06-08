#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int mySqrt  (int x) {
        int i=0, j= x;
        while(j>=i){
            long long  m = i+(j-i)/2;
            if((m)*(m)==x){
                return m;
            }else if((m)*(m)>x){
                j=m-1;
            }else{
                i=m+1;
            }
        }
        return j;
    }
};