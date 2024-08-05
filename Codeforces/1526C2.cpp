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
    int n;
    cin>>n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    priority_queue<int> heap;
    int res = 0;
    int curr = 0;
    ll currHealth = 0;
    for (int i = 0; i < n; i++){
        if (currHealth+nums[i]<0){
            if (heap.empty()||-1*nums[i]>heap.top()) continue;
            int tp = heap.top();
            heap.pop();
            currHealth+=tp;
            curr--;
        }
        curr++;
        currHealth+=nums[i];
        if (nums[i]<0) heap.push(-1*nums[i]);
        res=max(res,curr);
    }
    cout<<res<<endl;
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