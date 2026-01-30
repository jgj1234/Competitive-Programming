#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
const int N = 105, V = 200005;
struct Card{
    ll p,c,l;
} cards[N];
bool prime[V];
int n,k;
struct Edge{
    ll v, cap;
    Edge(ll to, ll capacity){
        v = to; cap = capacity;
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
        edges.emplace_back(Edge(b, cap));
        edges.emplace_back(Edge(a, 0));
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
bool Check(int mid){
    Dinic d(n + 2);
    ll tot = 0, mx1 = 0, idx1 = -1;
    for (int i = 0; i < n; i++){
        if (cards[i].l <= mid){
            if (cards[i].c == 1){
                if (cards[i].p > mx1){
                    idx1 = i;
                    mx1 = cards[i].p;
                }
            }
            else{
                tot += cards[i].p;
            }
        }
    }
    for (int i = 0; i < n; i++){
        if (cards[i].l <= mid){
            if (cards[i].c == 1){
                if (i == idx1){
                    d.add_edge(0, i + 1, mx1);
                }
            }
            else{
                if (cards[i].c % 2 == 0){
                    d.add_edge(i + 1, n + 1, cards[i].p);
                }
                else{
                    d.add_edge(0, i + 1, cards[i].p);
                }
            }
        }
    }
    for (int i = 0; i < n; i++){
        if (cards[i].c % 2 == 0 || (cards[i].c == 1 && i != idx1) || cards[i].l > mid) continue;
        for (int j = 0; j < n; j++){
            if (j == i || cards[j].c % 2 == 1 || cards[j].l > mid) continue;
            if (prime[cards[i].c + cards[j].c]){
                d.add_edge(i + 1, j + 1, LLONG_MAX);
            }
        }
    }
    return tot + mx1 - d.max_flow() >= k;
}
void solve(int cas){
    cin>>n>>k;
    for (int i = 0; i < n; i++) cin >> cards[i].p >> cards[i].c >> cards[i].l;
    for (int i = 2; i < V; i++) prime[i] = true;
    for (int i = 2; i < V; i++){
        if (!prime[i]) continue;
        for (int j = 2; i * j < V; j++){
            prime[i*j] = false;
        }
    }
    ll tot = 0;
    int lp = 1, rp = n;
    while (lp <= rp){
        int mid = (lp + rp)/2;
        if (Check(mid)){
            rp = mid - 1;
        }
        else{
            lp = mid + 1;
        }
    }
    cout << (lp > n ? -1 : lp) << '\n';
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