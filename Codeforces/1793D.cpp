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
void solve(){
    ll n;
    cin>>n;
    vector<ll> idx1 (n+1), idx2(n+1);
    for (int i = 0; i < n; i++){
        ll a;
        cin>>a;
        idx1[a]=i;
    }
    for (int i = 0; i < n; i++){
        ll a;
        cin>>a;
        idx2[a]=i;
    }
    ll mn = min(idx1[1],idx2[1]), mx = max(idx1[1],idx2[1]);
    ll res = mn*(mn+1)/2 + ((n-1-mx)*(n-1-mx+1)/2) + (mx-mn-1)*(mx-mn)/2+1;
    for (ll i = 2; i<=n; i++){
        if ((mn<=idx1[i] && idx1[i]<=mx) || (mn<=idx2[i] && idx2[i]<=mx)){
            mx = max(mx,max(idx1[i],idx2[i]));
            mn = min(mn,min(idx1[i],idx2[i]));
        }
        else{
            ll m1 = min(idx1[i],idx2[i]);
            ll m2 = max(idx1[i],idx2[i]);
            if (m2<mn){
                ll l = mn-m2;
                ll r = n-mx;
                res+=l*r;
            }
            else if (m1>mx){
                ll l = mn+1;
                ll r = m1-mx;
                res+=l*r;
            }
            else{
                ll l = mn-m1;
                ll r = m2-mx;
                res+=l*r;
            }
            mn = min(mn, m1);
            mx = max(mx, m2);
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