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
    int n;
    cin>>n;
    vector<ll> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    vector<vector<int>> nodeMap(n);
    for (int i = 0; i < n - 1; i++){
        int x;
        cin>>x;
        --x;
        nodeMap[i+1].emplace_back(x);
        nodeMap[x].emplace_back(i+1);
    }
    auto dfs = [&] (auto&& self, int node, int parent) -> ll{
        ll mn = LLONG_MAX;
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                mn = min(mn,self(self,neighbor,node));
            }
        }
        if (node==0){
            return nums[node]+mn;
        }
        if  (mn==LLONG_MAX){
            return nums[node];
        }
        if (mn<=nums[node]){
            return mn;
        }
        return (nums[node]+mn)/2;
    };
    cout<<dfs(dfs,0,0)<<endl;
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