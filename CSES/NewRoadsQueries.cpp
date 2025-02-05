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
struct DSU{
    vector<int> par, sz, rank, md;
    DSU(int n, int m){
        par.resize(n + m, -1);
        sz.resize(n + m, 1);
        rank.resize(n + m);
        md.resize(n);
        iota(all(md), 0);
    }
    int find(int u){
        return par[u]==-1 ? u : par[u] = find(par[u]);
    }
    void merge(int u, int v, int day){
        if (rank[u]==rank[v]){
            rank[u]++;
        }
        if (rank[u] > rank[v]){
            sz[u] += sz[v];
            par[v] = u;
            md[u] = day;
        }
        else{
            sz[v] += sz[u];
            par[u] = v;
            md[v] = day;
        }
    }
};
void solve(int cas){ 
    int n,m,q; cin>>n>>m>>q;
    DSU dsu(n, m);
    vector<vector<ll>> g(n + m);
    for (int day = 0; day < m; day++){
        int u,v; cin>>u>>v;
        --u;--v;
        int uPar = dsu.find(u), vPar = dsu.find(v);
        if (uPar==vPar) continue;
        g[day + n].emplace_back(dsu.md[uPar]);
        g[day + n].emplace_back(dsu.md[vPar]);
        dsu.merge(uPar, vPar, day + n);
    }
    int tim = 0;
    vector<ll> start(n + m, -1), end(n + m), depths(n + m);
    vector<vector<ll>> jump(n + m, vector<ll> (20));
    auto dfs = [&] (auto&& self, int node, int parent, int depth) -> void{
        start[node] = tim++;
        depths[node] = depth;
        jump[node][0] = parent;
        for (int i = 1; i < 20; i++){
            jump[node][i] = jump[jump[node][i-1]][i-1];
        }
        for (int neighbor: g[node]){
            if (neighbor!=parent){
                self(self,neighbor,node,depth+1);
            }
        }
        end[node] = tim;
    };
    for (int i = n + m - 1; i >= 0; i--){
        if (start[i]==-1){
            dfs(dfs,i,i,0);
        }
    }
    auto anc = [&] (int u, int v) -> bool{
        return start[u] <= start[v] && end[u] >= end[v];
    };
    auto lca = [&] (int u, int v) -> int{
        if (depths[u] < depths[v]) swap(u,v);
        if (anc(u,v)) return u;
        for (int j = 19; j >= 0; j--){
            if (!anc(jump[u][j], v)) u = jump[u][j];
        }
        return jump[u][0];
    };
    while (q--){
        int a,b; cin>>a>>b;
        --a;--b;
        if (a==b){
            cout << 0 << '\n';
        }
        else if (dsu.find(a) != dsu.find(b)){
            cout << -1 << '\n';
        }
        else{
            cout << lca(a,b)-n+1 << '\n';
        }
    }
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t = 1;
    //cin>>t;
    for (int i = 1; i <= t; i++){
        solve(i);
    }
    return 0;
}
