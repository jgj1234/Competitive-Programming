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
ll dp[501][501];
void solve(int cas){
    int a,b;
    cin>>a>>b;
    for (int i = 0; i < 501; i++) for (int j = 0; j < 501; j++) dp[i][j] = LLONG_MAX;
    if (a==b){
        cout<<0<<'\n'; return;
    }
    for (int i = 1; i <= b; i++) dp[1][i] = i - 1;
    for (int i = 2; i <= a; i++){
        for (int j = 1; j<=b; j++){
            if (i==j){
                dp[i][j] = 0; continue;
            }
            //i rows j columns. try horizontal cuts then vertical cuts
            for (int hz = 1; hz < i; hz++){
                dp[i][j] = min(dp[i][j], 1 + dp[hz][j] + dp[i-hz][j]);
            }
            for (int vt = 1; vt < j; vt++){
                dp[i][j] = min(dp[i][j], 1 + dp[i][vt] + dp[i][j-vt]);
            }
        }
    }
    cout<<dp[a][b]<<'\n';
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