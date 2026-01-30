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
long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
const int N = 200005;
mint pw2[N];
void pre(){
    pw2[0] = 1;
    for (int i = 1; i < N; i++) pw2[i] = pw2[i-1]*2;
}
void solve(int cas){ 
    int n; cin>>n;
    vector<ll> nums(n);
    for (auto& a: nums) cin>>a;
    vector<ll> ct(n + 1);
    for (int i = 0; i < n; i++) ct[nums[i]]++;
    vector<vector<mint>> dp(n + 1);
    ll mn = INT_MAX;
    for (int i = 0; i < n; i++){
        mn = min(mn, ct[i]);
        dp[i].resize(mn + 1);
    }
    for (int i = 0; i <= ct[0]; i++){
        dp[0][i] = c.comb(ct[0], i);
    }
    for (int i = 1; i < n; i++){
        vector<mint> lsuff(dp[i-1].size());
        for (int j = dp[i-1].size() - 1; j >= 0; j--){
            lsuff[j] = dp[i-1][j];
            if (j + 1 < dp[i-1].size()) lsuff[j] += lsuff[j+1];
        }
        vector<mint> csuff(ct[i] + 1);
        for (int j = ct[i]; j > 0; j--){
            csuff[j] = c.comb(ct[i], j);
            if (j!=ct[i]) csuff[j] += csuff[j+1];
        }
        for (int j = dp[i].size() - 1; j > 0; j--){
            if (j!=lsuff.size() - 1) dp[i][j] = c.comb(ct[i], j)*lsuff[j+1];
            dp[i][j] += dp[i-1][j]*csuff[j];
        }
    }
    vector<ll> suffct(n);
    for (int i = n - 2; i >= 0; i--) suffct[i] = ct[i+1]+suffct[i+1];
    mint res = 0;
    for (int i = 0; i < n; i++){
        for (int j = 1; j < dp[i].size(); j++){
            res += dp[i][j]*j*pw2[suffct[i]];
        }
    }
    cout << res << '\n';
}
int main(){
    pre();
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