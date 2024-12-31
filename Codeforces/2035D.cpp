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
void solve(int cas){  
    int n; cin>>n;
    vector<ll> nums(n), res(n);
    for (auto& a: nums) cin>>a;
    auto red = [&] (ll x) -> pair<ll,ll>{
        int ct = 0;
        while (x%2==0){
            ct++;
            x>>=1;
        }
        return pair<ll,ll>(x, ct); //without 2 factors, count
    };
    mint curr = 0;
    vector<vector<ll>> stk; //segments that move all 2s toward the last element. index, without 2 factors, count
    for (int i = 0; i < n; i++){
        int cnt = 0;
        while (!stk.empty() && (cnt > 30 || (nums[i]*(1<<cnt) >= stk.back()[1]))){
            int idx = stk.back()[0], wo2 = stk.back()[1], cnt1 = stk.back()[2];
            cnt += cnt1;
            curr -= (wo2*binpow(2,cnt1,MOD))%MOD;
            curr += wo2;
            stk.pop_back();
        }
        curr += (binpow(2, cnt, MOD)*nums[i])%MOD;
        auto [wo2, cnt1] = red(nums[i]);
        res[i] = curr.x;
        stk.emplace_back(vector<ll> {i, wo2, cnt1 + cnt});
    }
    for (auto& a: res) cout << a << ' ';
    cout << '\n';
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