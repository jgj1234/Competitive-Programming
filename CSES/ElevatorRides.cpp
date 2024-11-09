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
    ll n,x;
    cin>>n>>x;
    vector<ll> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    vector<pair<ll,ll>> dp (1<<n);
    for (int i = 1; i < (1<<n); i++) dp[i] = pair<ll,ll> (LLONG_MAX, LLONG_MAX);
    dp[0] = pair<ll,ll> (0,x);
    for (int i = 0; i < (1<<n); i++){
        for (int j = 0; j < n; j++){
            if (((i>>j)&1)==0){
                pair<ll,ll> p = pair<ll,ll> (dp[i].first, dp[i].second + nums[j]);
                if (p.second > x){
                    p = pair<ll,ll> (dp[i].first + 1, nums[j]);
                }
                dp[i|(1<<j)] = min(dp[i|(1<<j)],p);
            }
        }
    }
    cout<<dp.back().first<<'\n';
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