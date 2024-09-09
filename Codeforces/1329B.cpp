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
void solve(){
    ll d,m;
    cin>>d>>m;
    ll bt = 63 - __builtin_clzll(d);
    vector<ll> ct(bt+1);
    for (int i = 0; i < bt + 1; i++){
        ct[i] = 1<<i;
    }
    ct[bt] = d - (1<<bt) + 1; 
    ll res = 1;
    for (int i = 0; i < bt + 1; i++){
        res = (res)*(ct[i]+1);
        res%=m;
    }
    cout<<((res-1)+m)%m<<endl;
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