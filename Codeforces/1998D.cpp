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
// maximum value of dist[jump_node]-i>0
void solve(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> alternative(n);
    for (int i = 0; i < n; i++) alternative[i].emplace_back(i+1);
    for (int i = 0; i < m; i++){
        int u,v;
        cin>>u>>v;
        --u;--v;
        alternative[u].emplace_back(v);
    }
    
    priority_queue<pair<ll,ll>,vector<pair<ll,ll>>, greater<pair<ll,ll>>> heap;
    heap.push(pii(0,0));
    vector<ll> ed(n,LLONG_MAX);ed[0]=0;
    vector<map<ll,ll>> jump(n);
    while (!heap.empty()){
        auto [weight, node] = heap.top(); heap.pop();
        if (weight>ed[node]) continue;
        if (node==n-1) continue;
        for (int neighbor: alternative[node]){
            if (weight+1<ed[neighbor]){
                ed[neighbor]=weight+1;
                heap.push(pair<ll,ll>(weight+1,neighbor));
            }
            if (!jump[node].count(neighbor)){
                    jump[node][neighbor]=weight+1;
            }
            else{
                jump[node][neighbor]=min(jump[node][neighbor],weight+1);
            }
        }
    }
    vector<pair<int,int>> q;
    string res;
    for (int i = 0; i <  n - 1; i++){
        while (q.size()>0 && q[q.size()-1].first - i <= q[q.size()-1].second) {
            q.pop_back();
        }
        if (q.size()>0){
            res.pb('0');
        }
        else{
            res.pb('1');
        }
        for (auto [k,v]:jump[i]){
            q.emplace_back(pii(k,v));
        }
    }
    cout<<res<<endl;
    
    
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