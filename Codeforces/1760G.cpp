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
    int n,a,b;
    cin>>n>>a>>b;
    --a;--b;
    vector<vector<pii>> nodeMap(n);
    for (int i = 0; i < n-1; i++){
        int x,y,z;
        cin>>x>>y>>z;
        --x;--y;
        nodeMap[x].emplace_back(y,z);
        nodeMap[y].emplace_back(x,z);
    }
    set<int> bedges;
    vector<bool> visited(n); visited[b]=true;
    queue<pii> q;
    q.push({b,0});
    while (!q.empty()){
        auto [node,xr] = q.front(); q.pop();
        for (auto [neighbor,w]:nodeMap[node]){
            if (!visited[neighbor]){
                visited[neighbor]=true;
                q.push({neighbor,xr^w});
                bedges.insert(xr^w);
            }
        }
    }
    auto dfs = [&] (auto self, int node, int parent, int xr) -> bool{
        if (bedges.find(xr)!=bedges.end()){
            return true;
        }
        for (auto [neighbor, weight]: nodeMap[node]){
            if ((neighbor==parent)||(neighbor==b)) continue;
            if (self(self,neighbor,node,xr^weight)){
                return true;
            }
        }
        return false;
    };
    cout<<(dfs(dfs,a,a,0)?"YES":"NO")<<endl;
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