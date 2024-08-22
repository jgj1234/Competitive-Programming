//Problem Link: https://codeforces.com/problemset/problem/570/E
#include<bits/stdc++.h>
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
    int n,m;
    cin>>n>>m;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) cin>>grid[i];
    if (grid[0][0]!=grid[n-1][m-1]){
        cout<<0<<endl;
        return;
    }
    vector<vector<mint>> dp(n,vector<mint> (n));
    dp[0][0] = 1;
    for (int moveNum = 1; moveNum < ceil((n + m - 1)/2.0); moveNum++){
        vector<vector<mint>> curr(n,vector<mint>(n));
        for (int down = 0; down <= min(moveNum,n-1); down++){
            pii co1 (down, moveNum - down);
            if (co1.second<0 || co1.second>=m) continue;
            for (int up = 0; up <= min(moveNum,n-1); up++){
                pii co2(n-1-up,m-1-(moveNum-up));
                if (co2.first<0 || co2.second<0 || co2.second>=m || co1.first>co2.first || co1.second>co2.second||grid[co1.first][co1.second]!=grid[co2.first][co2.second]) continue;
                for (int d1 = down-1;d1<=down;d1++){
                    for (int u1 = up-1;u1<=up;u1++){
                        if (d1>=0 && u1>=0){
                            curr[down][up]+=dp[d1][u1];
                        }
                    }
                }
            }
        }
        dp = curr;
    }
    mint res = 0;
    for (int i = 0; i < dp.size(); i++){
        for (int j = 0; j < dp[0].size(); j++){
            res+=dp[i][j];
        }
    }
    cout<<res<<endl;
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