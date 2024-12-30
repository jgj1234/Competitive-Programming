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
const ll MAX_BIT = 23;
ll dp[1<<MAX_BIT];
void solve(int cas){  
    int n; cin>>n;
    vector<ll> nums(n);
    for (auto& a: nums) cin>>a;
    memset(dp, -1, sizeof dp);
    for (int i = 0; i < n; i++){
        dp[nums[i]] = nums[i];
    }
    for (int i = 0; i < MAX_BIT; i++){
        for (int mask = 1; mask < (1<<MAX_BIT); mask++){
            if (mask&(1<<i)){
                if (dp[mask^(1<<i)]!=-1) dp[mask] = dp[mask^(1<<i)];
            }
        }
    }
    for (int i = 0; i < n; i++){
        cout << dp[((1<<MAX_BIT)-1)^nums[i]] << ' ';
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