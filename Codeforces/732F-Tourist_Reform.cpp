#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
const int N = 400005;
vector<pair<int,int>> g[N];
vector<vector<int>> ccs[N];
int tin[N], low[N], ids[N], szs[N];
vector<int> stk;
vector<pair<int,int>> e;
vector<tuple<int,int,int>> bridges;
int id = 0, tim = 0;
void dfs(int node, int par){
    tin[node] = low[node] = tim++;
    stk.emplace_back(node);
    for (auto [neighbor, index]: g[node]){
        if (neighbor != par){
            if (tin[neighbor] != -1){
                low[node] = min(low[node], tin[neighbor]);
                if (tin[neighbor] < tin[node])
                    e[index] = make_pair(node, neighbor);
            }
            else{
                dfs(neighbor, node);
                if (low[neighbor] > tin[node]){
                    szs[id] = 1;
                    while (stk.back() != neighbor){
                        ids[stk.back()] = id;
                        szs[id]++;
                        stk.pop_back();
                    }
                    ids[stk.back()] = id++;
                    stk.pop_back();
                    bridges.emplace_back(make_tuple(node, neighbor, index));
                }
                else{
                    e[index] = make_pair(node, neighbor);
                    low[node] = min(low[node], low[neighbor]);
                }
            }
        }
    }
}
void solve(int cas){
    int n,m; cin>>n>>m;
    for (int i = 0; i < m; i++){
        int u,v; cin>>u>>v;--u;--v;
        g[u].emplace_back(make_pair(v, i));
        g[v].emplace_back(make_pair(u, i));
    }
    e.resize(m);
    for (int i = 0; i < n; i++) tin[i] = -1;
    dfs(0,0);
    while (!stk.empty()){
        szs[id]++;
        ids[stk.back()] = id;
        stk.pop_back();
    }
    id++;
    for (auto& [u, v, i]: bridges){
        ccs[ids[u]].emplace_back(vector<int> {ids[v], u, v, i});
        ccs[ids[v]].emplace_back(vector<int> {ids[u], v, u, i});
    }
    int mx = 0;
    for (int i = 1; i < id; i++){
        if (szs[i] > szs[mx]) mx = i;
    }
    cout << szs[mx] << '\n';
    queue<pair<int,int>> q;
    q.push(make_pair(mx, -1));
    while (!q.empty()){
        auto [node, par] = q.front(); q.pop();
        for (auto& neighbor: ccs[node]){
            if (neighbor[0] != par){
                q.push(make_pair(neighbor[0], node));
                e[neighbor[3]] = make_pair(neighbor[2], neighbor[1]);
            }
        }
    }
    for (auto& [u, v]: e) cout << u + 1 << " " << v + 1 << '\n';
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