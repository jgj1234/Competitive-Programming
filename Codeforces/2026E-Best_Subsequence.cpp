#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
struct Edge{
    ll u, v, cap;
    Edge(ll from, ll to, ll capacity){
        u = from; v = to; cap = capacity;
    }
};
struct Dinic{
    vector<vector<int>> g;
    vector<int> level, ptr;
    vector<Edge> edges;
    int ct = 0, n;
    Dinic(int tot){
        n = tot;
        level.resize(n);
        ptr.resize(n);
        g.resize(n);
    }
    void add_edge(int a, int b, ll cap){
        edges.emplace_back(Edge(a, b, cap));
        edges.emplace_back(Edge(b, a, 0));
        g[a].emplace_back(ct);
        g[b].emplace_back(ct+1);
        ct += 2;
    }
    bool bfs(){
        fill(level.begin(), level.end(), -1);
        level[0] = 0;
        queue<int> q;
        q.push(0);
        while (!q.empty()){
            int node = q.front();
            q.pop();
            for (int neighbor: g[node]){
                if (level[edges[neighbor].v] == -1 && edges[neighbor].cap > 0){
                    level[edges[neighbor].v] = level[node] + 1;
                    q.push(edges[neighbor].v);
                }
            }
        }
        return level.back() != -1;
    }
    ll dfs(int node, ll mn){
        if (mn == 0) return 0;
        if (node == n - 1) return mn;
        for (int& i = ptr[node]; i < g[node].size(); i++){
            int neighbor = g[node][i];
            ll v = edges[neighbor].v, cap = edges[neighbor].cap;
            if (level[v] != level[node] + 1) continue;
            ll res = dfs(v, min(mn, cap));
            if (res != 0){
                edges[neighbor].cap -= res;
                edges[neighbor ^ 1].cap += res;
                return res;
            }
        }
        return 0;
    }
    ll max_flow(){
        if (n == 1) return LLONG_MAX;
        ll res = 0;
        while (bfs()){
            fill(ptr.begin(), ptr.end(), 0);
            while (1){
                ll x = dfs(0, LLONG_MAX);
                if (!x) break;
                res += x;
            }
        }
        return res;
    }
};
void solve(int cas){
    int n; cin>>n;
    vector<ll> nums(n);
    for (auto& a: nums) cin>>a;
    Dinic d(n + 62);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < 60; j++){
            if (nums[i] & (1LL << j)){
                d.add_edge(i + 1, j + n + 1, LLONG_MAX);
            }
        }
    }
    for (int i = 1; i <= n; i++) d.add_edge(0, i, 1);
    for (int j = 0; j < 60; j++) d.add_edge(j + n + 1, n + 61, 1);
    cout << n - d.max_flow() << '\n';
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