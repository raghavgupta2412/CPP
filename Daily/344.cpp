// 344. Reverse String
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    void reverseString(vector<char>& s) {
        for(int i=0;i<s.size()/2;i++){
            char k= s[i];
            s[i]=s[s.size()-i-1];
            s[s.size()-i-1]=k;
            // swap(s[i],s[s.size()-i-1]);
        }
    }
};