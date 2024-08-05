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
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    vector<vector<int>> dp (n,vector<int> (5,-1));
    auto dfs = [&] (auto&& self, int row, int lc) -> int{
        if (row==n) return 0;
        if (dp[row][lc]!=-1) return dp[row][lc];
        if (nums[row]==0){
            return dp[row][lc] = self(self,row+1,0);
        }
        int nc = nums[row];
        if (lc && nums[row]>=lc-2){
            nc = max(0,nc-min(2,nums[row]-(lc-2)));
        }
        int res = nc?1+self(self,row+1,0):self(self,row+1,0);
        if (lc==0 && nums[row]<=2){
            res = min(res,1+self(self,row+1,2));
        }
        if (lc==2 && nums[row]<=4){
            res = min(res,1+self(self,row+1,4));
        }
        if (lc==4 && nums[row]<=4){
            res = min(res,1+self(self,row+1,2));
        }
        return dp[row][lc] = res;
    };
    cout<<dfs(dfs,0,0)<<endl;
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