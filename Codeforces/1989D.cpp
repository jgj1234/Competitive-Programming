#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <iomanip>
#include <set>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <ext/pb_ds/assoc_container.hpp>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
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
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
void solve(){
    int n,m;
    cin>>n>>m;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin>>a[i];
    vector<ll> b(n);
    for (int i = 0; i < n; i++) cin>>b[i];
    vector<pii> pairs(n);
    for (int i = 0; i < n; i++) pairs[i] = pii(a[i],b[i]);
    sort(all(pairs));
    vector<pair<ll,ll>> diffs;
    int minDiff = INT_MAX;
    for (int i = 0; i < n; i++){
        if (pairs[i].first-pairs[i].second<minDiff){
            minDiff = pairs[i].first-pairs[i].second;
            diffs.emplace_back(pair<ll,ll> (pairs[i].first,pairs[i].first-pairs[i].second));
        }
    }
    vector<ll> c(m);
    int mn = *min_element(all(a));
    for (int i = 0; i < m; i++) cin>>c[i];
    vector<ll> dp (*max_element(all(a))+1,-1);
    auto dfs = [&] (auto self, int i) -> ll{
        if (i<mn) return 0;
        if (i<dp.size() && dp[i]!=-1) return dp[i];
        int lp = 0, rp = diffs.size() - 1;
        while (lp<=rp){
            int mid = (lp+rp)>>1;
            if (diffs[mid].first>i){
                rp=mid-1;
            }
            else{
                lp=mid+1;
            }
        }
        ll times = (i-diffs[rp].first)/diffs[rp].second+1;
        if (i>=dp.size()){
            return times+self(self,i-times*diffs[rp].second);
        }
        return dp[i]=times+self(self,i-times*diffs[rp].second);
    };
    ll res = 0;
    for (int i = 0; i < m; i++){
        res+=2*dfs(dfs,c[i]);
    }
    cout<<res<<endl;
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