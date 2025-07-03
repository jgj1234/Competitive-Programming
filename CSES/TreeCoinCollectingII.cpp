#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
const int N = 200005;
const int LG = 17;
int tim = 0;
bool has[N];
vector<int> g[N];
int sub_ct[N], out_ct[N], tin[N], tout[N], depth[N];
pair<ll,ll> jump[N][LG];
void dfs(int node, int parent){
    tin[node] = tim++;
    if (node!=parent){
        depth[node] = depth[parent] + 1;
    }
    for (int neighbor: g[node]){
        if (neighbor != parent){
            dfs(neighbor, node);
            if (has[neighbor] || sub_ct[neighbor]){
                sub_ct[node] += 2 + sub_ct[neighbor];
            }
        }
    }
    tout[node] = tim;
}

void dfs1(int node, int parent, int pass){
    if (node && (pass || has[parent])){
        out_ct[node] = 2 + pass;
    }
    if (node){
        jump[node][0] = make_pair(parent, 1 + sub_ct[parent] - (has[node] || sub_ct[node] ? 2 + sub_ct[node]: 0));
        for (int j = 1; j < LG; j++){
            auto [l, lct] = jump[node][j-1];
            jump[node][j] = make_pair(jump[l][j-1].first, lct + jump[l][j-1].second);
        }
    }
    for (int neighbor: g[node]){
        if (neighbor!=parent){
            int curr = sub_ct[node];
            if (has[neighbor] || sub_ct[neighbor]){
                curr -= 2 + sub_ct[neighbor];
            }
            dfs1(neighbor, node, out_ct[node] + curr);
        }
    }
}
bool anc(int a, int b){
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}
int lca(int a, int b){
    if (depth[a] > depth[b]) swap(a, b);
    if (anc(a, b)) return a;
    for (int j = LG - 1; j >= 0; j--){
        if (!anc(jump[a][j].first, b)) a = jump[a][j].first;
    }
    return jump[a][0].first;
}
ll get(int u, int v){
    ll dist = depth[u] - depth[v];
    ll curr = u, res = 0;
    for (int j = LG - 1; j >= 0; j--){
        if (dist&(1<<j)){
            res += jump[curr][j].second;
            curr = jump[curr][j].first;
        }
    }
    return res;
}
int kth(int node, int k){
    for (int j = LG - 1; j >= 0; j--){
        if (k&(1<<j)) node = jump[node][j].first;
    }
    return node;
}
void solve(int cas){
    int n,q; cin>>n>>q;
    for (int i = 0; i < n; i++) cin>>has[i];
    for (int i = 0; i < n - 1; i++){
        int u,v; cin>>u>>v;
        --u;--v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs(0,0);
    dfs1(0,0,0);
    while (q--){
        int a,b; cin>>a>>b;
        --a;--b;
        if (a==b){
            cout << sub_ct[a] + out_ct[a] << '\n';
            continue;
        }
        if (depth[a] > depth[b]) swap(a, b);
        int l = lca(a, b);
        if (l == a){
            cout << out_ct[a] + get(b, a) + sub_ct[b] << '\n';
            continue;
        }
        int aanc = kth(a, depth[a] - depth[l] - 1), banc = kth(b, depth[b] - depth[l] - 1);
        ll res = 2 + out_ct[l] + sub_ct[a] + sub_ct[b] + get(a, aanc) + get(b, banc);
        ll curr = sub_ct[l];
        if (has[aanc] || sub_ct[aanc]) curr -= 2 + sub_ct[aanc];
        if (has[banc] || sub_ct[banc]) curr -= 2 + sub_ct[banc];
        cout << res + curr << '\n';
    }
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