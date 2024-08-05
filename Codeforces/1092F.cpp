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
    ll n;
    cin>>n;
    vector<ll> nums(n);
    ll s = 0;
    for (ll i = 0; i < n; i++){
        cin>>nums[i];
        s+=nums[i];
    }
    vector<vector<ll>> nodeMap(n);
    for (ll i = 0; i < n - 1; i++){
        ll a,b;
        cin>>a>>b;
        --a;--b;
        nodeMap[a].emplace_back(b);
        nodeMap[b].emplace_back(a);
    }
    vector<ll> sub(n);
    auto dfs = [&] (auto self, ll node, ll parent, ll dist, ll& res) -> ll {
        res += dist*nums[node];
        ll ans = nums[node];
        for (ll neighbor: nodeMap[node]){
            if (neighbor!=parent){
                ans+=self(self,neighbor,node,dist+1,res);
            }
        }
        return sub[node]=ans;
    };
    ll init = 0;
    dfs(dfs,0,0,0,init);
    vector<ll> dp (n);
    dp[0]=init;
    auto dfs2 = [&] (auto self, ll node, ll parent) -> void{
        if (node!=0){
            dp[node] = dp[parent] + (s-sub[node]) - sub[node];
        }
        for (ll neighbor: nodeMap[node]){
            if (neighbor!=parent){
                self(self,neighbor,node);
            }
        }
    };
    dfs2(dfs2,0,0);
    cout<<*max_element(all(dp))<<endl;
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