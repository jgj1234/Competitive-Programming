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
    vector<vector<ll>> dp (n, vector<ll> (20,-1));
    auto dfs = [&] (auto&& self, int node, int parent) -> pair<pair<ll,int>,ll>{
        for (int i = 0; i < 20; i++){
            dp[node][i] = nums[node]*(i+1);
        }
        for (int neighbor: nodeMap[node]){
            if (neighbor==parent) continue;
            pair<pair<ll,int>,ll> p = self(self,neighbor,node);
            for (int i = 0; i < 20; i++){
                if (i==p.first.second){
                    dp[node][i]+=p.second;
                }
                else{
                    dp[node][i]+=p.first.first;
                }
            }
        }
        pair<pair<ll,int>,ll> p = {{LLONG_MAX,0},LLONG_MAX};
        for (int i = 0; i < 20; i++){
            if (dp[node][i]<p.first.first){
                swap(p.first.first,p.second);
                p.first.first = dp[node][i];
                p.first.second=i;
            }
            else if (dp[node][i]<p.second){
                p.second = dp[node][i];
            }
        }
        return p;
    };
    cout<<dfs(dfs,0,0).first.first<<endl;
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