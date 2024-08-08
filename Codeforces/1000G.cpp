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
constexpr ll N = 300006, MAX_LG = 19;
ll sub[N], par[N-1], w[N], jump[N][MAX_LG], pos[N][MAX_LG],e[N], v[N], out[N], depths[N];
void solve(){
    int n,q;
    cin>>n>>q;
    vector<ll> nums(n);
    for (int i = 0; i < n; i++) cin>>nums[i];
    vector<vector<pii>> nodeMap(n);
    for (int i = 0; i < n - 1; i++){
        int a,b,w;
        cin>>a>>b>>w;
        --a;--b;
        nodeMap[a].emplace_back(b,w);
        nodeMap[b].emplace_back(a,w);
    }
    const int LG = 32 - __builtin_clz(n);
    auto dfs1 = [&] (auto&& self, ll node, ll parent, ll weight, ll ew, ll vw, ll d) -> ll{
        if (node!=0){
            par[node-1] = parent;
        }
        depths[node] = d;
        vw+=nums[node]; //Formula for vsum  = v[n1] + v[n2] - 2*v[lca] + nums[lca]
        w[node] = weight; e[node] = ew; v[node] = vw;
        ll x = nums[node];
        for (auto [neighbor, we]: nodeMap[node]){
            if (neighbor!=parent){
                x+=max(0LL, self(self,neighbor,node, we, ew+we,vw,d+1));
            }
        }
        sub[node]=x;
        return x-2*weight;
    };
    auto kth = [&] (int node, int k)-> int{
        int curr = node;
        for (int i = LG-1; i>=0; i--){
            if ((k&(1<<i))!=0){
                curr = pos[curr][i];
                if (curr==-1) return -1;
            }
        }
        return curr;
    };
    auto lca = [&] (int a, int b)-> int{
        if (depths[a]<depths[b]){
            swap(a,b);
        }
        int diff = depths[a]-depths[b];
        int c = kth(a,diff);
        if (b==c) return c;
        for (int i = LG - 1; i>=0 ; i--){
            if (pos[c][i]!=pos[b][i]){
                c = pos[c][i];
                b = pos[b][i];
            }
        }
        return pos[c][0];
    };
    dfs1(dfs1,0,0,0,0,0,0);
    //cout<<sub[0]<<endl;
    auto dfs2 = [&] (auto&& self, ll node, ll parent, ll pass) -> void{
        out[node] = max(0LL, pass-2*w[node]);
        //cout<<node<<" "<<out[node]<<endl;
        ll curr = sub[node]+out[node];
        for (auto [neighbor, we]: nodeMap[node]){
            if (neighbor!=parent){
                self(self,neighbor,node, curr-max(0LL,sub[neighbor]-2*w[neighbor]));
            }
        }
    };
    dfs2(dfs2,0,0,0);
    for (int i = 1; i < n; i++){
        pos[i][0] = par[i-1];
        jump[i][0] = max(0LL,sub[par[i-1]]-nums[par[i-1]]);
        ll x = sub[i] - 2*w[i];
        if (x>0) jump[i][0]-=x;
    }
    for (int j = 1; j < LG; j++){
        for (int i = 1; i < n; i++){
            ll p = pos[i][j-1];
            if (p==0){
                pos[i][j]=0;
                jump[i][j] = jump[i][j-1];
                continue;
            }
            pos[i][j] = pos[p][j-1];
            jump[i][j] = jump[i][j-1]+jump[pos[i][j-1]][j-1];
        }
    }
    while (q--){
        int a,b;
        cin>>a>>b;
        --a;--b;
        if (depths[a]>depths[b]) swap(a,b);
        if (a==b){
            //cout<<sub[a]<<" "<<out[a]<<endl;
            cout<<sub[a]+out[a]<<endl;
            continue;
        }
        ll l = lca(a,b);
        ll res = (v[a]+v[b]-2*v[l]+nums[l])-(e[a]+e[b]-2*e[l])+out[l];
        //cout<<res-out[l]<<" "<<res<<endl;
        ll bdist = depths[b]-depths[l];
        ll curr = b;
        for (int i = 0; i < LG; i++){
            if (bdist&(1<<i)){
                //cout<<curr<<" "<<i<<" "<<jump[curr][i]<<endl;
                res+=jump[curr][i];
                curr=pos[curr][i];
            }
        }
        ll adist = max(0LL,depths[a]-depths[l]-1);
        curr = a;
        for (int i = 0; i < LG; i++){
            if (adist&(1<<i)){
                res+=jump[curr][i];
                curr = pos[curr][i];
            }
        }
        if (a!=l){
            if (sub[curr]-2*w[curr]>0) res-=(sub[curr]-2*w[curr]);
        }
        if (a!=l){
            res+=max(0LL,(sub[a]-nums[a])+(sub[b]-nums[b]));
        }
        else{
            res+=max(0LL,sub[b]-nums[b]);
        }
        cout<<res<<endl;
    }
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