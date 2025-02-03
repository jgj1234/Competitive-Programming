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
    int h,w,n; cin>>h>>w>>n;
    vector<pair<int,int>> points(n + 1);
    for (int i = 0; i < n; i++) cin>>points[i].first>>points[i].second;
    points[n] = make_pair(h,w);
    sort(all(points));
    vector<mint> dp (n + 1); //dp[i] - number of ways to visit this black cell without visiting any other black cell in the process
    for (int i = 0; i <= n; i++){
        dp[i] = c.comb(points[i].first + points[i].second - 2, points[i].first - 1);
    }
    for (int i = 0; i <= n; i++){
        for (int j = 0; j < i; j++){
            if (points[j].first <= points[i].first && points[j].second <= points[i].second){
                dp[i] -= dp[j]*c.comb(points[i].first - points[j].first + points[i].second - points[j].second, points[i].first - points[j].first);
            }
        }
    }
    cout << dp[n] << '\n';
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
