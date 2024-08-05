#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <ext/pb_ds/assoc_container.hpp>

#include <cmath>
#define pii pair<int,int>
#define pb push_back
#define ppii pair<int, pair<int,int>>
#define pld pair<long long,double>
#define pibb pair<int,<bool,bool>>
#define yes "YES"
#define no "NO"
#define ll long long
#define MOD 1000000007
#define MOD2 998244353
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

void solve(){
   int n,m,k;
   cin>>n>>m>>k;
   vector<int> sat(n);
   for (int i = 0; i < n; i++) cin>>sat[i];
   vector<vector<pii>> nodeMap(n);
   for (int i = 0; i < k; i++){
      int a,b,c;
      cin>>a>>b>>c;
      --a;--b;
      nodeMap[a].emplace_back(b,c);
   }
   vector<vector<ll>> dp (1<<n, vector<ll> (n,-1));
   auto dfs = [&] (auto self, int bitmask, int lastDish) -> ll {
      if (__builtin_popcount(bitmask)==m){
         return 0;
      }
      if (lastDish!=-1 && dp[bitmask][lastDish]!=-1) return dp[bitmask][lastDish];
      if (lastDish==-1){
         ll res = 0;
         for (int i = 0; i < n; i++){
            res=max(res,sat[i]+self(self, 1<<i, i));
         }
         return res;
      }
      ll res = 0;
      for (auto [nextDish, weight]: nodeMap[lastDish]){
         if ((bitmask&(1<<nextDish))==0){
            res=max(res,weight+sat[nextDish]+self(self,bitmask|(1<<nextDish),nextDish));
         }
      }
      for (int i = 0; i < n; i++){
         if ((bitmask&(1<<i))==0){
            res=max(res,sat[i]+self(self,bitmask|(1<<i),i));
         }
      }
      return dp[bitmask][lastDish]=res;
   };
   cout<<dfs(dfs,0,-1)<<endl;
}
int main(){
   int t=1;
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   //cin>>t;
   while (t--){
      solve();
   }
}