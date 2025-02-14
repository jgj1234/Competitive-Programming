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
    int n,p; cin>>n>>p;
    vector<ll> nums(n);
    for (auto& a: nums) cin>>a;
    sort(all(nums));
    vector<int> dp(p+1);
    dp[0] = 1;
    for (int i = 1; i <= p; i++){
        dp[i] += dp[i-1];
        if (i > 1) dp[i] += dp[i-2];
        if (dp[i] >= MOD) dp[i] -= MOD;
    }
    for (int i = 1; i <= p; i++){
        dp[i] += dp[i-1];
        if (dp[i] >= MOD) dp[i] -= MOD;
    }
    set<ll> prev;
    auto check = [&] (ll num) -> bool{
        while (num > 0){
            if (num&1){
                num>>=1;
            }
            else{
                if ((num&2)) return true;
                num>>=2;
            }
            if (prev.count(num)) return false;
        }
        return true;
    };
    ll res = 0;
    for (int i = 0; i < n; i++){
        if (32 - __builtin_clz(nums[i]) > p) break;
        if (check(nums[i])){
            prev.insert(nums[i]);
            res += dp[p - (32 - __builtin_clz(nums[i]))];
            if (res >= MOD) res -= MOD;
        }
    }
    cout << res << '\n';
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t = 1;
    //cin>>t;
    for (int i = 1; i <= t; i++){
        solve(i);
    }
    return 0;
}
