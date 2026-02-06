#include <bits/stdc++.h>
using namespace std;
string reverseStr(string s, int k) {
        if(k>=s.size()){
            for(int i=0;i<s.size()/2;i++){
                 swap(s[i],s[s.size()-i-1]);
            }
            return s;
        }
        for(int i=0;i<s.size();){
            int n=i/k;       
                if((s.size()-1-n*k)<k){
                    for(int h=i;h<(s.size()-i)/2+i;h++){
                        swap(s[h], s[s.size()-1-h+i]);
                    }
                    return s;
                }
            for(int j=i;j<((k/2)+i) && (j<s.size()) ;j++){
                cout<<j<<" "<<(k-1)+i-j+i<<endl;
                if((k-1)+i-j+i>=s.size()) break;
                 swap(s[j],s[(k-1)+i-j+i]);
            }
            i+=k-1+k+1;
        }
        return s;
    }

    int main(){
        string s="lgsqddebemjanqcqnfkjmi";
        cout<<s.size()<<endl;
        int k=39;
        // cout<<reverseStr(s,k)<<endl;
    }