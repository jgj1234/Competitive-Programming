#include <bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
template<int MODX>
struct ModInt {
  unsigned x;
  ModInt() : x(0) { }
  ModInt(signed sig) : x(((sig%MODX)+MODX)%MODX) { }
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
typedef ModInt<MOD2> mint;

class Combinations {
public:
  vector<mint> inv, fact, ifact;
  
  Combinations(int N) {
    inv.resize(N+10), fact.resize(N+10), ifact.resize(N+10);
    inv[1] = fact[0] = fact[1] = ifact[0] = ifact[1] = 1;
    for(int i=2;i<=N;++i) {
      inv[i] = inv[MOD2%i] * (MOD2 - MOD2/i);
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
Combinations c(1000006);
mint dp[61][61];
int p[61], xset[61][61];
void solve(int cas){  
    int n,m; cin>>n>>m;
    vector<int> ct(61);
    vector<mint> pw2(1000006);
    pw2[0] = 1;
    for (int i = 1; i < pw2.size(); i++) pw2[i] = mint(2) * pw2[i - 1];
    for (int i = 0; i < n; i++){
        int x; cin>>x;
        ct[x]++;
    }
    while (m--){
        int t; cin>>t;
        if (t == 1){
            int x; cin>>x;
            ct[x]++;
        }
        else if (t == 2){
            int x; cin>>x;
            ct[x]--;
        }
        else{
            ll x; cin>>x;
            for (int i = 0; i <= 60; i++){
                p[i] = ct[i];
                if (i) p[i] += p[i - 1];
            }
            for (int i = 0; i <= 60; i++){
                for (int j = 0; j <= 60; j++){
                    dp[i][j] = 0;
                }
            }
            for (int i = 0; i < 61; i++){
                for (int j = i; j < 61; j++){
                    if (x & (1LL << j)){
                        xset[i][j] = 1;
                    }
                    else{
                        xset[i][j] = 0;
                    }
                    if (j > i) xset[i][j] &= xset[i][j - 1];
                }
            }
            for (int i = 0; i <= 60; i++){
                for (int bit = 0; bit <= i; bit++){
                    if (i == 0){
                        if (xset[0][0]){
                            dp[i][bit] = (pw2[p[i]] - mint(1));
                        }
                        else{
                            dp[i][bit] = pw2[p[i]];
                        }
                        continue;
                    }
                    if (!xset[bit][bit]){
                        if (bit == 0){
                            dp[i][bit] += pw2[p[i - 1]];
                        }
                        else{
                            dp[i][bit] += dp[i - 1][bit - 1];
                        }
                    }
                    for (int times = 1; times <= ct[i]; times++){
                        mint ways = c.comb(ct[i], times);
                        int ntight = xset[max(0, bit - times + 1)][bit];
                        if (!ntight || bit - times < 0){
                            dp[i][bit] += ways * pw2[p[i - 1]];
                        }
                        else{
                            int nxt = bit - times;
                            if (xset[nxt][nxt]) continue;
                            if (nxt - 1 < 0){
                                dp[i][bit] += ways * pw2[p[i - 1]];
                            }
                            else{
                                dp[i][bit] += ways * dp[i - 1][nxt - 1];
                            }
                        }
                    }
                    
                }
            }
            cout << dp[60][60] << '\n';
        }
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