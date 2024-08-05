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
#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
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
    ll n,x;
    cin>>n>>x;
    vector<ll> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    set<ll> s {1};
    int res = 1;
    for (int i = 0; i < n; i++){
        if (x%nums[i]) continue;
        ll tar = x/nums[i];
        if (s.count(tar)){
            res++;
            s={1};
        }
        vector<ll> fac;
        for (int a:s){
            ll pr = a*nums[i];
            if (x%pr==0 && !s.count(pr)){
                fac.emplace_back(pr);
            }
        }
        for (int a:fac) s.insert(a);
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