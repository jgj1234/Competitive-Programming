#include <iostream>
#include <vector>
#include <string>
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
void solve(){
    ll n,m;
    cin>>n>>m;
    vector<ll> a(n),c(n);
    for (int i = 0; i < n; i++) cin>>a[i];
    for (int i = 0; i < n; i++) cin>>c[i];
    map<ll,ll> ct;
    for (int i = 0; i < n; i++){
        if (a[i]<=m){
            ct[a[i]]=c[i];
        }
    }
    ll res = 0;
    for (auto [k,v]: ct){
        res = max(res, min(v,m/k)*k);
        if (ct.count(k+1)){
            ll ct1 = min(v,m/k)*k;
            ll diff = m - ct1;
            ll nv = min(diff/(k+1),ct[k+1]);
            ll left = ct[k+1]-nv;
            nv*=(k+1);
            ct1+=nv;
            res = max(res,ct1+min(min(left,min(v,m/k)),m-ct1));
        }
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