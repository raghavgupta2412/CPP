#include<bits/stdc++.h>
using namespace std;

/*
==========================================================================
 875. Koko Eating Bananas  --  NOTE (Intuition + Solution)
==========================================================================

 PROBLEM (1 line):
   piles[] banana ki dher hain, Koko ko h ghante mein sab khaane hain.
   Har ghante woh ek speed 'k' (banana/hour) se ek pile khaati hai.
   Minimum integer speed 'k' nikalo jisse woh h ghante ke andar sab khaa le.

--------------------------------------------------------------------------
 KEY IDEA -> "Binary Search on the ANSWER"
--------------------------------------------------------------------------
   Yahan hum index pe binary search nahi kar rahe -- hum SPEED 'k' pe
   binary search kar rahe hain. Speed ki ek range hai, aur uss range mein
   se sabse chhoti valid speed dhoondhni hai.

 WHY binary search valid hai? -> MONOTONICITY (sabse important baat)
   - Jaise-jaise 'k' badhti hai, total ghante GHATTE jaate hain (ya same).
   - Matlab ek point ke baad har speed "kaam karti hai" (feasible),
     aur uss point se pehle har speed "kaam nahi karti" (too slow).
   - feasible ka pattern: F F F F T T T T   <- ek hi jagah flip hota hai
                                    ^
                                    yahi humara answer (sabse pehla T)
   - Is "ek baar flip" property ki wajah se hi binary search lag sakta hai,
     warna har k try karna padta (O(n * maxPile) -> TLE).

--------------------------------------------------------------------------
 SEARCH SPACE  [i, j]
--------------------------------------------------------------------------
   i = 1            -> sabse slow possible speed (1 banana/hour).
                       (DHYAAN: answer min(piles) se bhi chhota ho sakta hai,
                        isliye i ko min pile mat banao -- yeh ek galti thi.)
   j = max(piles)   -> isse tez khaane ka koi fayda nahi. Ek ghante mein
                       Koko sirf EK pile khaati hai, to ek pile poora khaane
                       ke liye max(piles) se zyada speed bekaar hai.

--------------------------------------------------------------------------
 FEASIBILITY CHECK  -> solve(k): k speed pe kitne ghante lagenge?
--------------------------------------------------------------------------
   Ek pile p ke liye ghante = ceil(p / k).
   Integer ceil ka trick: (p + k - 1) / k
     (kyunki C++ mein p/k FLOOR deta hai: 7/4 = 1 galat, chahiye 2)
   Sab piles ke ghante jodo -> agar total <= h to speed k feasible hai.

   OVERFLOW WARNING: total ghante ~ 1e4 piles * 1e9 = 1e13 tak ja sakta hai.
   Isliye accumulator aur return type 'long long' hone chahiye, int nahi.

--------------------------------------------------------------------------
 KAUNSA BOUNDARY RAKHNA HAI? -> humein sabse CHHOTI feasible k chahiye
--------------------------------------------------------------------------
   if (ghante <= h)  -> yeh k kaam karti hai -> answer yaad rakho (jj)
                        aur aur chhoti dhoondho -> j = m - 1
   else (ghante > h) -> too slow -> speed badhao -> i = m + 1

   ZAROORI: feasible hone par 'j = m - 1' karo (jump), 'j--' nahi.
   Agar bahut saari speeds bilkul barabar h ghante leti hain (ek "plateau"),
   to j-- ek-ek karke chalega aur ~1e9 iterations -> TLE. j=m-1 se log(n)
   rehta hai.

--------------------------------------------------------------------------
 COMPLEXITY
--------------------------------------------------------------------------
   Time : O(n * log(maxPile))   n = piles.size()
          (binary search ke har step pe solve() poore array pe chalta hai)
   Space: O(1)

--------------------------------------------------------------------------
 DRY RUN: piles = [3,6,7,11], h = 8   -> answer 4
   k=6 -> 1+1+2+2 = 6 <= 8  (feasible, chhoti try karo)
   k=3 -> 1+2+3+4 = 10 > 8  (too slow, tez karo)
   k=4 -> 1+2+2+3 = 8  <= 8 (feasible) -> minimum = 4
==========================================================================
*/

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int i = 1;
        int j = *max_element(piles.begin(),piles.end());
        if(piles.size()==h){
            return j;
        }
        long long  jj=INT_MAX;
        while(j>=i){
            long long m = i+(j-i)/2;
            long long ans=solve(m,piles);
            if(ans<=h){
                jj=min(jj,m);
                j=m-1;
            }
            else{
                i=m+1;   
            }
        }
        return jj;
    }

    long long solve(long long m,vector<int>&piles){
        long long ans=0;
        for(auto k:piles){
            ans+=(k+m-1)/m;
        }
        return ans;
    }
};