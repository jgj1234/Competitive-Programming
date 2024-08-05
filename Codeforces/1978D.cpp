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
    ll n,c;
    cin>>n>>c;
    vector<ll> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    vector<ll> pref (n, -1);
    ll mx = nums[0];
    for (int i = 1; i < n; i++){
        pref[i]=mx;
        mx = max(mx, nums[i]);
    }
    vector<ll> sfx(n, -1);
    mx = nums[n-1];
    for (int i = n - 2; i>=0 ;i--){
        sfx[i]=mx;
        mx = max(mx,nums[i]);
    }
    vector<ll> res(n);
    if (nums[0]+c<*max_element(nums.begin(),nums.end())) res[0]=1;
    ll pre=nums[0]+c;
    for (int i = 1; i < n; i++){
        pre+=nums[i];
        ll x = 0;
        bool p = false;
        if (nums[0]+c>=nums[i] || pref[i]>=nums[i]){
            x=i;p=true; nums[i]=pre;
        }
        if (sfx[i]>nums[i]){
            if (!p && pre>=sfx[i]){
                x+=i;
            }
            else{
                x++;
                if (!p) x+=i;
            }
        }
        res[i]=x;
    }
    for (int i = 0; i < n; i++) cout<<res[i]<<" ";
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