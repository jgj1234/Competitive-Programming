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
    int n,k;
    cin>>n>>k;
    set<int> marked;
    for (int i = 0; i < k; i++) {
        int x;
        cin>>x;
        marked.insert(x-1);
    }
    vector<vector<int>> nodeMap(n);
    for (int i = 0; i < n - 1; i++){
        int a,b;
        cin>>a>>b;
        --a;--b;
        nodeMap[a].emplace_back(b);
        nodeMap[b].emplace_back(a);
    }
    vector<int> subtree(n);
    auto dfs1 = [&] (auto&& self, int node, int parent) -> int{
        int res = INT_MIN;
        if (marked.count(node)) res = 0;
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                res = max(res, self(self,neighbor,node)+1);
            }
        }
        return subtree[node] = res;
    };
    vector<int> ans(n);
    ans[0] = dfs1(dfs1,0,0);
    auto dfs2 = [&] (auto&& self, int node, int parent, int mx) -> void{
        if (node!=0){
            ans[node] = max(mx,subtree[node]);
        }
        int mx1 = mx, mx1i = INT_MIN, mx2 = INT_MIN;
        if (marked.count(node)){
            if (0>=mx1){
                mx1=0;
            }
            else if (0>=mx2){
                mx2=0;
            }
        }
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                if (subtree[neighbor]+1>=mx1){
                    mx2=mx1;
                    mx1=subtree[neighbor]+1;
                    mx1i=neighbor;
                }
                else if (subtree[neighbor]+1>=mx2){
                    mx2=subtree[neighbor]+1;
                }
            }
        }
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                if (neighbor==mx1i){
                    self(self,neighbor,node,mx2+1);
                }
                else{
                    self(self,neighbor,node,mx1+1);
                }
            }
        }
    };
    dfs2(dfs2,0,0,INT_MIN);
    cout<<*min_element(all(ans))<<endl;
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