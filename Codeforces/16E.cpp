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
    int n;
    cin>>n;
    vector<vector<long double>> nums(n,vector<long double> (n));
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin>>nums[i][j];
    vector<long double> dp (1<<n);
    dp[0] = 1;
    for (int i = 1; i < (1<<n) - 1; i++){
        int bc = n - (__builtin_popcount(i)-1);
        long double prob = ((long double)(1))/((bc*(bc-1))/2);
        for (int j = 0; j < n; j++){
            if (i&(1<<j)){
                int old_mask = i^(1<<j);
                for (int k = 0; k < n; k++){
                    if ((i&(1<<k))==0){
                        dp[i]+=(dp[old_mask]*nums[k][j]*prob);
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++){
        cout<<dp[((1<<n)-1)^(1<<i)]<<" ";
    }
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
    return 0;
}