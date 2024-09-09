#include <bits/stdc++.h>
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
const int MAXN = 100005;
ll sz[MAXN], tin[MAXN], low[MAXN];
bool vis[MAXN];
ll res,tim,n;
void dfs(int node, int parent, vector<vector<int>>& nodeMap){
    sz[node] = 1;
    vis[node] = true;
    tin[node] = low[node] = tim++;
    for (int neighbor: nodeMap[node]){
        if (neighbor!=parent){
            if (vis[neighbor]){
                low[node] = min(low[node], low[neighbor]);
            }
            else{
                dfs(neighbor,node,nodeMap);
                low[node] = min(low[node],low[neighbor]);
                sz[node] += sz[neighbor];
            }
        }
    }
    if (low[node]==tin[node]){
        res = min(res, (sz[node]*(sz[node]-1))/2 + ((n-sz[node])*(n-sz[node]-1))/2);
    }
    
}
void solve(){
    ll m;
    cin>>n>>m;
    tim = 0;
    res = n*(n-1)/2;
    for (int i = 0; i < n; i++){
        sz[i] = tin[i] = low[i] = vis[i] = 0;
    }
    vector<vector<int>> nodeMap(n);
    for (int i = 0; i < m; i++){
        int a,b;
        cin>>a>>b;
        --a;--b;
        nodeMap[a].emplace_back(b);
        nodeMap[b].emplace_back(a);
    }
    dfs(0,0,nodeMap);
    cout<<res<<endl;
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