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
    int n;
    cin>>n;
    vector<vector<ll>> nodeMap(n);
    for (int i = 0; i < n - 1; i++){
        int a,b;
        cin>>a>>b;
        --a;--b;
        nodeMap[a].emplace_back(b);
        nodeMap[b].emplace_back(a);
    }
    vector<ll> sz(n), tin(n); int tim = 0;
    auto dfs1 = [&] (auto&& self, int node, int parent) -> ll{
        tin[node] = tim++;
        int res = 1;
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                res+=self(self,neighbor,node);
            }
        }
        return sz[node] = res;
    };
    dfs1(dfs1,0,0);
    int m; cin>>m;
    vector<ll> fac(m);
    for (int i = 0; i < m; i++) cin>>fac[i];
    for (int i = 0; i < n - 1 - m; i++) fac.emplace_back(1);
    sort(all(fac));
    while (fac.size() > n - 1){
        fac[fac.size() - 2] = (fac[fac.size() - 2]*fac[fac.size()-1])%MOD;
        fac.pop_back();
    }
    vector<ll> edgect;
    for (int i = 0; i < n; i++){
        for (int x: nodeMap[i]){
            if (x > i){
                if (tin[x] <= tin[i]){
                    edgect.emplace_back(sz[i]*(n - sz[i]));
                }
                else{
                    edgect.emplace_back(sz[x]*(n-sz[x]));
                }
            }
        }
    }
    sort(all(edgect));
    ll res = 0;
    for (int i = n - 2; i >= 0; i--){
        res += (fac[i]*(edgect[i]%MOD))%MOD;
        res%=MOD;
    }
    cout<<res<<endl;
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