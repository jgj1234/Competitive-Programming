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
    int n,a,b;
    cin>>n>>a>>b;
    --a;--b;
    vector<vector<int>> nodeMap(n);
    for (int i = 0; i < n; i++){
        int u,v;
        cin>>u>>v;
        --u;--v;
        nodeMap[u].emplace_back(v);
        nodeMap[v].emplace_back(u);
    }
    auto dfs1 = [&] (auto&& self, int node, int parent, vector<int>& tim, int time) -> int{
        if (tim[node]!=-1){
            return node;
        }
        tim[node] = time;
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                int x = self(self,neighbor, node, tim,time+1);
                if (x!=-1) return x;
            }
        }
        return -1;
    };
    vector<int> tim1 (n,-1);
    int n1 = dfs1(dfs1,b,-1,tim1,0);
    int t1 = tim1[n1];
    auto dfs2 = [&] (auto&& self, int node, int parent, int time) -> int{
        if(node==n1) return time;
        int res = INT_MAX;
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                res=min(res,self(self,neighbor,node,time+1));
            }
        }
        return res;
    };
    int t2 = dfs2(dfs2,a,-1,0);
    cout<<(t1<t2?"YES":"NO")<<endl;
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