#include <bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
struct Edge{
    int u, v; ll cap;
    Edge(int a, int b, ll c){
        u = a; v = b; cap = c;
    }
};
struct Dinic{
    vector<Edge> edges;
    vector<int> ptr, level;
    vector<vector<int>> g;
    int m = 0, n;
    Dinic(int nn){
        n = nn;
        ptr.resize(n);
        level.resize(n, -1);
        g.resize(n);
    }
    void add_edge(int a, int b, ll c){
        edges.emplace_back(Edge(a, b, c));
        edges.emplace_back(Edge(b, a, 0));
        g[a].emplace_back(m);
        g[b].emplace_back(m + 1);
        m += 2;
    }
    bool bfs(){
        fill(level.begin(), level.end(), -1);
        level[0] = 0;
        queue<int> q;
        q.push(0);
        while (!q.empty()){
            int node = q.front(); q.pop();
            for (int idx: g[node]){
                Edge e = edges[idx];
                if (e.cap == 0) continue;
                if (level[e.v] != -1) continue;
                level[e.v] = level[node] + 1;
                q.push(e.v);
            }
        }
        return level[n - 1] != -1;
    }
    ll dfs(int node, ll mn){
        if (node == n - 1) return mn;
        if (mn == 0) return 0;
        for (int& i = ptr[node]; i < g[node].size(); i++){
            Edge e = edges[g[node][i]];
            if (e.cap == 0 || level[e.v] != level[e.u] + 1) continue;
            ll x = dfs(e.v, min(mn, e.cap));
            if (x){
                edges[g[node][i]].cap -= x;
                edges[g[node][i] ^ 1].cap += x;
                return x;
            }
        }
        return 0;
    }
    ll max_flow(){
        ll res = 0;
        while (bfs()){
            fill(ptr.begin(), ptr.end(), 0);
            while (1){
                ll x =  dfs(0, LLONG_MAX);
                if (!x) break;
                res += x;
            }
        }
        return res;
    }
    void reset(){
        for (int i = 0; i < m; i += 2){
            edges[i].cap += edges[i + 1].cap;
            edges[i + 1].cap = 0;
        }
    }
};
int sink[6], src[1 << 6];
void solve(int cas){  
    string s; cin>>s;
    int n = s.size();
    Dinic d(72);
    for (int i = 0; i < (1 << 6); i++){
        for (int j = 0; j < 6; j++){
            if (i & (1 << j)){
                d.add_edge(i + 1, (1 << 6) + j + 1, LLONG_MAX);
            }
        }
    }
    vector<int> ct(6);
    for (int i = 0; i < n; i++){
        ct[s[i] - 'a']++;
    }
    for (int i = 0; i < 6; i++){
        sink[i] = d.m;
        d.add_edge((1 << 6) + i + 1, 71, ct[i]);
    }
    vector<int> mask_ct(1 << 6), mask(n, (1 << 6) - 1);
    int q; cin>>q;
    mask_ct[(1 << 6) - 1] = n - q;
    for (int i = 0; i < q; i++){
        int p; cin>>p;
        --p;
        mask[p] = 0;
        string f; cin>>f;
        for (int j = 0; j < f.size(); j++){
            mask[p] |= (1 << (f[j] - 'a'));
        }
        mask_ct[mask[p]]++;
    }
    for (int i = 0; i < (1 << 6); i++){
        src[i] = d.m;
        d.add_edge(0, i + 1, mask_ct[i]);
    }
    string res(n, 'z');
    if (d.max_flow() != n){
        cout << "Impossible\n";
        return;
    }
    d.reset();
    for (int i = 0; i < n; i++){
        d.edges[src[mask[i]]].cap--;
        for (int j = 0; j < 6; j++){
            if (mask[i] & (1 << j)){
                if (d.edges[sink[j]].cap == 0) continue;
                d.edges[sink[j]].cap--;
                if (d.max_flow() == n - 1 - i){
                    res[i] = 'a' + j;
                    d.reset();
                    break;
                }
                d.reset();
                d.edges[sink[j]].cap++;
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