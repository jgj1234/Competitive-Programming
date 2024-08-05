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
#define pld pair<long long,double>
#define pibb pair<int,<bool,bool>>
#define yes "YES"
#define no "NO"
#define ll long long
#define MOD 1000000007
using namespace std;
struct SparseTable{
   vector<vector<int>> table;
   SparseTable(vector<int> nums){
      table.resize(20,vector<int> (nums.size()));
      for (int i = 0; i < nums.size(); i++){
         table[0][i]=nums[i];
      }
      for (int j = 1; j < table.size(); j++){
         for (int i = 0; i+(1<<j)<=nums.size(); i++){
            table[j][i]=min(table[j-1][i],table[j-1][i+(1<<(j-1))]);
         }
      }
   }
   int query(int left, int right){
      int length = right-left+1;
      int power = length ? __builtin_clzll(1) - __builtin_clzll(length) : -1;
      return min(table[power][left],table[power][right-(1<<power)+1]);
   }
};
void solve(){
   int n,q;
   cin>>n>>q;
   vector<int> a(n);
   for (int i = 0; i < n; i++) cin>>a[i];
   SparseTable st(a);
   for (int i = 0; i < q; i++){
      int l,r;
      cin>>l>>r;
      cout<<st.query(l-1,r-1)<<endl;
   }
 
}
int main(){
   int t=1;
   //cin>>t;
   while (t--){
      solve();
   }
}