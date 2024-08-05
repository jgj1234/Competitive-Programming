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
void solve(){
   int n,m;
   cin>>n>>m;
   ll max_value = (ll)(1e9);
   vector<vector<pii>> nodeMap (n);
   for (int i = 0; i < n - 2; i++){
      nodeMap[i].emplace_back(pii(i+1,1));
   }
   int currWeight = n-2;
   int add = 800677-currWeight;
   nodeMap[n-2].emplace_back(pii(n-1,add));
   currWeight+=add;
   m-=n-1;
   int x = 0;
   while (m){
      for (int i = x + 2; i < n; i++){
         nodeMap[x].emplace_back(pii(i,max_value));
         if (--m==0) break;
      }
      x++;
   }
   cout<<currWeight<<" "<<currWeight<<endl;
   for (int i = 0; i < n; i++){
      for (auto& [j,w]: nodeMap[i]){
         cout<<i+1<<" "<<j+1<<" "<<w<<endl;
      }
   }
}
int main(){
   int t=1;
   //cin>>t;
   while (t--){
      solve();
   }
}