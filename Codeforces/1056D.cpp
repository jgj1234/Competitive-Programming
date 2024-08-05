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
#define MOD2 998244353
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

void solve(){
    int n;
    cin>>n;
    if (n==1){
        cout<<1;
        return;
    }
    vector<int> edges(n-1);
    for (int i = 0; i < n - 1; i++) cin>>edges[i];
    vector<vector<int>> nodeMap(n);
    for (int i = 0; i < n - 1; i++){
        nodeMap[i+1].emplace_back(edges[i]-1);
        nodeMap[edges[i]-1].emplace_back(i+1);
    }
    vector<int> sz(n);
    auto dfs = [&] (auto self, int node, int parent)->int{
        int res = 0;
        if (nodeMap[node].size()==1 && node!=0){
            res=1;
        }
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                res+=self(self,neighbor,node);
            }
        }
        return sz[node]=res;
    };
    dfs(dfs,0,0);
    sort(sz.begin(),sz.end());
    for (int i = 0; i < n; i++){
        cout<<sz[i]<<" ";
    }
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