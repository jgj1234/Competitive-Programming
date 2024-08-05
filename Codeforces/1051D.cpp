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
    int n,k;
    cin>>n>>k;
    vector<vector<vector<vector<int>>>> dp(n, vector<vector<vector<int>>>(k + 1, vector<vector<int>>(2, vector<int>(2, -1))));
    auto dfs = [&] (auto&& self, int i, int cc, bool l1, bool l2) -> int{
        if (cc>k) return 0;
        if (i==n) return cc==k;
        if (dp[i][cc][l1][l2]!=-1) return dp[i][cc][l1][l2];
        if (i==0){
            int res = 0;
            for (int c1 = 0; c1 < 2; c1++){
                for (int c2 = 0; c2 < 2; c2++){
                    int numcc = c1!=c2?2:1;
                    res+=self(self,i+1,numcc,c1,c2);
                    res%=MOD2;
                }
            }
            return dp[i][cc][l1][l2] = res;
        }
        int res = 0;
        for (int c1 = 0; c1 < 2; c1++){
            for (int c2 = 0; c2 < 2; c2++){
                int numcc = 2;
                if (c1==l1 || c1==c2) numcc--;
                if (c2==l2 || c1==c2) numcc--;
                if (c1==c2 && c1!=l1 && c1!=l2) numcc++;
                res+=self(self,i+1,cc+numcc,c1,c2);
                res%=MOD2;
            }
        }
        return dp[i][cc][l1][l2] = res;
    };
    cout<<dfs(dfs,0,0,0,0)<<endl;
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