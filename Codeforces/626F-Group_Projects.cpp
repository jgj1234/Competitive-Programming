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
    ll n,k; cin>>n>>k;
    vector<ll> nums(n);
    for (auto& a: nums) cin>>a;
    sort(all(nums));
    vector<vector<ll>> dp (n+1, vector<ll> (k+2));
    for (int i = 0; i <= k; i++){
        dp[0][i] = 1;
    }
    for (ll i = n - 1; i >= 0; i--){
        vector<vector<ll>> curr(n+1, vector<ll> (k+2));
        for (ll j = 0; j <= min(i, n-i); j++){
            for (ll imb = 0; imb <= k; imb++){
                if (i==0 && (imb||j)) continue;
                if (i==n-1){
                    curr[j][imb] = 1;
                    continue;
                }
                if (imb + (nums[i+1] - nums[i])*j <= k){
                    curr[j][imb] = dp[j][imb+(nums[i+1]-nums[i])*j]; //group of size 1
                }
                // adding to open group without closing
                if (i && j){
                    ll newImb = imb + (nums[i+1] - nums[i])*j;
                    if (newImb <= k){
                        curr[j][imb] += (j*dp[j][newImb])%MOD;
                        if (curr[j][imb] >= MOD) curr[j][imb] -= MOD;
                    }
                }
                //creating new group
                if (j < n){
                    ll newImb = imb + (nums[i+1] - nums[i])*(j+1);
                    if (newImb <= k){
                        curr[j][imb] += dp[j+1][newImb];
                        if (curr[j][imb] >= MOD) curr[j][imb] -= MOD;
                    }
                }
                //closing group
                if (j){
                    ll newImb = imb + (nums[i+1] - nums[i])*(j-1);
                    if (newImb <= k){
                        curr[j][imb] += (j*(dp[j-1][newImb]))%MOD;
                        if (curr[j][imb] >= MOD) curr[j][imb] -= MOD;
                    }
                }
            }
        }
        dp = curr;
    }
    cout << dp[0][0] << '\n';
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