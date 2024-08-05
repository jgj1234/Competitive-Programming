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
#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
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
    ll x;
    cin>>x;
    ll curr = 1;
    vector<int> res;
    ll currNum = 100;
    while (curr*2<=x){
        res.emplace_back(currNum);
        currNum+=100;
        curr<<=1;
    }
    ll rem = x - curr;
    for (int i = 63; i>=0; i--){
        if ((rem & (1LL<<i))!=0){
            int lastNum = ((i==0?0:res[i-1]));
            res.emplace_back(lastNum+99);
        }
    }
    cout<<res.size()<<endl;
    for (int i = 0; i < res.size(); i++){
        cout<<res[i]<<" ";
    }
    cout<<endl;
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