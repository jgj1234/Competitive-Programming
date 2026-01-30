#include <bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
const int N = 200005;
int spf[N], ct[64];
uint64_t xr[N];
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
mint comb[20][20];

void solve(int cas){  
    int n,k; cin>>n>>k;
    vector<ll> nums(n);
    for (auto& a: nums) cin>>a;
    vector<vector<int>> fac(n);
    for (int i = 0; i < n; i++){
        while (nums[i] > 1){
            int x = spf[nums[i]];
            fac[i].emplace_back(x);
            while  (nums[i] % x == 0) nums[i] /= x;
        }
        sort(all(fac[i]));
    }
    vector<unordered_map<uint64_t, mint>> mp(7);
    vector<mint> tot(7), pwk(13);
    pwk[0] = 0;
    for (int i = 1; i < 13; i++) pwk[i] = mint(i).pow(k);
    mint res = 0;
    for (int i = 0; i < n; i++){
        int sz = fac[i].size();
        vector<uint64_t> subs(1 << sz);
        for (int mask = 1; mask < (1 << sz); mask++){
            uint64_t cxr = 0;
            for (int j = 0; j < sz; j++){
                if ((mask >> j) & 1) cxr^=xr[fac[i][j]];
            }
            subs[mask] = cxr;
        }
        for (int j = 1; j <= 6; j++){
            vector<mint> sm(7);
            for (int x = 1; x < (1 << sz); x++){
                sm[ct[x]] += mp[j][subs[x]];
            }
            mint got = 0;
            for (int x = 1; x <= j; x++){
                mint curr = 0;
                for (int y = x; y <= j; y++){
                    if ((y - x) % 2 == 0){
                        curr += comb[y][x] * sm[y];
                    }
                    else{
                        curr -= comb[y][x] * sm[y];
                    }
                }
                res += pwk[j + sz - x] * curr;
                got += curr;
            }
            res += pwk[j + sz] * (tot[j] - got); // disjoint
        }
        if (sz)
            res += pwk[sz]* tot[0];
        for (int j = 1; j < (1 << sz); j++){
            mp[sz][subs[j]]+=1;
        }
        tot[sz]+=1;
    }
    cout << res << '\n';
}
void pre(){
    for (int i = 0; i < 20; i++){
        comb[i][0] = 1;
    }
    for (int i = 1; i < 20; i++){
        for (int j = 1; j < 20; j++){
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
        }
    }
    for (int i = 0; i < 64; i++) ct[i] = __builtin_popcount(i);
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<uint64_t> dist;
    memset(spf, -1, sizeof(spf));
    for (int i = 2; i < N; i++){
        if (spf[i] == -1){
            xr[i] = dist(gen);
            for (int j = i; j < N; j += i){
                if (spf[j] == -1) spf[j] = i;
            }
        }
    }
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