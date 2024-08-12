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
    vector<ll> a(n),b(n);
    for (int i = 0; i < n; i++) cin>>a[i]>>b[i];
    vector<pair<ll,ll>> stack = {pair<ll,ll>(a[0],b[0])};
    vector<ll> res = {a[0]};
    for (int i = 1; i < n; i++){
        ll tim = 0, freq=a[i];
        while (!stack.empty()){
            auto [tt, num] = stack.back(); stack.pop_back();
            if (num==b[i]){
                tim+=tt;
            }
            else{
                tim+=min(freq,tt);
                if (freq>=tt){
                    freq-=tt;
                }
                else{
                    stack.emplace_back(tt-freq,num);
                    freq=0;
                    break;
                }
            }
        }
        tim+=freq;
        res.emplace_back(max(res.back(),tim));
        stack.emplace_back(tim,b[i]);
    }
    for (int i = 0; i < res.size(); i++){
        cout<<res[i]<<" ";
    }
    cout<<endl;
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