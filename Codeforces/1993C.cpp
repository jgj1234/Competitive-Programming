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
    ll n,k;
    cin>>n>>k;
    vector<ll> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    sort(all(nums));
    ll lp = nums[0];
    ll rp = nums[0]+k-1;
    for (int i = 1; i < n; i++){
        ll x1 = nums[i], x2 = nums[i] + k - 1;
        if (lp>=x1){
            if (lp>x2){
                cout<<-1<<endl;
                return;
            }
            rp = min(rp,x2);
            continue;
        }
        else if (rp>=x1){
            rp=min(rp,x2);
            lp=max(lp,x1);
            continue;
        }
        ll dist = ceil((x1-rp)/(2.0*k));
        lp+=2*k*dist;
        rp+=2*k*dist;
        if (lp>x2 || rp<x1){
            cout<<-1<<endl;
            return;
        }
        lp = max(lp,x1);
        rp = min(rp,x2);
    }
    cout<<lp<<endl;
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