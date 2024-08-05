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
#pragma GCC optimize("O3,unroll-loops")
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
struct TreeTable{ //Assumes 0 is the root and parents are for nodes 1 to n - 1
    vector<vector<int>> table;
    vector<vector<int>> mw;
    int lg;
    TreeTable(int n, vector<int>& par){
        int max_log = 32 - __builtin_clz(n);
        lg = max_log;
        table.resize(n,vector<int> (max_log));
        for (int i = 0; i < n - 1; i++){
            table[i + 1][0] = par[i];
        }
        for (int bit = 1; bit < max_log; bit++){
            for (int i = 1; i < n; i++){
                table[i][bit] = table[table[i][bit-1]][bit-1];
            }
        }
    }
    void getDepths(int node, int parent, int depth, vector<int>& res, vector<vector<int>>& nodeMap){
        res[node] = depth;
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                getDepths(neighbor,node,depth+1,res,nodeMap);
            }
        }
    }
    int kth(int node, int k){
        int curr = node;
        for (int i = 30; i>=0; i--){
            if ((k&(1<<i))!=0){
                curr = table[curr][i];
                if (curr==-1) return -1;
            }
        }
        return curr;
    }
    int lca(int a, int b, vector<int>& depths){
        if (depths[a]<depths[b]){
            swap(a,b);
        }
        int diff = depths[a]-depths[b];
        int c = kth(a,diff);
        if (b==c) return c;
        for (int i = lg - 1; i>=0 ; i--){
            if (table[c][i]!=table[b][i]){
                c = table[c][i];
                b = table[b][i];
            }
        }
        return table[c][0];
    }
};
void solve(){
    int n,m,q;
    cin>>n>>m>>q;
    vector<vector<int>> nodeMap(n);
    for (int i = 0; i < n - 1; i++){
        int a,b;
        cin>>a>>b;
        --a;--b;
        nodeMap[a].emplace_back(b);
        nodeMap[b].emplace_back(a);
    }
    vector<int> depths(n);
    vector<int> par(n-1);
    vector<vector<int>> children(n);
    auto dfs = [&] (auto&& self, int node, int parent, int depth)->void{
        depths[node]=depth;
        if (node!=0){
            par[node-1]=parent;
        }
        for (int neighbor: nodeMap[node]){
            if (neighbor!=parent){
                children[node].emplace_back(neighbor);
                self(self,neighbor,node,depth+1);
            }
        }
    };
    dfs(dfs,0,0,0);
    TreeTable tt(n,par);
    vector<vector<int>> cities(n);
    for (int i = 0; i < m; i++){
        int x;
        cin>>x;
        cities[x-1].emplace_back(i+1);
    }
    int lg = 32-__builtin_clz(n);
    vector<vector<vector<int>>> table(n,vector<vector<int>> (lg));
    for (int i = 0; i < n; i++){
        sort(all(cities[i]));
        for (int j = 0; j < min(10,(int)cities[i].size());j++){
            for (int child: children[i]){
                table[child][0].emplace_back(cities[i][j]);
            }
        }
    }
    auto me = [&] (vector<int>& l, vector<int>& r, vector<int>& res)->void{
        int lp = 0, rp = 0;
        while (lp < l.size() && rp<r.size() && res.size()<=10){
            if (l[lp]<r[rp]){
                res.emplace_back(l[lp++]);
            }
            else{
                res.emplace_back(r[rp++]);
            }
        }
        while (lp<l.size() && res.size()<=10){
            res.emplace_back(l[lp++]);
        }
        while (rp<r.size() && res.size()<=10){
            res.emplace_back(r[rp++]);
        }
    };
    for (int j = 1; j < lg; j++){
        for (int i = 0; i < n; i++){
            me(table[i][j-1],table[tt.table[i][j-1]][j-1],table[i][j]);
        }
    }
    while (q--){
        int v,u,a;
        cin>>v>>u>>a;
        --v;--u;
        if (u==v){
            cout<<min(a,(int)cities[u].size())<<" ";
            for (int i = 0; i < min(a,(int)cities[u].size());i++){
                cout<<cities[u][i]<<" ";
            }
            cout<<endl;
            continue;
        }
        int l = tt.lca(u,v,depths);
        int distu = depths[u]-depths[l]-1;
        int curr = u;
        vector<int> left(all(cities[u]));
        if (distu>0){
            for (int i = 0; i < lg; i++){
                if ((distu)&(1<<i)){
                    vector<int> p;
                    me(left,table[curr][i],p);
                    curr = tt.table[curr][i];
                    left=p;
                }
            }
        }
        if (l!=u && l!=v){
            vector<int> g;
            me(left,cities[l],g);
            left=g;
        }
        vector<int> right(all(cities[v]));
        int distv = depths[v]-depths[l]-1;
        curr = v;
        if (distv>0){
            for (int i = 0; i < lg; i++){
                if ((distv)&(1<<i)){
                    vector<int> p;
                    me(right,table[curr][i],p);
                    curr = tt.table[curr][i];
                    right = p;
                }
            }
        }
        vector<int> r;
        me(left,right,r);
        cout<<min(a,(int)r.size())<<" ";
        for (int i = 0; i < min(a,(int)r.size()); i++) cout<<r[i]<<" ";
        cout<<endl;
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