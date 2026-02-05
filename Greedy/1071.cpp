#include <bits/stdc++.h>
using namespace std;
string gcdOfStrings(string str1, string str2) {
     string max="";
        if(str1.size()>str2.size()){
            string s="";
            for(int i =1;i<=str2.size();i++){
                s = str2.substr(0,i);
                int k =str2.size()/s.size();
                string ans="";
                for(int j=0;j<k;j++){
                    ans+=s;
                }
                if(ans==str2){
                    string ans="";
                    int k= str1.size()/s.size();
                    for(int i=0;i<k;i++){
                        ans+=s;
                    }
                    if(ans==str1){
                        max=max.size()<s.size()?s:max;
                    }
                }
            }
            return max;
        }else{
            string s="";
            for(int i =1;i<=str1.size();i++){
                s = str1.substr(0,i);
                int k =str1.size()/s.size();
                string ans="";
                for(int j=0;j<k;j++){
                    ans+=s;
                }
                if(ans==str1){
                    string ans="";
                    int k= str2.size()/s.size();
                    for(int i=0;i<k;i++){
                        ans+=s;
                    }
                    if(ans==str2){
                        max=max.size()<s.size()?s:max;
                    }
                }
            }
            return max;
        }     
    }

    int main(){
        string str1="ABABABAB";
        string str2="ABAB";
        cout<<gcdOfStrings(str1,str2)<<endl;
    return 0;
}