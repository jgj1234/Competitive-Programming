#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
const int N = 100005;
ll n,m,res;
vector<pair<ll,ll>> g[N];
bool dead[N];
ll sz[N];
ll inv[N], pw10[N];
map<ll,ll> pmp;
int dfs_1(int node, int parent) {
    sz[node] = 1;
    for (auto [neighbor, _]: g[node]) {
        if (neighbor != parent && !dead[neighbor]) {
            sz[node] += dfs_1(neighbor, node);
        }
    }
    return sz[node];
}

int dfs_centroid(int node, int parent, int tot) {
    for (auto [neighbor, _]: g[node]) {
        if (neighbor != parent && !dead[neighbor] && sz[neighbor] > tot / 2) {
            return dfs_centroid(neighbor, node, tot);
        }
    }
    return node;
}
void pref_dfs(int node, int parent, ll p, int add, int depth){
    pmp[p] += add;
    for (auto [neighbor, dig]: g[node]){
        if (neighbor!=parent && !dead[neighbor]){
            pref_dfs(neighbor, node,(p + (pw10[depth]*dig)%m)%m, add, depth + 1);
        }
    }
}
void suff_dfs(int node, int parent, int depth, ll md){
    ll want = ((-1*md + m)%m*inv[depth])%m;
    res += pmp[want];
    if (md==0) res++;
    for (auto [neighbor, dig]: g[node]){
        if (neighbor!=parent && !dead[neighbor]){
            suff_dfs(neighbor, node, depth + 1, ((md*10)%m + dig)%m);
        }
    }
}
void Go(int node) {
    dfs_1(node, node);
    int cent = dfs_centroid(node, node, sz[node]);
    dead[cent] = true;
    for (auto [neighbor, dig]: g[cent]){
        if (!dead[neighbor])
            pref_dfs(neighbor, cent, dig%m,1,1);
    }
    res += pmp[0];
    for (auto [neighbor, dig]: g[cent]){
        if (!dead[neighbor]){
            pref_dfs(neighbor, cent, dig%m, -1,1);
            suff_dfs(neighbor, cent, 1, dig%m);
            pref_dfs(neighbor, cent, dig%m, 1,1);
        }
    }
    pmp.clear();
    for (auto [neighbor, _]: g[cent]) {
        if (!dead[neighbor]) {
            Go(neighbor);
        }
    }
}
ll pw(ll a, ll b, ll md){
    //a^b mod m
    a%=m;
    ll ans = 1, mul = a;
    while (b){
        if (b&1) ans=(ans*mul)%md;
        mul=(mul*mul)%md;b>>=1;
    }
    return ans;
}
tuple<ll,ll,ll> extGCD(ll a, ll b){
    if (b==0) return make_tuple(a, 1, 0);
    auto [g, x1, y1] = extGCD(b, a%b);
    return {g, y1, x1 - (a/b)*y1};
}
ll modInv(ll a, ll m){
    auto [g,x,y] = extGCD(a,m);
    x%=m;
    return (x+m)%m;
}
void solve(int cas){
    cin>>n>>m;
    for (int i = 0; i < n - 1; i++){
        ll a,b,w; cin>>a>>b>>w;
        g[a].emplace_back(make_pair(b,w));
        g[b].emplace_back(make_pair(a,w));
    }
    if (m==1){
        cout << n*(n-1) << '\n';
        return;
    }
    ll inverse = modInv(10, m);
    inv[0] = pw10[0] = 1;
    for (int i = 1; i < N; i++){
        pw10[i] = (10*pw10[i-1])%m;
        inv[i] = (inverse*inv[i-1])%m;
    }
    Go(0);
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