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
    int n,c,k; cin>>n>>c>>k;
    string s; cin>>s;
    if (n == k){
        cout << 1 << '\n';
        return;
    }
    vector<vector<int>> pref(n, vector<int> (c));
    for (int i = 0; i < n; i++){
        pref[i][s[i]-'A']++;
        if (i){
            for (int j = 0; j < c; j++) pref[i][j] += pref[i-1][j];
        }
    }
    vector<int> dp (1 << c);
    dp[(1<<(s.back()-'A'))^((1<<c)-1)]++;
    for (int i = 0; i + k - 1 < n; i++){
        vector<int> curr(all(pref[i+k-1]));
        if (i){
            for (int j = 0; j < c; j++) curr[j] -= pref[i-1][j];
        }
        int mask = 0;
        for (int j = 0; j < c; j++){
            if (curr[j]) mask|=(1<<j);
        }
        dp[mask^((1<<c)-1)]++;
    }
    for (int i = 0; i < c; i++){
        for (int mask = (1 << c) - 1; mask >= 0; mask--){
            if ((mask&(1<<i))==0) dp[mask] += dp[mask|(1<<i)];
        }
    }
    int res = INT_MAX;
    for (int i = 0; i < (1<<c); i++){
        if (dp[i]==0){
            res = min(res, __builtin_popcount(i));
        }
    }
    cout << res << endl;
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