#include <bits/stdc++.h>
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
    vector<ll> gas(n);
    for (int i = 0; i < n; i++) cin>>gas[i];
    vector<vector<pii>> nodeMap(n);
    for (int i = 0; i < n - 1; i++){
        ll a,b,c;
        cin>>a>>b>>c;
        --a;--b;
        nodeMap[a].emplace_back(b,c);
        nodeMap[b].emplace_back(a,c);
    }
    vector<ll> close(n), open(n);
    auto dfs = [&] (auto&& self, int node, int parent) -> void{
        ll mx1 = 0, mx2 = 0;
        for (auto[neighbor, weight]: nodeMap[node]){
            if (neighbor!=parent){
                self(self,neighbor,node);
                if (open[neighbor]-weight>mx1){
                    mx2 = mx1;
                    mx1 = open[neighbor] - weight;
                }
                else if (open[neighbor]-weight>mx2){
                    mx2 = open[neighbor] - weight;
                }
            }
        }
        close[node] = mx1+mx2+gas[node];
        open[node] = mx1+gas[node];
    };
    dfs(dfs,0,0);
    ll res = 0;
    for (int i = 0; i < n; i++){
        res = max(res, close[i]);
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