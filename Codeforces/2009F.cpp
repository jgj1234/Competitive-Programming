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
    ll n,q;
    cin>>n>>q;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin>>a[i];
    vector<ll> pref(n+1);
    for (int i = 1; i<=n; i++) pref[i] = pref[i-1] + a[i-1];
    ll sm = pref[n];
    auto findsm = [&] (ll left, ll right, ll cycles) -> ll{
        left = ((left + cycles) + n)%n;
        right = ((right + cycles) + n)%n;
        if (left > right){
            return (pref[n] - pref[left]) + pref[right + 1];
        }
        return pref[right + 1] - pref[left];
    };
    while (q--){
        ll l,r;
        cin>>l>>r;
        --l;--r;
        ll res = 0;
        ll cycles_left = l/n;
        ll rem_left = n - (l%n);
        if (l+rem_left-1>=r){
            cout<<findsm(l%n,r%n,cycles_left)<<endl;
            continue;
        }
        res = findsm(l%n,n-1,cycles_left);
        l+=rem_left;
        ll cycles_right = r/n;
        ll rem_right = r%n;
        if (r-rem_right<=l){
            res+=findsm(l%n,r%n, cycles_right);
            cout<<res<<endl;
            continue;
        }
        res+=findsm(0,r%n, cycles_right);
        res+=sm*((r-l+1)/n - (r%n==n-1));
        cout<<res<<endl;
    }
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