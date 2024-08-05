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
#define MOD2 998244353
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
void solve(){
    int n,k;
    cin>>n>>k;
    vector<int> nums(n);
    map<int,vector<int>> mp;
    for (int i = 0; i < n; i++) cin>>nums[i];
    for (int i = 0; i < n; i++){
        mp[nums[i]%k].emplace_back(nums[i]);
    }
    auto dfs = [&] (auto self, int i, bool skipped, vector<int>& v, vector<vector<ll>>& dp)->ll{
        if (i>=v.size()-1){
            if (!skipped){
                if (i>=v.size()){
                    return 1000000000;
                }
                return 0;
            }
            return 0;
        }
        if (dp[i][skipped]!=-1) return dp[i][skipped];
        ll res = (v[i]-v[i+1])/k+self(self,i+2,skipped,v,dp);
        if (!skipped && i+1<dp.size()){
            res=min(res,self(self,i+1,true,v,dp));
        }
        return dp[i][skipped]=res;
    };
    ll res = 0;
    int oddCount = 0;
    for (auto [x,v]: mp){
        sort(v.begin(),v.end(),greater<int>());
        if (v.size()%2==1){
            oddCount++;
            if (v.size()==1){
                continue;
            }
            vector<vector<ll>> dp (v.size(),vector<ll> (2,-1));
            ll l1 = dfs(dfs,0,false,v,dp);
            res+=l1;
        }
        else{
            for (int i = 0; i < v.size(); i+=2){
                res+=(v[i]-v[i+1])/k;
            }
        }
    }
    if ((n%2==0 && oddCount>0)|| (n%2==1 && oddCount>1)){
        cout<<-1<<endl;
    }
    else{
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