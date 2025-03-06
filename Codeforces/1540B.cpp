#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
template<int MODX>
struct ModInt {
  unsigned x;
  ModInt() : x(0) { }
  ModInt(signed sig) : x(((sig%MODX)+MODX)%MODX) {  }
  ModInt(signed long long sig) : x(((sig%MODX)+MODX)%MODX) { }
  int get() const { return (int)x; }
  ModInt pow(ll p) { ModInt res = 1, a = *this; while (p) { if (p & 1) res *= a; a *= a; p >>= 1; } return res; }
 
  ModInt &operator+=(ModInt that) { if ((x += that.x) >= MODX) x -= MODX; return *this; }
  ModInt &operator-=(ModInt that) { if ((x += MODX - that.x) >= MODX) x -= MODX; return *this; }
  ModInt &operator*=(ModInt that) { x = (unsigned long long)x * that.x % MODX; if (x < 0) x += MODX; return *this; }
  ModInt &operator/=(ModInt that) { return (*this) *= that.pow(MODX - 2); }
 
  ModInt operator+(ModInt that) const { return ModInt(*this) += that; }
  ModInt operator-(ModInt that) const { return ModInt(*this) -= that; }
  ModInt operator*(ModInt that) const { return ModInt(*this) *= that; }
  ModInt operator/(ModInt that) const { return ModInt(*this) /= that; }
  bool operator<(ModInt that) const { return x < that.x; }
  friend ostream& operator<<(ostream &os, ModInt a) { os << a.x; return os; }
};
typedef ModInt<MOD> mint;
class Combinations {
public:
  vector<mint> inv, fact, ifact;
 
  Combinations(int N) {
    inv.resize(N+10), fact.resize(N+10), ifact.resize(N+10);
    inv[1] = fact[0] = fact[1] = ifact[0] = ifact[1] = 1;
    for(int i=2;i<=N;++i) {
      inv[i] = inv[MOD%i] * (MOD - MOD/i);
      fact[i] = fact[i-1]*i;
      ifact[i] = ifact[i-1]*inv[i];
    }
  }
  // a > b
  mint comb(ll a, ll b) {
    if(a < b) return mint(0);
    return fact[a] * ifact[b] * ifact[a-b];
  }
  mint perm(ll a, ll b){
      if (a < b) return mint(0);
      return fact[a]*ifact[a-b];
  }
};
Combinations c(300005);
void solve(int cas){
    int n; cin>>n;
    vector<vector<ll>> g(n);
    for (int i = 0; i < n - 1; i++){
        int u,v; cin>>u>>v;
        --u;--v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    int tim = 0;
    vector<vector<ll>> jump(n, vector<ll> (20));
    vector<ll> depths(n), start(n), end(n);
    auto dfs = [&] (auto&& self, int node, int parent, int depth) -> void{
        jump[node][0] = parent;
        for (int j = 1; j < 20; j++){
            jump[node][j] = jump[jump[node][j-1]][j-1];
        }
        depths[node] = depth;
        start[node] = tim++;
        for (int neighbor: g[node]){
            if (neighbor!=parent){
                self(self,neighbor,node,depth+1);
            }
        }
        end[node] = tim;
    };
    dfs(dfs,0,0,0);
    auto anc = [&] (int u, int v) -> bool{
        return start[u] <= start[v] && end[u] >= end[v];
    };
    auto sanc = [&] (int u, int v) -> bool{
        return u!=v && anc(u, v);
    };
    auto lca = [&] (int u, int v) -> int{
        if (depths[u] > depths[v]) swap(u, v);
        if (anc(u, v)) return u;
        for (int i = 19; i >= 0; i--){
            if (!anc(jump[u][i], v)) u = jump[u][i];
        }
        return jump[u][0];
    };
    auto dist = [&] (int u, int v) -> int{
        return depths[u] + depths[v] - 2*depths[lca(u,v)];
    };
    vector<vector<int>> lcas(n, vector<int> (n));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            lcas[i][j] = lca(i, j);
        }
    }
    vector<vector<mint>> dp(n, vector<mint> (n));
    for (int i = 1; i < n; i++){
        dp[0][i] = 1;
    }
    for (int i = 1; i < n; i++){
        for (int j = 1; j < n; j++){
            dp[i][j] = (dp[i-1][j] + dp[i][j-1])/mint(2);
        }
    }
    mint res = 0;
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            mint curr = 0;
            int l = lcas[i][j];
            int idist = depths[i] - depths[l], jdist = depths[j] - depths[l];
            int tot = idist + jdist;
            for (int k = 0; k < n; k++){
                int jk = lcas[j][k];
                int ik = lcas[i][k];
                mint ad = 0;
                if (!sanc(l, jk) && !sanc(l, ik)){
                    ad = dp[jdist][idist];
                }
                else if (sanc(l, jk)){
                    int nj = depths[j] - depths[jk];
                    ad = dp[nj][tot-nj];
                }
                else{
                    int nj = jdist + depths[ik] - depths[l];
                    ad = dp[nj][tot-nj];
                }
                curr += ad;
            }
            res += curr/mint(n);
        }
    }
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
