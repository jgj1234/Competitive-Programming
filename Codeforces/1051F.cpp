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
struct UnionFind{
    vector<ll> par, rank;
    UnionFind(int n){
        par.resize(n, -1);
        rank.resize(n);
    }
    int find(int u){
        if (par[u]==-1) return u;
        return par[u] = find(par[u]);
    }
    bool unionn(int u, int v){
        int uPar = find(u), vPar = find(v);
        if (uPar==vPar) return false;
        if (rank[uPar]==rank[vPar]) rank[uPar]++;
        if (rank[uPar] > rank[vPar]) par[vPar] = uPar;
        else par[uPar] = vPar;
        return true;
    }
};
void solve(int cas){
    int n,m; cin>>n>>m;
    vector<vector<ll>> edges(m, vector<ll> (3));
    for (int i = 0; i < m; i++){
        cin>>edges[i][0]>>edges[i][1]>>edges[i][2];
        --edges[i][0]; --edges[i][1];
    }
    sort(all(edges), [] (vector<ll>& v1, vector<ll>& v2){
        return v1[2] < v2[2];
    });
    UnionFind uf(n);
    vector<vector<pair<ll,ll>>> g(n);
    vector<vector<ll>> rem;
    vector<vector<pair<ll,ll>>> g1(n);
    for (int i = 0; i < m; i++){
        if (uf.unionn(edges[i][0], edges[i][1])){
            g[edges[i][0]].emplace_back(make_pair(edges[i][1], edges[i][2]));
            g[edges[i][1]].emplace_back(make_pair(edges[i][0], edges[i][2]));
        }
        else{
            rem.emplace_back(edges[i]);
        }
        g1[edges[i][0]].emplace_back(make_pair(edges[i][1], edges[i][2]));
        g1[edges[i][1]].emplace_back(make_pair(edges[i][0], edges[i][2]));
    }
    int lg = 32 - __builtin_clz(n);
    vector<ll> start(n), end(n), depths(n), pref(n);
    vector<vector<ll>> jump(n, vector<ll> (lg));
    int tim = 0;
    auto dfs = [&] (auto&& self, int node, int parent, int depth, ll sm) -> void{
        start[node] = tim++;
        depths[node] = depth;
        jump[node][0] = parent;
        pref[node] = sm;
        for (int i = 1; i < lg; i++){
            jump[node][i] = jump[jump[node][i-1]][i-1];
        }
        for (const auto& [neighbor, weight]: g[node]){
            if (neighbor!=parent){
                self(self,neighbor,node,depth+1,sm+weight);
            }
        }
        end[node] = tim;
    };
    dfs(dfs,0,0,0,0);
    auto anc = [&] (int u, int v) -> bool{
        return start[u] <= start[v] && end[u] >= end[v];
    };
    auto lca = [&] (int u, int v) -> int{
        if (depths[u] > depths[v]) swap(u,v);
        if (anc(u,v)) return u;
        for (int i = lg - 1; i >= 0; i--){
            if (!anc(jump[u][i], v)){
                u = jump[u][i];
            }
        }
        return jump[u][0];
    };
    auto dist = [&] (int u, int v) -> ll{
        return pref[u] + pref[v] - 2*pref[lca(u,v)];
    };
    int q; cin>>q;
    vector<vector<ll>> bad;
    for (int i = 0; i < rem.size(); i++){
        vector<ll> dp(n, LLONG_MAX);
        dp[rem[i][0]] = 0;
        priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> heap;
        heap.push(make_pair(0,rem[i][0]));
        while (!heap.empty()){
            auto [weight, node] = heap.top(); heap.pop();
            if (weight > dp[node]) continue;
            for (const auto& [neighbor, w1]: g1[node]){
                if (weight + w1 < dp[neighbor]){
                    dp[neighbor] = weight + w1;
                    heap.push(make_pair(dp[neighbor], neighbor));
                }
            }
        }
        bad.emplace_back(dp);
    }
    while (q--){
        int u,v; cin>>u>>v;--u;--v;
        ll res = dist(u,v);
        for (int i = 0; i < rem.size(); i++){
            res = min(res, bad[i][u] + bad[i][v]);
        }
        cout << res << '\n';
    }
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