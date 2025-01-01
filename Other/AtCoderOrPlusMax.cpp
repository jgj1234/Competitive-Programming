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
    int n; cin>>n;
    vector<ll> nums(1<<n);
    for (auto& a: nums) cin>>a;
    vector<vector<int>> dp(1<<n, vector<int>(2));
    for (int i = 0; i < (1<<n); i++) dp[i][0] = nums[i];
    for (int i = 0; i < n; i++){
        for (int mask = 1; mask < (1<<n); mask++){
            if ((mask&(1<<i))){
                if (dp[mask^(1<<i)][0] >= dp[mask][0]){
                    swap(dp[mask][0], dp[mask][1]);
                    dp[mask][0] = dp[mask^(1<<i)][0];
                }
                else if (dp[mask^(1<<i)][0] >= dp[mask][1]){
                    dp[mask][1] = dp[mask^(1<<i)][0];
                }
                if (dp[mask^(1<<i)][1] >= dp[mask][1]){
                    dp[mask][1] = dp[mask^(1<<i)][1];
                }
            }
        }
    }
    int res = 0;
    for (int i = 1; i < (1<<n); i++){
        res = max(res, dp[i][0] + dp[i][1]);
        cout << res << '\n';
    }
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