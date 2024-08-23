//Problem Link: https://codeforces.com/contest/960/problem/E
#include <bits/stdc++.h>
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
void solve(){
    int n;
    cin>>n;
    vector<ll> nums(n);
    for (auto& i: nums) cin>>i;
    vector<vector<int>> nodeMap(n);
    for (int i = 0; i < n - 1; i++){
        int a,b;
        cin>>a>>b;
        --a;--b;
        nodeMap[a].emplace_back(b);
        nodeMap[b].emplace_back(a);
    }
    vector<int> even(n,1), odd(n), sz(n);
    auto dfs1 = [&] (auto&& self, int node, int parent) -> int{
        int res = 1;
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                res+=self(self,neighbor,node);
                odd[node]+=even[neighbor];
                even[node]+=odd[neighbor];
            }
        }
        return sz[node] = res;
    };
    dfs1(dfs1,0,0);
    auto dfs2 = [&] (auto&& self, int node, int parent, int e, int o) -> mint{
        mint res = nums[node]*(e*sz[node] - o*sz[node] + 1);
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                //inside to inside
                res+=nums[node]*((even[node]-odd[neighbor])*sz[neighbor]-(odd[node]-even[neighbor])*sz[neighbor]);
                res+=nums[node]*(odd[neighbor]-even[neighbor]);
                //inside to outside
                res+=nums[node]*(odd[neighbor]*(n-sz[node])-even[neighbor]*(n-sz[node]));
                res+=self(self, neighbor, node, o+(odd[node]-even[neighbor]), e+(even[node]-odd[neighbor]));
            }
            else{
                res+=nums[node]*(n-sz[node]);
            }
        }
        return res;
    };
    cout<<dfs2(dfs2,0,0,0,0)<<endl;
}
int main(){
    int t=1;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //cin>>t;
    while (t--){
        solve();
    }
}