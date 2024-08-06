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

void add(int& a, int b){
    a+=b;
    if (a>=MOD) a-=MOD;
}
void solve(){
    int n,k;
    cin>>n>>k;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    vector<vector<int>> dp (n,vector<int> (1<<6,-1));
    auto dfs =[&] (auto&& self, int i, int bitmask) -> int{
        if (i==n){
            return bitmask!=-1 && __builtin_popcount(bitmask)==k;
        }
        if (bitmask!=-1 && dp[i][bitmask]!=-1) return dp[i][bitmask];
        int res = self(self,i+1,bitmask);
        int nb = nums[i];
        if (bitmask!=-1) nb = bitmask&nums[i];
        add(res,self(self,i+1,nb));
        if (bitmask==-1) return res;
        return dp[i][bitmask]=res;
    };
    cout<<dfs(dfs,0,-1)<<endl;
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