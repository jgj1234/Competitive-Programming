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
#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
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
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
void solve(){
    int n;
    cin>>n;
    vector<ll> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    vector<vector<int>> nodeMap(n);
    for (int i = 0; i < n - 1; i++){
        int x,y;
        cin>>x>>y;
        --x;--y;
        nodeMap[x].emplace_back(y);
        nodeMap[y].emplace_back(x);
    }
    vector<ll> dp1 (n);
    vector<ll> sz (n,-1);
    auto dfs1 = [&] (auto&& self, int node, int parent) -> ll{
        int res = 1;
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                res+=self(self,neighbor,node);
                dp1[node]+=dp1[neighbor] + (sz[neighbor]*(nums[neighbor]^nums[node]));
            }
        }
        return sz[node]=res;
    };
    vector<ll> dp (n,-1);
    dfs1(dfs1,0,0);
    dp[0]=dp1[0];
    auto dfs2 = [&] (auto&& self, int node, int parent) ->void{
        if (node!=0){
            dp[node]=dp[parent]-((nums[node]^nums[parent])*(sz[node])) + ((nums[node]^nums[parent])*(n-sz[node]));
        }
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                self(self,neighbor,node);
            }
        }
    };
    dfs2(dfs2,0,0);
    for (int i = 0; i < n; i++){
        cout<<dp[i]<<" ";
    }
    cout<<endl;
}
int main(){
   int t=1;
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   cin>>t;
   while (t--){
      solve();
   }
}