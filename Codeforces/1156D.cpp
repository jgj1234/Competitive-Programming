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
    vector<vector<pii>> nodeMap(n);
    for (int i = 0; i < n - 1; i++){
        int x,y,c;
        cin>>x>>y>>c;--x;--y;
        nodeMap[x].emplace_back(pii(y,c));
        nodeMap[y].emplace_back(pii(x,c));
    }
    vector<ll> sub(n), ones(n);
    auto dfs = [&] (auto&& self, int node, int parent) -> void{
        for (auto [neighbor, type]: nodeMap[node]){
            if (neighbor!=parent){
                self(self,neighbor,node);
                if (type==1){
                    ones[node] += ones[neighbor] + 1;
                    sub[node] += ones[neighbor] + 1;
                }
                else{
                    sub[node] += sub[neighbor] + 1;
                }
            }
        }
        //cout<<node+1<<" "<<sub[node]<<" "<<ones[node]<<endl;
    };
    dfs(dfs,0,0);
    auto dfs1 = [&] (auto&& self, int node, int parent, bool parEdge, ll oc, ll gc) ->ll{
        ll res = sub[node];
        if (parEdge){
            gc = oc;
        }
        else{
            oc = 0;
        }
        res+=gc;
        for (auto [neighbor, type]: nodeMap[node]){
            if (neighbor!=parent){
                res+=self(self,neighbor,node,type,oc+(ones[node]-ones[neighbor]),gc+(sub[node]-sub[neighbor]));
            }
        }
        return res;
    };
    cout<<dfs1(dfs1,0,0,false,0,0)<<endl;
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