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

class Combinations {
public:
  vector<ll> fac;
 
  Combinations(ll N) {
      fac.resize(N+1,1);
      for (int i = 2; i <= N; i++){
          fac[i]=i*fac[i-1];
      }
  }
  // a > b
  ll comb(ll a, ll b) {
    if (a<b || b<0){
        return 0;
    }
    return fac[a]/(fac[b]*(fac[a-b]));
  }
};
Combinations c(18);
void solve(){
    string s;
    cin>>s;
    int n = s.size();
    vector<ll> ct(10);
    for (int i = 0; i < n; i++) ct[s[i]-'0']++;
    int mn = 0;
    for (int i = 0; i < 10; i++){
        mn+=(ct[i]>0);
    }
    auto dfs = [&] (auto&& self, int i, int left) -> ll{
        if (left<0) return 0;
        if (i==10) return left==0;
        if (ct[i]==0){
            return self(self,i+1,left);
        }
        if (i==0){
            ll res = 0;
            for (int x = 1; x <= ct[i]; x++){
                if (x>left-1) break;
                res+=c.comb(left-1,x)*self(self,i+1,left-x);
            }
            return res;
        }
        ll res = 0;
        for (int x = 1; x <= ct[i]; x++){
            res+=c.comb(left,x)*self(self,i+1,left-x);
        }
        return res;
    };
    ll res = 0;
    for (int j = mn; j <= s.size(); j++){
        res+=dfs(dfs,0,j);
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