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
    vector<ll> l(n);
    vector<ll> r(n);
    for (int i = 0; i < n; i++){
        cin>>l[i]>>r[i];
    }
    vector<vector<int>> nodeMap(n);
    for (int i = 0; i < n - 1; i++){
        int a,b;
        cin>>a>>b;
        --a;--b;
        nodeMap[a].emplace_back(b);
        nodeMap[b].emplace_back(a);
    }
    vector<vector<ll>> dp(n,vector<ll> (2));
    auto dfs = [&] (auto&& self, int node, int parent) -> void{
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                self(self,neighbor,node);
                dp[node][0] += max(abs(l[node]-r[neighbor])+dp[neighbor][1],abs(l[node]-l[neighbor])+dp[neighbor][0]);
                dp[node][1] += max(abs(r[node]-l[neighbor])+dp[neighbor][0],abs(r[node]-r[neighbor])+dp[neighbor][1]);
            }
        }
    };
    dfs(dfs,0,0);
    cout<<max(dp[0][0],dp[0][1])<<endl;
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