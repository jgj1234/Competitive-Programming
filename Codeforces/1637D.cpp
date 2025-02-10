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
void solve(int cas){ 
    int n; cin>>n;
    vector<ll> a(n), b(n);
    for (auto& x: a) cin>>x;
    for (auto& x: b) cin>>x;
    vector<vector<ll>> dp(n+1, vector<ll> (10001, LLONG_MAX));
    for (int i = 0; i <= 10000; i++) dp[n][i] = 0;
    vector<ll> pref(n);
    pref[0] = b[0] + a[0];
    for (int i = 1; i < n; i++) pref[i] = pref[i-1] + b[i] + a[i];
    //dp[i][prefa_sum]
    for (int i = n - 1; i >= 0; i--){
        for (int p = 0; p <= (i==0 ? 0:pref[i-1]); p++){
            ll bsum = (i==0?0:pref[i-1] - p);
            if (p + a[i] <= 10000 && dp[i+1][p + a[i]]!=LLONG_MAX){
                dp[i][p] = (2*a[i]*p+(a[i]*a[i]*(n-1)))+(2*b[i]*bsum+(b[i]*b[i]*(n-1)))+dp[i+1][p+a[i]];
            }
            if (p + b[i] <= 10000 && dp[i+1][p+b[i]]!=LLONG_MAX){
                dp[i][p] = min(dp[i][p], (2*b[i]*p+(b[i]*b[i]*(n-1)))+(2*a[i]*bsum+(a[i]*a[i]*(n-1)))+dp[i+1][p+b[i]]);
            }
        }
    }
    cout << dp[0][0] << '\n';
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t = 1;
    cin>>t;
    for (int i = 1; i <= t; i++){
        solve(i);
    }
    return 0;
}
