#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
int n;
string s;
const int N = 200005;
vector<ll> g[N];
ll res[N], ct[1<<20], sz[N], off[N];
int mask_ct[1<<20];
bool dead[N];
int dfs_1(int node, int parent){
    sz[node] = 1;
    for (int neighbor: g[node]){
        if (neighbor!=parent && !dead[neighbor]){
            sz[node] += dfs_1(neighbor, node);
        }
    }
    return sz[node];
}
int dfs_centroid(int node, int parent, int tot){
    for (int neighbor: g[node]){
        if (neighbor!=parent && !dead[neighbor] && sz[neighbor] > tot/2){
            return dfs_centroid(neighbor, node, tot);
        }
    }
    return node;
}
ll dfs_res(int node, int parent, int mask, int cent){
    mask^=(1<<(s[node] - 'a'));
    int ac_mask = mask^(1<<(s[cent]-'a'));
    ll add = ct[ac_mask];
    for (int i = 0; i < 20; i++){
        add += ct[ac_mask^(1<<i)];
    }
    if (mask_ct[ac_mask] <= 1){
        off[node]++;
    }
    for (int neighbor: g[node]){
        if (neighbor!=parent && !dead[neighbor]){
            add += dfs_res(neighbor, node, mask, cent);
            off[node] += off[neighbor];
            off[neighbor] = 0;
        }
    }
    res[node] += add + off[node];
    return add;
}
void dfs(int node, int parent, int mask, bool add){
    mask^=(1<<(s[node] - 'a'));
    if (add){
        ct[mask]++;
    }
    else{
        ct[mask]--;
        off[node] = 0;
    }
    for (int neighbor: g[node]){
        if (neighbor!=parent && !dead[neighbor]){
            dfs(neighbor, node, mask, add);
        }
    }
}
void Go(int node){
    dfs_1(node, node);
    int cent = dfs_centroid(node, node, sz[node]);
    dead[cent] = true;
    for (int neighbor: g[cent]){
        if (dead[neighbor]) continue;
        dfs(neighbor, neighbor, 0, true);
    }
    ll tot = 0;
    for (int neighbor: g[cent]){
        if (dead[neighbor]) continue;
        dfs(neighbor, neighbor, 0, false);
        ll x = dfs_res(neighbor, neighbor, 0, cent);
        tot += x;
        dfs(neighbor, neighbor, 0, true);
    }
    int m = 1<<(s[cent]-'a');
    res[cent] += ct[m] + tot/2;
    ll ad = 0;
    for (int i = 0; i < 20; i++){
        ad += ct[m^(1<<i)];
    }
    res[cent] += ad;
    for (int neighbor: g[cent]){
        if (dead[neighbor]) continue;
        dfs(neighbor, neighbor, 0, false);
    }
    for (int neighbor: g[cent]){
        if (!dead[neighbor]){
            Go(neighbor);
        }
    }
}
void solve(int cas){ 
    for (int i = 0; i < (1<<20); i++) mask_ct[i] = __builtin_popcount(i);
    cin>>n;
    for (int i = 0; i < n - 1; i++){
        int u,v; cin>>u>>v;
        --u;--v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    cin>>s;
    Go(0);
    for (int i = 0; i < n; i++) cout << res[i] + 1 << " ";
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
