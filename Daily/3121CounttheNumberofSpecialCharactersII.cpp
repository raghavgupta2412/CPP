#include <bits/stdc++.h>
using namespace std;

    int numberOfSpecialChars(string word) {
          map<char,int>small;
        vector<pair<char,pair<int,int>>>cap;
        int k=0;
        for(int i =0;i<word.size();i++){
            if(islower(word[i])){
                small[word[i]]++;
            }
            if(isupper(word[i]) && !any_of(cap.begin(), cap.end(),
                       [&](const auto& p){ return p.first == word[i]; })){
                cap.push_back({word[i],{1,i}});
            }
        }
        for (auto& [ch, pr] : cap) {
            auto& [x, y] = pr;
            if(small.find((char)tolower(ch))!=small.end()){
                if(word.find((char)tolower(ch),y) == string::npos){
                    cout<<(char)tolower(ch);
                    k++;
                }
            }
        }
        return k;
}

// Optimized: O(n) time, O(1) space.
// A character is "special" iff the LAST lowercase occurrence comes
// strictly BEFORE the FIRST uppercase occurrence.
int numberOfSpecialCharsOptimized(string word) {
    int lastLower[26], firstUpper[26];
    fill(begin(lastLower), end(lastLower), -1);
    fill(begin(firstUpper), end(firstUpper), INT_MAX);

    for (int i = 0; i < (int)word.size(); i++) {
        char c = word[i];
        if (islower(c)) {
            lastLower[c - 'a'] = i;          // keep overwriting -> last index
        } else {                              // isupper
            int idx = c - 'A';
            if (firstUpper[idx] == INT_MAX)  // record only the first
                firstUpper[idx] = i;
        }
    }

    int k = 0;
    for (int i = 0; i < 26; i++) {
        if (lastLower[i] != -1 && firstUpper[i] != INT_MAX
            && lastLower[i] < firstUpper[i]) {
            k++;
        }
    }
    return k;
}

int main(){
    string word="aaAbcBC";
    cout<<numberOfSpecialChars(word)<<endl;
    cout<<numberOfSpecialCharsOptimized(word)<<endl;
}

    
