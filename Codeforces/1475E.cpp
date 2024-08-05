#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#define pii pair<int,int>
#define pb push_back
#define ppii pair<int, pair<int,int>>
#define pli pair<long long,int>
#define pibb pair<int,<bool,bool>>
#define yes "YES"
#define no "NO"
#define ll long long
#define MOD 1000000007
using namespace std;

int comb(int n, int k) {
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD;
        }
    }

    return dp[n][k];
}
void solve(){
   int n,k;
   cin>>n>>k;
   vector<int> nums(n);
   for (int i = 0; i < n; i++) cin>>nums[i];
   sort(nums.begin(),nums.end());
   int ct = 0;
   int target = nums[n-k];
   for (int i = n-k; i < n; i++){
      if (nums[i]==target){
         ct++;
      }
      else{
         break;
      }
   }
   int ct1 = 0;
   for (int i = 0; i < size(nums); i++){
      if (nums[i]==target){
         ct1++;
      }
   }
   cout<<comb(ct1,ct)<<"\n";

}
int main(){
   int t;
   cin>>t;
   while (t--){
      solve();
   }
}