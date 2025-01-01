#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define yes "YES"
#define no "NO"
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
void solve(int cas){  
    int n,m; cin>>n>>m;
    vector<vector<bool>> g(n, vector<bool>(n));
    for (int i = 0; i < m; i++){
        int a,b; cin>>a>>b;
        --a;--b;
        g[a][b] = true;
        g[b][a] = true;
    }
    vector<ll> dp(1<<n, INT_MAX);
    vector<bool> gs(1<<n);
    for (int mask = 1; mask < (1<<n); mask++){
        bool good = true;
        for (int j = 0; j < n; j++){
            if ((mask>>j)&1){
                for (int k = j + 1; k < n; k++){
                    if ((mask>>k)&1){
                        if (!g[j][k]){
                            good = false;
                            break;
                        }
                    }
                }
            }
            if (!good) break;
        }
        if (good){
            dp[mask] = 1;
            gs[mask] = true;
        }
    }
    dp[0] = 0;
    for (int mask = 1; mask < (1<<n); mask++){
        if (gs[mask]) continue;
        dp[mask] = __builtin_popcount(mask);
        for (int sm = mask; sm; sm = (sm-1)&mask){
            if (dp[sm]!=INT_MAX && dp[sm^mask]!=INT_MAX){
                dp[mask] = min(dp[mask], dp[sm^mask] + dp[sm]);
            }
        }
    }
    cout << dp.back() << '\n';
    
}
int main(){
    int t=1;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //cin>>t;
    for (int i = 1; i<=t; i++){
        solve(i);
    }
    return 0;
}