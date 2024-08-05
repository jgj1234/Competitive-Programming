#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <ext/pb_ds/assoc_container.hpp>

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
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

void solve(){
   ll r;
   cin>>r;
   ll res = 0;
   for (int x = 1; x<=r; x++){
       int lp = 1;
       int rp = r+1;
       while (lp<=rp){
           int mid = (lp+rp)>>1;
           double dist = sqrt(pow(x,2)+pow(mid,2));
           if (dist<r){
               lp=mid+1;
           }
           else{
               rp=mid-1;
           }
       }
       int y = lp;
       double dist = sqrt(pow(x,2)+(y,2));
       while (dist<r+1){
           res+=4;
           y++;
           dist = sqrt(pow(x,2)+pow(y,2));
       }
   }
   cout<<res+4<<endl;
}
int main(){
   int t;
   cin>>t;
   while (t--){
      solve();
   }
}