#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <ext/pb_ds/assoc_container.hpp>
 
#include <cmath>
#define pii pair<int,int>
#define pb push_back
#define ppii pair<int, pair<int,int>>
#define pld pair<long long,double>
#define pibb pair<int,<bool,bool>>
#define yes "YES"
#define no "NO"
#define ll long long
#define MOD 1000000007
#define MOD2 998244353
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
 
void solve(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> nodeMap(n);
    for (int i = 0; i < m; i++){
        int a,b;
        cin>>a>>b;
        --a;--b;
        nodeMap[a].emplace_back(b);
    }
    vector<int> dp (n,-1);
    auto dfs = [&] (auto self, int node) -> int{
        if (node==n-1) return 1;
        if (dp[node]!=-1) return dp[node];
        int res = 0;
        for (int neighbor: nodeMap[node]){
            res+=self(self,neighbor);
            res%=MOD;
        }
        return dp[node]=res;        
    };
    cout<<dfs(dfs,0)<<endl;
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