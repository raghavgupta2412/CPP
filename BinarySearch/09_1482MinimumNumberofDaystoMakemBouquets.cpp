#include<bits/stdc++.h>
using namespace std;

/* ---------------- SHORT SUMMARY (logic only) ----------------
   - Binary search on DAYS d in [min(bloomDay), max(bloomDay)].
   - sort() mat karo -> "adjacent k flowers" chahiye, order zaroori hai.
   - solve(d): array pe streak count karo; khila (<=d) -> streak++,
     streak==k -> bouquets++ & reset; nahi khila -> streak=0.
     feasible = bouquets >= m.
   - feasible -> jj=min(jj,d), j=mid-1 ; warna i=mid+1. Answer = jj (else -1).
   - Time O(n log maxDay), Space O(1).
------------------------------------------------------------- */

/*
==========================================================================
 1482. Minimum Number of Days to Make m Bouquets  --  NOTE (Intuition)
==========================================================================

 PROBLEM (1 line):
   bloomDay[i] = uss din jab i-th flower khilta hai. Humein m bouquets
   banane hain, har bouquet ke liye k ADJACENT (lagatar, bagal-bagal)
   khile hue flowers chahiye. Minimum kitne DIN wait karein?
   Agar possible hi nahi -> -1.

--------------------------------------------------------------------------
 SABSE BADA TWIST -> "ADJACENT" (875 Koko se yahi farak hai)
--------------------------------------------------------------------------
   Sirf k flowers nahi chahiye -- ORIGINAL array mein k CONSECUTIVE khile
   hue flowers chahiye. Isliye:
     -> sort() KABHI mat karo. Sort karte hi adjacency (kaun kiske bagal)
        ki info tabaah ho jaati hai. Order hi to sab kuch hai.

--------------------------------------------------------------------------
 KEY IDEA -> "Binary Search on the ANSWER (= number of DAYS)"
--------------------------------------------------------------------------
   Hum din 'd' pe binary search karte hain, index pe nahi.
   Search space:  i = min(bloomDay)   (isse pehle ek bhi flower nahi khila)
                  j = max(bloomDay)   (iske baad sab khil chuke)

 WHY binary search valid? -> MONOTONICITY
   - Jitne zyada din wait karoge, utne zyada flower khilenge -> bouquets
     sirf BADH sakte hain, ghat nahi sakte.
   - feasible ka pattern:  F F F F T T T T   <- ek hi jagah flip
                                    ^ yahi answer (sabse pehla T = min din)

--------------------------------------------------------------------------
 FEASIBILITY CHECK -> solve(d): din d pe kitne bouquets ban sakte hain?
--------------------------------------------------------------------------
   ORIGINAL array pe ek baar chalo, ek streak counter rakho:
     - flower khila (bloomDay[i] <= d)  -> consecutive++
        jaise hi consecutive == k       -> bouquets++, consecutive = 0
     - flower nahi khila (bloomDay[i] > d) -> streak TOOT gayi -> reset 0
   Aakhir mein bouquets >= m  ?  -> din d feasible hai.

   (Is code mein same kaam window se: run [i,j) ki length / k = us run ke
    bouquets. Leftover flowers integer-division se apne aap ignore.)

--------------------------------------------------------------------------
 KAUNSA BOUNDARY -> sabse CHHOTA feasible din chahiye
--------------------------------------------------------------------------
   if (feasible)  -> din yaad rakho (jj = min(jj, mid)),  aur chhota dhoondo -> j = mid-1
   else           -> aur din chahiye                                          -> i = mid+1

--------------------------------------------------------------------------
 IMPOSSIBLE CASE (-1) -> apne aap handle
--------------------------------------------------------------------------
   Agar m*k flowers hi nahi hain (ya adjacency ki wajah se kabhi m bouquets
   nahi bante), to solve() kabhi m tak nahi pahunchega -> jj = INT_MAX reh
   jayega -> -1 return. Alag se guard ki zaroorat nahi.

--------------------------------------------------------------------------
 COMPLEXITY
--------------------------------------------------------------------------
   Time : O(n * log(maxBloomDay))   (har binary-search step pe solve O(n))
   Space: O(1)

--------------------------------------------------------------------------
 DRY RUN: bloomDay = [7,7,7,7,12,7,7], m = 2, k = 3   -> answer 12
   d=7  -> khile: [0,1,2,3] & [5,6]; bouquets = 4/3 + 2/3 = 1 < 2  (no)
   d=12 -> sab khile: ek run length 7; bouquets = 7/3 = 2 >= 2     (yes)
   smallest feasible din = 12
==========================================================================
*/

class Solution {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        int i = *min_element(bloomDay.begin(),bloomDay.end());
        int j = *max_element(bloomDay.begin(),bloomDay.end());
        int jj=INT_MAX;
        while(j>=i){
            int mid = i+(j-i)/2;
            bool ans = solve(mid,bloomDay,m,k);
            if(ans){
                jj=min(jj,mid);
                j=mid-1;
            }else{
                i=mid+1;
            }
        }
        return jj==INT_MAX ? -1:jj;
    }
    bool solve(int val,vector<int>& a,int m,int k){
        int c=0;
        int i=0,j=0;
        while(j<=a.size()){
            if(j<a.size() && val>=a[j]){
                j++;
            }else{
                int l=(j-i)/k;
                c+=l;
                j++;
                i=j;
            }
        }
        cout<<val<<" "<<c<<endl;
        if(c>=m){
            return true;
        }
        return false;
    }
};