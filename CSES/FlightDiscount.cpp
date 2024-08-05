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
#define MOD2 998244353
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
 
void solve(){
    int n,m;
    cin>>n>>m;
    vector<vector<pii>> nodeMap(n);
    for (int i = 0; i < m; i++){
        int a,b,c;
        cin>>a>>b>>c;
        nodeMap[a-1].emplace_back(b-1,c);
    }
    auto cmp = [&] (const pair<int,pair<ll,bool>> &a, const pair<int,pair<ll,bool>> &b){
        return a.second.first>b.second.first;
    };
    priority_queue<pair<int, pair<ll, bool>>, vector<pair<int,pair<ll,bool>>>, decltype(cmp)> heap(cmp);
    heap.push({0,{0,true}});
    vector<pair<ll,ll>> dp (n,pair<ll,ll>(LLONG_MAX,LLONG_MAX));
    dp[0]={0,0};
    while (!heap.empty()){
        auto [node, p] = heap.top(); heap.pop();
        auto [cost, half] = p;
        if (node==n-1) break;
        if ((half && cost>dp[node].second) || (!half && cost>dp[node].first)) continue;
        
        for (auto [neighbor, weight]: nodeMap[node]){
            if (half){
                if (cost+weight<dp[neighbor].second){
                    heap.push({neighbor,{cost+weight,half}});
                    dp[neighbor].second=cost+weight;
                }
                if (cost+weight/2<dp[neighbor].first){
                    heap.push({neighbor,{cost+weight/2,false}});
                    dp[neighbor].first=cost+weight/2;
                }
            }
            else{
                if (cost+weight<dp[neighbor].first){
                    heap.push({neighbor,{cost+weight,half}});
                    dp[neighbor].first=cost+weight;
                }
            }
        }
    }
    cout<<dp[n-1].first<<endl;
    
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