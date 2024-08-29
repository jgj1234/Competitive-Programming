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
const int MAXN = 200005;
const int MAX_LG = 19;
ll jump[MAXN][MAX_LG];
void solve(){
    ll n,k;
    cin>>n>>k;
    vector<ll> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    vector<ll> pref(2*n + 1);
    pref[1] = nums[0];
    for (int i = 2; i < pref.size(); i++){
        pref[i] = pref[i-1] + nums[(i-1)%n];
    }
    for (int i = 0; i < n; i++){
        int lp = i + 1;
        int rp = i + n;
        while (lp<=rp){
            int mid = (lp+rp)>>1;
            ll s = pref[mid] - pref[i];
            if (s<=k){
                lp = mid + 1;
            }
            else{
                rp = mid - 1;
            }
        }
        jump[i][0] = rp%n;
    }
    vector<int> mx (n,INT_MAX);
    int res = INT_MAX;
    for (int j = 1; j < MAX_LG ; j++){
        for (int i = 0; i < n; i++){
            if (mx[i]!=INT_MAX) continue;
            ll prev = jump[i][j-1];
            ll nxt = jump[prev][j-1];
            if ((prev<=i && nxt>=i) || (prev>=i && nxt<prev && nxt>=i) || (nxt<=prev && prev<=i)){
                mx[i] = min(mx[i], j);
            }
            jump[i][j] = nxt;
        }
    }
    for (int i = 0; i < n; i++){
        int curr = i;
        int r = 0;
        for (int j = mx[i]-1; j >=0; j--){
            if ((curr<=i && jump[curr][j]<i) || (curr>=i && (jump[curr][j]>curr || jump[curr][j]<i))){
                r+=(1<<j);
                curr = jump[curr][j];
            }
        }
        res = min(res,r+1);
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