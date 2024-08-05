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
      nodeMap[b].emplace_back(a);
   }
   vector<bool> visited (n);
   auto dfs = [&] (auto self, int node) -> void{
      visited[node]=true;
      for (int neighbor: nodeMap[node]){
         if (!visited[neighbor]){
            self(self,neighbor);
         }
      }
   };
   vector<pii> roads;
   int last = -1;
   int ncc = 0;
   for (int i = 0; i < n; i++){
      if (!visited[i]){
         if (ncc>0){
            roads.emplace_back(last+1,i+1);
         }
         dfs(dfs,i);
         last = i;
         ncc++;
      }
   }
   cout<<roads.size()<<endl;
   for (auto [a,b]: roads){
      cout<<a<<" "<<b<<endl;
   }
 
}
int main(){
   int t=1;
   //cin>>t;
   while (t--){
      solve();
   }
}