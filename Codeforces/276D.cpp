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
    ll l,r;
    cin>>l>>r;
    int lg = 63 - __builtin_clzll(r);
    ll dp[lg+1][2][2][2][2];
    for (int i = 0; i < lg + 1; i++){
        for (int j = 0; j < 2; j++){
            for (int k = 0; k < 2; k++){
                for (int l = 0; l < 2; l++){
                    for (int m = 0; m < 2; m++){
                        dp[i][j][k][l][m]=-1;
                    }
                }
            }
        }
    }
    function<ll(ll, bool, bool, bool, bool)> dfs = [&] (ll i, bool lt1, bool rt1, bool lt2, bool rt2) -> ll{
        if (i<0){
            return 0;
        }
        if (dp[i][lt1][rt1][lt2][rt2]!=-1) return dp[i][lt1][rt1][lt2][rt2];
        ll res = 0;
        ll length = 1LL<<(i+1);
        ll half = length>>1;
        bool diff = r-l>=half || ((r&(1LL<<i))!=(l&(1LL<<i)));
        int lt = ((l&(1LL<<i))!=0);
        int rt = ((r&(1LL<<i))!=0);
        for (int b1 = 0; b1 < 2; b1++){
            for (int b2 = 0; b2 < 2; b2++){
                if (!diff && (b1!=b2||b1!=rt)) continue;
                if ((lt1&& lt>b1) || (rt1 && rt<b1)) continue;
                if ((lt2 && lt>b2) || (rt2 && b2>rt)) continue;
                ll add = (b1!=b2?(1LL<<i):0LL);
                res = max(res,add+dfs(i-1,lt1&&b1==lt,rt1&&b1==rt,lt2&&b2==lt,rt2&&b2==rt));
            }
        }
        return dp[i][lt1][rt1][lt2][rt2]=res;
    };
    cout<<dfs(lg,true,true,true,true)<<endl;
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