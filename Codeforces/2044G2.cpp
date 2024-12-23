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
void solve(int cas){
    int n; cin>>n;
    vector<ll> r(n), indeg(n);
    for (auto& a: r) cin>>a, a--, indeg[a]++;
    vector<vector<int>> nodeMap(n);
    for (int i = 0; i < n; i++){
        nodeMap[r[i]].emplace_back(i);
    }
    ll res = 0;
    vector<bool> cycle(n), vis(n), vis1(n);
    vector<int> last(n);
    auto dfs = [&] (auto&& self, int node) -> int{
        vis1[node] = true;
        last[r[node]] = node;
        if (vis[r[node]]){
            vis1[node] = false;
            vis[node] = true;
            return -1;
        }
        if (vis1[r[node]]){
            vis1[r[node]] = false;
            cycle[node] = true;
            vis[node] = true;
            return node;
        }
        int x = self(self,r[node]);
        vis1[node] = false;
        vis[node] = true;
        return x;
    };
    for (int i = 0; i < n; i++){
        if (!vis[i] && indeg[i]==0){
            int c = dfs(dfs,i);
            if (c==-1) continue;
            int curr = last[c];
            while (curr!=c){
                cycle[curr] = true;
                curr = last[curr];
            }
        }
    }
    for (int i = 0; i < n; i++){
        if (!vis[i]) cycle[i] = true;
    }
    for (int i = 0; i < n; i++){
        if (cycle[i] && nodeMap[i].size() > 1){
            for (int neighbor: nodeMap[i]){
                if (!cycle[neighbor]){
                    queue<int> q;
                    q.push(neighbor);
                    ll x = 0;
                    while (!q.empty()){
                        int node = q.front();
                        q.pop();
                        x++;
                        for (int nb: nodeMap[node]){
                            if (!cycle[nb]){
                                q.push(nb);
                            }
                        }
                    }
                    res = max(res, x);
                }
            }
        }
    }
    cout << res + 2 << '\n';
}

int main(){
    int t=1;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>t;
    for (int i = 1; i<=t; i++){
        solve(i);
    }
    return 0;
}