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
Combinations c(505);
void solve(int cas){ 
    string s; cin>>s;
    int n = s.size();
    vector<vector<int>> dp(n, vector<int> (n,-1));
    auto dfs = [&] (auto&& self, int l, int r) -> mint{
        if ((r-l+1)%2==1) return 0;
        if (l >= r) return 1;
        if (dp[l][r]!=-1) return mint(dp[l][r]);
        mint res = 0;
        int sz = (r - l + 1)/2;
        for (int i = l + 1; i <= r; i++){
            if (s[l] == s[i]){
                mint leftWays = self(self,l+1,i-1);
                mint rightWays = self(self,i+1,r);
                int leftSz = (i - (l + 1))/2 + 1;
                if (leftWays.x > 0 && rightWays.x > 0){
                    res += c.comb(sz, leftSz)*leftWays*rightWays;
                }
            }
        }
        return dp[l][r] = res.x;
    };
    cout << dfs(dfs,0,n-1) << '\n';
}
int main(){
    int t=1;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //cin>>t;
    for (int i = 1; i<=t; i++){
        solve(i);
    }
    return 0;
}