#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <queue>
#include <iomanip>
#include <set>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <ext/pb_ds/assoc_container.hpp>
#include <cmath>
#define pii pair<int,int>
#define pi 3.14159265358979323846
#define pb push_back
#define ppii pair<int, pair<int,int>>
#define pld pair<long long,double>
#define pibb pair<int,<bool,bool>>
#define yes "YES"
#define no "NO"
#define ll long long
#define MOD 1000000007
#define all(x) x.begin(),x.end()
#define MOD2 998244353
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
#define MOD 1000000007
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
};
Combinations c(200005);
void solve(){
    int n,m;
    cin>>n>>m;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    map<ll,ll> ct;
    for (int i = 0; i < n; i++) ct[nums[i]]++;
    vector<int> copy(nums.begin(),nums.end());
    sort(all(copy));
    mint res = 0;
    copy.erase(unique(all(copy)),copy.end());
    vector<mint> prods(copy.size());
    map<ll,ll> idx;
    for (int i = 0; i < copy.size(); i++){
        idx[copy[i]]=i;
        prods[i]=ct[copy[i]];
        if (i>0) prods[i]*=prods[i-1];
    }
    for (int i = 0; i < n; i++){
        int pos = idx[nums[i]];
        int lp = 0;
        int rp = copy.size()-1;
        while (lp<=rp){
            int mid = (lp+rp)>>1;
            if (copy[mid]>=nums[i]+m){
                rp=mid-1;
            }
            else{
                lp=mid+1;
            }
        }
        int pos2=rp;
        mint ad = c.comb(pos2-pos,m-1);
        mint mul = prods[pos2]/prods[pos];
        res+=ad*mul;
    }
    cout<<res<<endl;
    
}
int main(){
   int t=1;
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   cin>>t;
   while (t--){
      solve();
   }
}