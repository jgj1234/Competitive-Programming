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
    int n,m;
    cin>>n>>m;
    vector<vector<int>> dp (m,vector<int> (1<<n,-1));
    auto generate = [&](auto self, int i, int currMask, int bitmask, vector<int>& res) ->void {
        if (i==n){
            res.emplace_back(currMask);
            return;
        }
        bool c = (bitmask&(1<<i))!=0;
        bool d = (i+1<n && (bitmask&(1<<(i+1)))!=0);
        if (c){
            self(self,i+1,currMask,bitmask,res);
            return;
        }
        if (i+1<n && !d){
            self(self,i+2,currMask,bitmask,res);
        }
        self(self,i+1,currMask|(1<<i),bitmask,res);
    };
    auto dfs = [&] (auto self, int column, int bitmask) -> int{
        if (column==m){
            if (bitmask!=0) return 0;
            return 1;
        }
        if (dp[column][bitmask]!=-1) return dp[column][bitmask];
        vector<int> res;
        generate(generate,0,0,bitmask,res);
        int ans = 0;
        for (int mask: res){
            ans+=self(self,column+1,mask);
            ans%=MOD;
        }
        return dp[column][bitmask]=ans;
    };
    cout<<dfs(dfs,0,0)<<endl;
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