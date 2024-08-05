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
#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
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
    int n,m;
    cin>>n>>m;
    string a,b;
    cin>>a>>b;
    vector<int> pref(m);
    for (int i = 0; i < m; i++){
        if (i>0) pref[i]+=pref[i-1];
        pref[i]+=(b[i]=='1');
    }
    ll multiplier = 1;
    int idx = m - 1;
    ll res = 0;
    for (int i = n - 1; i>=0; i--,idx--){
        int ct = idx>=0?pref[idx]:0;
        if (a[i]=='1'){
            res+=((multiplier)*(ct))%MOD2;
            res%=MOD2;
        }
        multiplier = (multiplier*2)%MOD2;
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