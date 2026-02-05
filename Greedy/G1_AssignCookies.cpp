#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(),g.end());
        sort(s.begin(),s.end());
        int n = g.size();
        int m = s.size();
        int i=0,j=0;
        int res=0;
        while(i<n && j<m){
            if(s[j]>=g[i]){
                i++;
            }
            j++;
        }
        return i;
    }
};


int main (){
    Solution sol;
    vector<int> g={1,2,3};
    vector<int> s={1,1};
    cout<<sol.findContentChildren(g,s)<<endl;
}