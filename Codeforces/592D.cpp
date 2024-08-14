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
    int n,m;
    cin>>n>>m;
    vector<vector<int>> nodeMap(n);
    vector<bool> marked(n);
    for (int i = 0; i < n - 1; i++){
        int u,v;
        cin>>u>>v;
        --u;--v;
        nodeMap[u].emplace_back(v);
        nodeMap[v].emplace_back(u);
    }
    for (int i = 0; i < n; i++){
        int a;
        cin>>a;
        marked[a-1]=true;
    }
    vector<bool> has(n);
    vector<vector<ll>> dp (n,vector<ll> (2)); //ends/not end
    vector<ll> c(n), c1(n);;
    auto dfs1 = [&] (auto&& self, int node, int parent) -> pair<bool,ll>{
        if (marked[node]){
            has[node] = true;
        }
        ll s = 0;
        ll ct = marked[node];
        ll ct1 = 0;
        ll mx = 0;
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                auto [f , con] = self(self,neighbor,node);
                if (f){
                    has[node] = true;
                    mx = max(mx,dp[neighbor][0]-dp[neighbor][1]);
                    s+=dp[neighbor][0];
                    ct1++;
                }
                ct+=con;
            }
        }
        c[node]=ct;
        c1[node] = ct1;
        dp[node][0] = 2*ct1+s;
        dp[node][1] = 2*(max(ct1-1,0LL))+(s-mx)+(ct1>0);
        //cout<<node+1<<" "<<dp[node][0]<<" "<<dp[node][1]<<endl;
        return pair<bool,ll>(has[node],ct);
    };
    dfs1(dfs1,0,0);
    vector<ll> res(n);
    res[0] = min(dp[0][0],dp[0][1]);
    auto dfs2 = [&] (auto&& self, int node, int parent, ll pass0,ll pass1) -> void{
        if (node!=0){
            res[node] = min((c[node]!=c[0]?pass0+2:0)+dp[node][1],(c[node]!=c[0]?pass1+1:0)+dp[node][0]);
        }
        //cout<<node+1<<" "<<pass0<<" "<<pass1<<" "<<res[node]<<" "<<dp[node][0]<<" "<<dp[node][1]<<endl;
        ll mx1 = 0, mx1i = 0, mx2 = 0;
        ll s = 0;
        ll ct =c1[node];
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent && has[neighbor]){
                ll diff = dp[neighbor][0]-dp[neighbor][1];
                s+=dp[neighbor][0];
                if (diff>mx1){
                    mx2=mx1;
                    mx1=diff;
                    mx1i=neighbor;
                }
                else if (diff>mx2){
                    mx2=diff;
                }
            }
        }
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                ll p0 = dp[node][0];
                if (has[neighbor]){
                    p0-=(dp[neighbor][0]+2);
                }
                if (c[node]!=c[0]){
                    p0+=pass0+2;
                }
                ll p1 = s;
                ll curr = ct;
                if (has[neighbor]){
                    p1-=dp[neighbor][0];
                    curr--;
                }
                if (neighbor==mx1i){
                        p1-=mx2;
                }
                else{
                    p1-=mx1;
                }
                p1+=2*max(0LL,curr-1)+(curr>0);
                ll x = s - (has[neighbor]? dp[neighbor][0]:0);
                ll p2 = min(p1+((c[node]!=c[0])?pass0+2:0),x+2*curr+((c[node]!=c[0])?pass1+1:0));
                self(self,neighbor,node,p0,p2);
            }
        }
    };
    dfs2(dfs2,0,0,0,0);
    int r = 0;
    for (int i = 1; i < n; i++){
        if (res[i]<res[r]){
            r=i;
        }
    }
    cout<<r+1<<endl;
    cout<<res[r]<<endl;
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