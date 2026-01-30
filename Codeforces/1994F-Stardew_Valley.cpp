#include <bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
void solve(int cas){  
    int n,m; cin>>n>>m;
    vector<vector<int>> aux(n);
    vector<multiset<int>> g(n);
    vector<int> npc_deg(n);
    for (int i = 0; i < m; i++){
        int u,v,c; cin>>u>>v>>c;
        --u;--v;
        if (c == 0){
            aux[u].emplace_back(v);
            aux[v].emplace_back(u);
        }
        else{
            npc_deg[u] ^= 1;
            npc_deg[v] ^= 1;
            g[u].insert(v);
            g[v].insert(u);
        }
    }
    int sm = 0;
    for (int x: npc_deg) sm += x;
    auto Go = [&] () -> void{
        vector<int> stk = {0};
        vector<int> res;
        while (!stk.empty()){
            int node = stk.back();
            if (g[node].empty()){
                res.emplace_back(node);
                stk.pop_back();
            }
            else{
                int nxt = *g[node].begin();
                stk.emplace_back(nxt);
                g[node].erase(g[node].begin());
                g[nxt].erase(g[nxt].lower_bound(node));
            }
        }
        reverse(res.begin(), res.end());
        cout << (int) res.size() - 1 << '\n';
        for (int x: res) cout << x + 1 << ' ';
        cout << '\n';
    };
    if (sm == 0){
        cout << "YES\n";
        Go();
        return;
    }
    vector<bool> vis(n);
    int bad = 0;
    auto Dfs = [&] (auto&& self, int node, int par) -> int{
        int sm = par != -1;
        vis[node] = 1;
        for (int neighbor: aux[node]){
            if (neighbor != par && !vis[neighbor]){
                sm ^= self(self, neighbor, node);
            }
        }
        if (sm != npc_deg[node]){
            if (par == -1){
                bad = 1;
                return 0;
            }
        }
        else if (par != -1){
            g[node].insert(par);
            g[par].insert(node);
        }
        return sm == npc_deg[node];
    };
    for (int i = 0; i < n; i++){
        if (!vis[i]){
            Dfs(Dfs, i, -1);
            if (bad){
                cout << "NO\n";
                return;
            }
        }
    }
    cout << "YES\n";
    Go();
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