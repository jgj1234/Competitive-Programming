#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <ext/pb_ds/assoc_container.hpp>
 
#include <cmath>
#define pii pair<int,int>
#define pb push_back
#define ppii pair<int, pair<int,int>>
#define pld pair<long long,double>
#define pibb pair<int,<bool,bool>>
#define yes "YES"
#define no "NO"
#define ll long long
#define MOD 1000000007
#define MOD2 998244353
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

void solve(){
    ll n;
    cin>>n;
    vector<ll> nums(n);
    for (ll i = 0; i < n; i++) cin>>nums[i];
    ll res = 0;
    for (ll bit = 0; bit < 30; bit++){
        vector<ll> ct(2);
        ct[0]=1;
        bool xr = false;
        ll totalCount = 0;
        ll range = 0;
        for (ll i = 0; i < n; i++){
            if (nums[i]&(1LL<<bit)) xr=!xr;
            totalCount+=ct[!xr];
            range+=ct[!xr]*(i+1);
            ct[xr]++;
        }
        ct = {1LL,0LL}; xr = false;
        for (ll i = n - 1; i>=0; i--){
            if (nums[i]&(1LL<<bit)) xr=!xr;
            range-=ct[!xr]*(i);
            ct[xr]++;
        }
        res+=((((range+MOD2)%MOD2)*(1LL<<bit))%MOD2);
        res%=MOD2;
    }
    cout<<(res+MOD2)%MOD2<<endl;
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