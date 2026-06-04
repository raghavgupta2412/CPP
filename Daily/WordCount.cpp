#include<bits/stdc++.h>
using namespace std;

int count(string input){
        int count = 0;
    bool isthisstarting = true;
 
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] != ' ' &&
            input[i] != '\n' &&
            input[i] != '\t' &&
            isthisstarting)
        {
            count++;
            isthisstarting = false;
        }
 
        if (input[i] == ' ' ||
        
            input[i] == '\n' ||
            input[i] == '\t')
        {
            isthisstarting = true;
        }
    }
 
    return count;
}


int main(){
    string s= "bogs\tl";
    cout<<count(s)<<endl;
}


