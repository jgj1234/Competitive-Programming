#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define yes "YES"
#define no "NO"
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
const ll MAXN = 200005, MAX_LG = 18;
ll tin[MAXN], tout[MAXN], depths[MAXN], jump[MAXN][MAX_LG];
int tim = 0;
vector<ll> nodeMap[MAXN];
void dfs(int node, int parent){
    tin[node] = tim++;
    if (node!=0) depths[node] = depths[parent] + 1;
    jump[node][0] = parent;
    for (int j = 1; j < MAX_LG; j++){
        jump[node][j] = jump[jump[node][j-1]][j-1];
    }
    for (int neighbor: nodeMap[node]){
        if (neighbor!=parent){
            dfs(neighbor,node);
        }
    }
    tout[node] = tim++;
};
bool anc(int u, int v){
    return tin[u]<=tin[v] && tout[u]>=tout[v];
}
inline int lca(int a, int b){
    if (depths[a] > depths[b]) swap(a,b);
    if (anc(a,b)) return a;
    for (int x = MAX_LG - 1; x>=0; x--){
        if (!anc(jump[a][x], b)) a = jump[a][x];
    }
    return jump[a][0];
}
void solve(int cas){
    int n,m;
    cin>>n>>m;
    for (int i = 0; i < n - 1; i++){
        int a,b;
        cin>>a>>b;
        --a;--b;
        nodeMap[a].emplace_back(b);
        nodeMap[b].emplace_back(a);
    }
    dfs(0,0);
    vector<ll> start(n), end(n);
    for (int i = 0; i < m; i++){
        int a,b;
        cin>>a>>b;
        --a;--b;
        start[a]++;
        start[b]++;
        end[lca(a,b)]++;
    }
    vector<ll> res(n);
    auto calc = [&] (auto&& self, int node, int parent) -> ll{
        ll f = start[node];
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                f+=self(self,neighbor,node);
            }
        }
        res[node] = f - end[node];
        return f - 2*end[node];
    };
    calc(calc,0,0);
    for (int i = 0; i < n; i++) cout<<res[i]<<' ';
    cout<<'\n';
}
int main(){
    int t=1;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //cin>>t;
    for (int i = 1; i<=t; i++){
        solve(i);
    }
    return 0;
}