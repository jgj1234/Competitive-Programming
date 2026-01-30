#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
const int N = 400005;
int jump[N][19], depth[N], tin[N], tout[N], parent[N];
vector<int> order, col, indeg, top;
vector<vector<int>> g, rev, cond;
vector<bool> vis;
int c = 0;
void add_disjunction(int a, bool aa, int b, bool bb){
    g[2*a + (1 - aa)].emplace_back(2*b + bb);
    g[2*b + (1 - bb)].emplace_back(2*a + aa);
    rev[2*b + bb].emplace_back(2*a + (1 - aa));
    rev[2*a + aa].emplace_back(2*b + (1 - bb));
}
void dfs1(int node){
    vis[node] = true;
    for (int neighbor: g[node]){
        if (!vis[neighbor]) dfs1(neighbor);
    }
    order.emplace_back(node);
}
void dfs2(int node){
    vis[node] = true;
    col[node] = c;
    for (int neighbor: rev[node]){
        if (!vis[neighbor]) dfs2(neighbor);
    }
}
void solve(int cas){
    int n,q; cin>>n>>q;
    vector<vector<int>> gg(n);
    for (int i = 0; i < n - 1; i++){
        int u,v; cin>>u>>v;
        --u;--v;
        gg[u].emplace_back(v);
        gg[v].emplace_back(u);
    }
    int timer = 0;
    auto dfs = [&] (auto&& self, int node, int par) -> void{
        if (node != par){
            depth[node] = depth[par] + 1;
            jump[node][0] = par;
        }
        parent[node] = par;
        tin[node] = timer++;
        for (int j = 1; j < 19; j++) jump[node][j] = jump[jump[node][j-1]][j-1];
        for (int neighbor: gg[node]){
            if (neighbor != par){
                self(self,neighbor,node);
            }
        }
        tout[node] = timer;
    };
    dfs(dfs,0,0);
    auto anc = [&] (int u, int v) -> bool{
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    };
    auto lca = [&] (int u, int v) -> int{
        if (depth[u] > depth[v]) swap(u, v);
        if (anc(u, v)) return u;
        for (int j = 18; j >= 0; j--){
            if (!anc(jump[u][j], v)) u = jump[u][j];
        }
        return jump[u][0];
    };
    auto path = [&] (int u, int v) -> vector<int>{
        int l = lca(u, v);
        vector<int> res;
        while (u != l){
            res.emplace_back(u);
            u = parent[u];
        }
        res.emplace_back(l);
        vector<int> p2;
        while (v != l){
            p2.emplace_back(v);
            v = parent[v];
        }
        reverse(all(p2));
        res.insert(res.end(), p2.begin(), p2.end());
        return res;
    };
    vector<pair<int,int>> q1(q);
    vector<string> q2(q);
    vector<vector<int>> paths(q), mp(n, vector<int> (26, -1));
    vector<int> masks(n), ct(n);
    for (int i = 0; i < q; i++){
        int u,v; cin>>u>>v;
        --u;--v;
        string s; cin>>s;
        q1[i] = make_pair(u, v);
        q2[i] = s;
        paths[i] = path(u, v);
        int x = s.size();
        for (int j = 0; j < x; j++){
            masks[paths[i][j]] |= (1 << (s[j] - 'a')) | (1 << (s[x - 1 - j] - 'a'));
        }
    }
    for (int i = 0; i < n; i++) ct[i] = __builtin_popcount(masks[i]);
    int tot = accumulate(ct.begin(), ct.end(), 0);
    g.resize(2* (tot + q));
    rev.resize(2* (tot + q));
    col.resize(2 * (tot + q));
    vis.resize(2 * (tot + q));
    int pref = 0;
    for (int i = 0; i < n; i++){
        int bef = 0;
        for (int j = 0; j < 26; j++){
            if (masks[i] & (1 << j)){
                mp[i][j] = pref + bef;
                bef++;
            }
        }
        for (int j = pref; j < pref + ct[i]; j++){
            for (int k = j + 1; k < pref + ct[i]; k++){
                add_disjunction(j, false, k, false);
            }
        }
        pref += ct[i];
    }
    for (int i = 0; i < q; i++){
        auto [u, v] = q1[i];
        string s = q2[i];
        vector<int> p = paths[i];
        int length = s.size();
        assert(length == (int) p.size());
        for (int i = 0; i < length; i++){
            add_disjunction(tot, false, mp[p[i]][s[i]-'a'], true);
        }
        for (int i = length - 1; i >= 0; i--){
            int op = length - 1 - i;
            add_disjunction(tot, true, mp[p[op]][s[i] - 'a'], true);
        }
        for (int i = 0; i < length/2; i++){
            if (s[length - 1 - i] != s[i]){
                add_disjunction(mp[p[i]][s[i]-'a'], false, tot, true);
                add_disjunction(mp[p[i]][s[length-1-i]-'a'], false, tot , false);
                add_disjunction(mp[p[length-1-i]][s[length-1-i]-'a'], false, tot, true);
                add_disjunction(mp[p[length-1-i]][s[i]-'a'], false, tot, false);
            }
        }
        tot++;
    }
    for (int i = 0; i < 2*tot; i++) if (!vis[i]) dfs1(i);
    reverse(order.begin(), order.end());
    for (int i = 0; i < 2*tot; i++) vis[i] = false;
    for (int i = 0; i < order.size(); i++){
        if (!vis[order[i]]){
            dfs2(order[i]);
            c++;
        }
    }
    for (int i = 0; i < 2*tot; i+=2){
        if (col[i] == col[i+1]){
            cout << "NO\n";
            return;
        }
    }
    cond.resize(c);
    indeg.resize(c);
    top.resize(c);
    cout << "YES\n";
    for (int i = 0; i < 2*tot; i++){
        for (int x: g[i]){
            if (col[i] != col[x]){
                cond[col[i]].emplace_back(col[x]);
                indeg[col[x]]++;
            }
        }
    }
    queue<int> qq;
    for (int i = 0; i < c; i++){
        if (indeg[i] == 0) qq.push(i);
    }
    int tt = 0;
    while (!qq.empty()){
        int node = qq.front(); qq.pop();
        top[node] = tt++;
        for (int neighbor: cond[node]){
            indeg[neighbor]--;
            if (indeg[neighbor] == 0) qq.push(neighbor);
        }
    }
    string res(n, '.');
    for (int i = 0; i < n; i++){
        if (ct[i] == 0){
            res[i] = 'a';
            continue;
        }
        for (int j = 0; j < 26; j++){
            if (mp[i][j] != -1){
                if (top[col[2*mp[i][j]]] < top[col[2*mp[i][j] + 1]]){
                    res[i] = 'a' + j;
                    break;
                }
            }
        }
    }
    cout << res << '\n';
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