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
void solve(){
   int n;
   cin>>n;
   vector<vector<int>> customers(n);
   for (int i = 0; i < n; i++){
      int a,b;
      cin>>a>>b;
      customers[i]={a,b,i};
   }
 
   sort(customers.begin(),customers.end(), [] (const vector<int> &a, const vector<int> &b){
      return a[0]<b[0];
   });
   priority_queue<pii,vector<pii>, greater<pii>> roomHeap;
   priority_queue<int,vector<int>,greater<int>> rooms;
   int maxRoom=1;
   vector<int> res(n);
   res[customers[0][2]]=1;
   roomHeap.push(pii(customers[0][1],maxRoom));
   for (int i = 1; i < n; i++){
      while (!roomHeap.empty() && customers[i][0]>roomHeap.top().first){
         rooms.push(roomHeap.top().second);
         roomHeap.pop();
      }
      if (rooms.empty()){
         maxRoom++;
         res[customers[i][2]]=maxRoom;
         roomHeap.push(pii(customers[i][1],maxRoom));
      }
      else{
         res[customers[i][2]]=rooms.top();
         rooms.pop();
         roomHeap.push(pii(customers[i][1],res[customers[i][2]]));
      }
   }
   cout<<maxRoom<<endl;
   for (int i = 0; i < n; i++){
      cout<<res[i]<<" ";
   }
}
int main(){
   int t=1;
   //cin>>t;
   while (t--){
      solve();
   }
