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
    vector<ll> nums(n);
    for (auto& a: nums) cin>>a;
    int lg = 32 - __builtin_clz(*max_element(all(nums)));
    pii dp[1<<lg];
    for (int i = 0; i < (1<<lg); i++){
        dp[i] = pii(-1,-1);
    }
    for (int i = n - 1; i >= 0; i--){
        if (dp[nums[i]].first==-1){
            dp[nums[i]].first = i;
        }
        else if (dp[nums[i]].second==-1){
            dp[nums[i]].second = i;
        }
    }
    auto Combine =  [&] (pii& ans, pii& bef) -> void{
        if (bef.first > ans.first){
            ans.second = ans.first;
            ans.first = bef.first;
        }
        else if (bef.first > ans.second){
            ans.second = bef.first;
        }
        if (bef.second > ans.second){
            ans.second = bef.second;
        }
    };
    for (int i = 0; i < lg; i++){
        for (int mask = 0; mask < (1<<lg); mask++){
            if ((mask&(1<<i))==0){
                Combine(dp[mask], dp[mask|(1<<i)]);
            }
        }
    }
    ll res = 0;
    for (int i = 0; i < n - 2; i++){
        ll curr = 0;
        for (int bit = lg - 1; bit >= 0; bit--){
            if ((nums[i]&(1<<bit))==0){
                if (dp[curr^(1<<bit)].first > i && dp[curr^(1<<bit)].second > i){
                    curr |= (1<<bit);
                }
            }
        }
        res = max(res, nums[i]|curr);
    }
    cout << res << '\n';
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