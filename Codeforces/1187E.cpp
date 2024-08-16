//Problem Link: https://codeforces.com/contest/1187/problem/E
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
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
void solve(){
    int n;
    cin>>n;
    vector<vector<int>> nodeMap(n);
    for (int i = 0; i < n - 1; i++){
        int a,b;
        cin>>a>>b;
        --a;--b;
        nodeMap[a].emplace_back(b);
        nodeMap[b].emplace_back(a);
    }
    vector<ll> sub(n), info(n), dp(n);
    auto dfs = [&] (auto&& self, int node, int parent) -> ll{
        ll sz = 1;
        ll res = 0;
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                sz+=self(self,neighbor,node);
                res+=info[neighbor];
            }
        }
        info[node] = sz+res;
        sub[node]=sz;
        return sz;
    };
    dfs(dfs,0,0);
    auto dfs1 = [&] (auto&& self, int node, int parent, ll pass) -> void{
        dp[node] = info[node]+pass+(n-sub[node]);
        ll infoSum = info[node] - sub[node];
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                self(self, neighbor, node, pass + (infoSum-info[neighbor])+(n-sub[neighbor]));
            }
        }
    };
    dfs1(dfs1,0,0,0);
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