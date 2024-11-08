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
    ll n;
    cin>>n;
    vector<array<ll,2>> dp (n + 1);
    dp[n][0] = dp[n][1] = 1;
    for (int i = n - 1; i > 0; i--){
        dp[i][0] = (2*dp[i+1][0] + dp[i+1][1])%MOD;
        dp[i][1] = (dp[i+1][0] + 4*dp[i+1][1])%MOD;
    }
    cout<<(dp[1][0] + dp[1][1])%MOD<<'\n';
}
int main(){
    int t=1;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>t;
    for (int i = 1; i<=t; i++){
        solve(i);
    }
    return 0;
}