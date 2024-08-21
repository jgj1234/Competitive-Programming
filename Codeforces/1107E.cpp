//Problem Link: https://codeforces.com/contest/1107/problem/E
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <queue>
#include <iomanip>
#include <set>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <ext/pb_ds/assoc_container.hpp>
#include <cmath>
#define pii pair<int,int>
#define pi 3.14159265358979323846
#define pb push_back
#define ppii pair<int, pair<int,int>>
#define pld pair<long long,double>
#define pibb pair<int,<bool,bool>>
#define yes "YES"
#define no "NO"
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
ll dp[100][100][101];
void solve(){
    ll n;
    cin>>n;
    string s;
    cin>>s;
    memset(dp,-1,sizeof dp);
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin>>arr[i];
    vector<ll> nums(n);
    nums[0] = arr[0];
    for (int i = 1; i < n; i++){
        nums[i] = arr[i];
        for (int j = 0; j < i; j++){
            nums[i] = max(nums[i], nums[j] + nums[i-j-1]);
        }
    }
    auto dfs = [&] (auto&& self, int l, int r, int pref) -> ll{
        if (l==r){
            return nums[pref-1];
        }
        if (l>r) return 0;
        if (dp[l][r][pref]!=-1) return dp[l][r][pref];
        ll res = nums[pref-1] + self(self, l+1,r,1);
        for (int i = l + 1; i <= r; i++){
            if (s[l] == s[i]){
                res = max(res, self(self, l+1,i-1,1)+self(self,i,r,pref+1));
            }
        }
        return dp[l][r][pref] = res;
    };
    cout<<dfs(dfs,0,n-1,1)<<endl;
}
int main(){
   int t=1;
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   //cin>>t;
   while (t--){
      solve();
   }
}