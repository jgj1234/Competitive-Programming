#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <iomanip>
#include <set>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <ext/pb_ds/assoc_container.hpp>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
#include <cmath>
#define pii pair<int,int>
#define pi 3.14159265358979323846
#define pb push_back
#define ppii pair<int, pair<int,int>>
#define pld pair<long long,double>
#define pibb pair<int,<bool,bool>>
#define yes "YES"
#define no "NO"
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

void solve(){
    ll s,x;
    cin>>s>>x;
    int lg = 64 - __builtin_clzll(max(s,x));
    vector<vector<ll>> dp (lg, vector<ll> (2, -1));
    auto dfs = [&] (auto self, int i, bool carry) -> ll{
        if (i==lg){
            if (carry==0) return 1;
            return 0;
        }
        if (dp[i][carry]!=-1) return dp[i][carry];
        bool xrBit = bool(x&(1LL<<i));
        bool sBit = bool(s&(1LL<<i));
        ll res = 0;
        for (int b1 = 0; b1 < 2; b1++){
            for (int b2 = 0; b2 < 2; b2++){
                if ((xrBit&& b1==b2) || (!xrBit && b1!=b2)) continue;
                if ((sBit&&(carry+b1+b2)%2==0)||(!sBit && (carry+b1+b2)%2==1)) continue;
                bool newCarry = (carry && (b1||b2))|| (!carry && b1 && b2);
                res+=self(self,i+1,newCarry);
            }
        }
        return dp[i][carry]=res;
    };
    ll res = dfs(dfs,0,false);
    if (s==x){
        res-=2;
    }
    cout<<res<<endl;
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