#include <bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
struct DSU{
    vector<int> par, rank, sz, mx;
    int cc;
    DSU(int n){
        cc = n;
        par.resize(n, -1);
        rank.resize(n);
        sz.resize(n, 1);
        mx.resize(n);
        iota(mx.begin(), mx.end(), 0);
    }
    int find(int u){
        return par[u]==-1?u:par[u] = find(par[u]);
    }
    bool merge(int u, int v){
        int uPar = find(u), vPar = find(v);
        if (uPar==vPar) return false;
        if (rank[uPar]==rank[vPar]) rank[uPar]++;
        cc--;
        if (rank[uPar] > rank[vPar]){
            sz[uPar] += sz[vPar];
            par[vPar] = uPar;
        }
        else{
            sz[vPar] += sz[uPar];
            par[uPar] = vPar;
        }
        return true;
    }
};
void solve(int cas){  
    int n,m; cin>>n>>m;
    using tll = tuple<ll,ll,ll>;
    vector<tll> edges(m);
    vector<int> deg(n);
    ll smw = 0;
    for (int i = 0; i < m; i++){
        int u,v,w; cin>>u>>v>>w;
        smw += w;
        --u;--v;
        deg[u]++;
        deg[v]++;
        edges[i] = make_tuple(u, v, w);
    }
    int cto = 0;
    for (int i = 0; i < n; i++){
        cto += deg[i] & 1;
    }
    if (cto == 0){
        cout << smw << '\n';
        return;
    }
    DSU dsu(n);
    vector<vector<int>> g(n + m);
    vector<ll> vals(n + m);    
    int idx = n;
    for (auto& [u, v, w]: edges){
        int uPar = dsu.find(u), vPar = dsu.find(v);
        dsu.merge(u, v);
        if (uPar == vPar){
            g[idx].emplace_back(dsu.mx[uPar]);
        }
        else{
            g[idx].emplace_back(dsu.mx[uPar]);
            g[idx].emplace_back(dsu.mx[vPar]);
        }
        dsu.mx[uPar] = dsu.mx[vPar] = idx;
        vals[idx] = w;
        idx++;
    }
    auto Dfs = [&] (auto&& self, int node, ll mn) -> pair<ll,ll>{
        if (g[node].empty()){
            return {0, deg[node] & 1};
        }
        mn = min(mn, vals[node]);
        ll res = 0, um = 0;
        for (int neighbor: g[node]){
            auto [sm, unmatched] = self(self, neighbor, mn);
            res += sm;
            um += unmatched;
        }
        res += mn * (um / 2);
        return {res, um & 1};
    };
    cout << smw + Dfs(Dfs, n + m - 1, LLONG_MAX).first << '\n';
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t = 1;
    cin>>t;
    for (int i = 1; i <= t; i++){
        solve(i);
    }
    return 0;
}