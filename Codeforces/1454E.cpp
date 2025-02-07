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

void solve(int cas){ 
    int n; cin>>n;
    vector<vector<ll>> g(n);
    for (int i = 0; i < n; i++){
        int u,v; cin>>u>>v;
        --u;--v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    vector<bool> cycle(n);
    vector<int> last(n,-1);
    last[0] = 0;
    int start = -1;
    auto dfs = [&] (auto&& self, int node, int parent) -> bool{
        for (int neighbor: g[node]){
            if (neighbor==parent) continue;
            if (last[neighbor]!=-1){
                int curr = node;
                cycle[curr] = true;
                while (curr!=neighbor){
                    curr = last[curr];
                    cycle[curr] = true;
                }
                return true;
            }
            last[neighbor] = node;
            if (self(self,neighbor,node)) return true;
        }
        return false;
    };
    dfs(dfs,0,0);
    auto dfs1 = [&] (auto&& self, int node, int parent) -> int{
        int res = 1;
        for (int neighbor: g[node]){
            if (neighbor!=parent && !cycle[neighbor]){
                res += self(self,neighbor,node);
            }
        }
        return res;
    };
    vector<ll> csz;
    for (int i = 0; i < n; i++){
        if (cycle[i]){
            csz.emplace_back(dfs1(dfs1,i,i));
        }
    }
    ll res = 0;
    ll sm = accumulate(all(csz), 0LL);
    for (ll x: csz){
        sm-=x;
        res += x*(x-1)/2 + (2*x*sm);
    }
    cout << res << '\n';
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
